#ifndef IRGEN_H
#define IRGEN_H

#include "AST.hpp"
#include "KaleidoscopeJIT.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace llvm;
using namespace llvm::orc;

//===----------------------------------------------------------------------===//
// Code Generation
//===----------------------------------------------------------------------===//

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> Builder;
//todo make a stack for this; getDecl
static std::map<std::string, Value *> NamedValues; // address
static std::unique_ptr<legacy::FunctionPassManager> TheFPM;
static std::unique_ptr<KaleidoscopeJIT> TheJIT;
static std::map<std::string, std::unique_ptr<PrototypeAST>> FunctionProtos;
static ExitOnError ExitOnErr;

/// LogError* - These are little helper functions for error handling.
std::unique_ptr<ExprAST> LogError(const char *Str) {
  fprintf(stderr, "Error: %s\n", Str);
  return nullptr;
}

Value *LogErrorV(const char *Str) {
  LogError(Str);
  return nullptr;
}

Function *getFunction(std::string Name) {
  // First, see if the function has already been added to the current module.
  if (auto *F = TheModule->getFunction(Name))
    return F;

  // If not, check whether we can codegen the declaration from some existing
  // prototype.
  auto FI = FunctionProtos.find(Name);
  if (FI != FunctionProtos.end())
    return FI->second->codegen();

  // If no existing prototype exists, return null.
  return nullptr;
}

// Methods

Value *BlockAST::codegen() {
  // new symtab for each scope
  auto symtab_stash = NamedValues;
  for (auto &&pAST : items) {
    pAST->codegen();
  }
  // restore symtab
  NamedValues = symtab_stash;
  return nullptr;
}

Value *NumberExprAST::codegen() {
  return Builder->getInt32(Val);
}

Value *VariableExprAST::codegen() {
  // Look this variable up in the function.
  Value *V = NamedValues[Name];
  if (!V)
    return LogErrorV("Unknown variable name");
  return Builder->CreateLoad(Builder->getInt32Ty(), V, Name);
}

Value *UnaryExprAST::codegen() {
  Value *OperandV = Operand->codegen();
  if (!OperandV)
    return nullptr;

  if (Opcode == '-') {
    return Builder->CreateNeg(OperandV);
  } else if (Opcode == '!') {
    return Builder->CreateNot(OperandV);
  } else if (Opcode == '+') {
    return OperandV;  
  } else {
    assert(false);
  }
}

Value *BinaryExprAST::codegen() {
  Value *L = LHS->codegen(), *R; // codegen of RHS postponed due to Logic Op
  // mapping
  std::unordered_map<std::string, Instruction::BinaryOps> sarith2op = {
      {"+", Instruction::BinaryOps::Add},  {"-", Instruction::BinaryOps::Sub},
      {"*", Instruction::BinaryOps::Mul},  {"/", Instruction::BinaryOps::SDiv},
      {"%", Instruction::BinaryOps::SRem},
  };
  std::unordered_map<std::string, CmpInst::Predicate> srel2pred = {
      {"<", CmpInst::Predicate::ICMP_SLT},
      {"LE_OP", CmpInst::Predicate::ICMP_SLE},
      {">", CmpInst::Predicate::ICMP_SGT},
      {"GE_OP", CmpInst::Predicate::ICMP_SGE},
      {"EQ_OP", CmpInst::Predicate::ICMP_EQ},
      {"NE_OP", CmpInst::Predicate::ICMP_NE},
  };
  // arithmetic op: i32
  auto it = sarith2op.find(Op);
  if (it != sarith2op.end()) {
    R = RHS->codegen();
    return Builder->CreateBinOp(it->second, L, R, "arithtmp");
  } else {
    // relation op: i32 in {0, 1}
    auto it = srel2pred.find(Op);
    if (it != srel2pred.end()) {
      R = RHS->codegen();
      L = Builder->CreateICmp(it->second, L, R, "cmptmp");
      return Builder->CreateZExt(L, Builder->getInt32Ty(), "i1toi32_");
    } else {
      // logic op: short-circuit evaluation
      BasicBlock *EntryBB = Builder->GetInsertBlock();
      Function *TheFunction = EntryBB->getParent();
      BasicBlock *ThenBB = BasicBlock::Create(*TheContext, "R", TheFunction);
      BasicBlock *MergeBB = BasicBlock::Create(*TheContext, "bypass");
      // trans possible i32 xhs (from e.g. AddExp) to i1
      Value *CondV = Builder->CreateICmpNE(L, Builder->getInt32(0), "short");

      if (Op == "AND_OP") {
        Builder->CreateCondBr(CondV, ThenBB, MergeBB);
      } else if (Op == "OR_OP") {
        Builder->CreateCondBr(CondV, MergeBB, ThenBB);
      } else {
        assert(false);
      }

      // Fill 'then' block
      Builder->SetInsertPoint(ThenBB);
      R = RHS->codegen();
      R = Builder->CreateICmpNE(R, Builder->getInt32(0), "i32toi1_");
      Builder->CreateBr(MergeBB);
      ThenBB = Builder->GetInsertBlock(); // needed by PHI

      // Finish merge block.
      MergeBB->insertInto(TheFunction);
      Builder->SetInsertPoint(MergeBB);
      PHINode *PN = Builder->CreatePHI(Builder->getInt1Ty(), 2, "logictmp");
      PN->addIncoming(CondV, EntryBB);
      PN->addIncoming(R, ThenBB);
      return Builder->CreateZExt(PN, Builder->getInt32Ty(), "i1toi32_");
    }
  }
}

Value *VarAssignAST::codegen() {
  auto val = RHS->codegen();
  auto var = NamedValues[VarName];
  Builder->CreateStore(val, var);
  return val;
}

Value *ReturnAST::codegen() {
  if (Value *RetVal = RHS->codegen()) {
    // Finish off the function.
    Builder->CreateRet(RetVal);
  }
  return nullptr;
}

Function *GenExtern(const std::string &Callee,
                    const std::vector<std::unique_ptr<ExprAST>> &Args);

Value *CallExprAST::codegen() {
  // Look up the name in the global module table.
  Function *CalleeF = getFunction(Callee);
  if (!CalleeF)
    // ad-hoc ref inserted into TheModule; JIT session error if not in lib
    CalleeF = GenExtern(Callee, Args);

  // If argument mismatch error.
  if (CalleeF->arg_size() != Args.size())
    return LogErrorV("Incorrect # arguments passed");

  std::vector<Value *> ArgsV;
  for (unsigned i = 0, e = Args.size(); i != e; ++i) {
    ArgsV.push_back(Args[i]->codegen());
    if (!ArgsV.back())
      return nullptr;
  }

  return Builder->CreateCall(CalleeF, ArgsV, "calltmp");
}

Value *IfAST::codegen() {
  // TODO CFG simplification is welcome
  Value *CondV = Cond->codegen();
  if (!CondV)
    return nullptr;

  // Convert condition to a bool by comparing non-equal to 0.
  CondV = Builder->CreateICmpNE(CondV, Builder->getInt32(0), "ifcond");
  // get current function
  Function *TheFunction = Builder->GetInsertBlock()->getParent();

  // Create basic blocks for if-[then]-[else]- control flow.
  // Only 'then' block is appended, 
  // since Codegen of 'then' block might create new blocks after it.
  BasicBlock *ThenBB = BasicBlock::Create(*TheContext, "then", TheFunction);
  BasicBlock *ElseBB = BasicBlock::Create(*TheContext, "else");
  BasicBlock *MergeBB = BasicBlock::Create(*TheContext, "ifcont");

  Builder->CreateCondBr(CondV, ThenBB, ElseBB);

  // Fill 'then' block
  Builder->SetInsertPoint(ThenBB);
  if (Then) {
    Then->codegen();
  }
  Builder->CreateBr(MergeBB);

  // Finish 'else' block
  ElseBB->insertInto(TheFunction);
  Builder->SetInsertPoint(ElseBB);
  if (Else) {
    Else->codegen();
  }
  Builder->CreateBr(MergeBB);

  // Finish merge block.
  MergeBB->insertInto(TheFunction);
  Builder->SetInsertPoint(MergeBB);

  return nullptr;
}

Value *WhileAST::codegen() {
  // get current function
  Function *TheFunction = Builder->GetInsertBlock()->getParent();
  
  // Create basic blocks for -[loop]-loopend-afterloop- control flow.
  BasicBlock *LoopBB = BasicBlock::Create(*TheContext, "loop", TheFunction);
  BasicBlock *LoopendBB = BasicBlock::Create(*TheContext, "loopend");
  BasicBlock *AfterBB = BasicBlock::Create(*TheContext, "afterloop");

  // establish magic labels
  auto symtab_stash = NamedValues;
  NamedValues["__WEND__"] = AfterBB;
  NamedValues["__WHILE__"] = LoopBB;
  
  // practice: loopend lies after loop; jump there on entry
  Builder->CreateBr(LoopendBB);
  
  // Fill 'loop' block
  Builder->SetInsertPoint(LoopBB);
  if (Body) {
    Body->codegen();
  }
  // a natural fall-thru results in unterminated BB
  Builder->CreateBr(LoopendBB);
  
  // Finish 'loopend' block
  LoopendBB->insertInto(TheFunction);
  Builder->SetInsertPoint(LoopendBB);
  Value *EndV = End->codegen();
  if (!EndV)
    return nullptr;
  // while non-zero, loop
  EndV = Builder->CreateICmpNE(EndV, Builder->getInt32(0), "whilecond");
  Builder->CreateCondBr(EndV, LoopBB, AfterBB);

  // Finish "afterloop" block.
  AfterBB->insertInto(TheFunction);
  Builder->SetInsertPoint(AfterBB);

  NamedValues = symtab_stash;
  return nullptr;
}

Value *GotoAST::codegen() {
  if (auto *tgtBB = dyn_cast<BasicBlock>(NamedValues[label])) {
    Builder->CreateBr(tgtBB);
  } else {
    assert(false);
  }
  return nullptr;
}

Value* VarDefAST::codegen() {
  for (auto &&p : VarNames) {
    // alloc stack space
    auto alloc = Builder->CreateAlloca(Builder->getInt32Ty(), nullptr, p.first);
    // Record locals in the NamedValues map.
    NamedValues[p.first] = alloc;
    // InitVal
    if (p.second) {
      auto iv = p.second->codegen();
      Builder->CreateStore(iv, alloc);
    }
  }
  return nullptr;
}

Value *GlblVarDefAST::codegen() {
  for (auto &&p : VarNames) {
    // todo const init
    // using zero initializer
    auto gv = new GlobalVariable(*TheModule, Builder->getInt32Ty(), false,
                                 GlobalVariable::CommonLinkage,
                                 Builder->getInt32(0), p.first);
    // Record in the NamedValues map.
    NamedValues[p.first] = gv;
  }
  return nullptr;
}

Function *GenExtern(const std::string &Callee,
                    const std::vector<std::unique_ptr<ExprAST>> &Args) {
  auto proto = std::make_unique<PrototypeAST>(
      Callee, std::vector<std::string>(Args.size()));
  // register in 2 tbl
  Function *F = proto->codegen();
  FunctionProtos[proto->getName()] = std::move(proto);
  return F;
}

Function *PrototypeAST::codegen() {
  // Make the function type:  int(int,int) etc.
  std::vector<Type *> Ints(Args.size(), Builder->getInt32Ty());
  FunctionType *FT = FunctionType::get(Builder->getInt32Ty(), Ints, false);

  Function *F =
      Function::Create(FT, Function::ExternalLinkage, Name, TheModule.get());

  // Set names for all arguments.
  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(Args[Idx++]);

  return F;
}

Function *FunctionAST::codegen() {
  // Transfer ownership of the prototype to the FunctionProtos map, but keep a
  // reference to it for use below.
  auto &P = *Proto;
  FunctionProtos[Proto->getName()] = std::move(Proto);
  Function *TheFunction = getFunction(P.getName());
  if (!TheFunction)
    return nullptr;
  
  // new symtab for each scope
  auto symtab_stash = NamedValues;
  
  // Create a new basic block to start insertion into.
  BasicBlock *BB = BasicBlock::Create(*TheContext, "entry", TheFunction);
  Builder->SetInsertPoint(BB);

  // Record the function arguments in the NamedValues map.
  for (auto &Arg : TheFunction->args()) {
    // alloc stack space
    auto alloc =
        Builder->CreateAlloca(Builder->getInt32Ty(), nullptr, Arg.getName());
    NamedValues[std::string(Arg.getName())] = alloc;
  }
  // Pass by Value
  for (auto &Arg : TheFunction->args()) {
    Builder->CreateStore(&Arg, NamedValues[std::string(Arg.getName())]);
  }

  Body->codegen();

  //TODO FPM?
  // BB not necessarily well-formed due to macro-expansion-like codegen
  for (BasicBlock &BB : *TheFunction) {
    //todo empty BB should be removed; guide ref to successor
    // append default terminator
    if (!BB.getTerminator()) {
      Builder->SetInsertPoint(&BB);
      Builder->CreateRet(Builder->getInt32(1));
    } 
    // eliminate instructions after first terminator
    else {
      auto it = BB.begin();
      for (; !it->isTerminator(); ++it)
        ;
      for (++it; it != BB.end(); it = it->eraseFromParent())
        ;
    }
  }

  // Validate the generated code, checking for consistency.
  verifyFunction(*TheFunction, &llvm::errs());

  // Run the optimizer on the function.
  TheFPM->run(*TheFunction);

  // restore symtab
  NamedValues = symtab_stash;
  
  return TheFunction;
}

#endif