#ifndef IRGEN_H
#define IRGEN_H

#include "AST.hpp"
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

//===----------------------------------------------------------------------===//
// Code Generation
//===----------------------------------------------------------------------===//

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> Builder;
static std::map<std::string, Value *> NamedValues; // address
static std::unique_ptr<legacy::FunctionPassManager> TheFPM;
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
  return ConstantInt::get(*TheContext, APInt(32, Val, true));
}

Value *VariableExprAST::codegen() {
  // Look this variable up in the function.
  Value *V = NamedValues[Name];
  if (!V)
    return LogErrorV("Unknown variable name");
  return Builder->CreateLoad(Type::getInt32Ty(*TheContext), V, Name);
}

Value *UnaryExprAST::codegen() {
  Value *OperandV = Operand->codegen();
  if (!OperandV)
    return nullptr;

  if (Opcode == '-') {
    return Builder->CreateNeg(OperandV);
  } else if (Opcode == '!') {
    return Builder->CreateNot(OperandV);
  }
}

Value *BinaryExprAST::codegen() {
  Value *L = LHS->codegen();
  Value *R = RHS->codegen();
  if (!L || !R)
    return nullptr;

  if (Op == "+") {
    return Builder->CreateAdd(L, R, "addtmp");
  } else if (Op == "-") {
    return Builder->CreateSub(L, R, "subtmp");
  } else if (Op == "*") {
    return Builder->CreateMul(L, R, "multmp");
  } else if (Op == "/") {
    return Builder->CreateSDiv(L, R, "divtmp");
  } else if (Op == "%") {
    return Builder->CreateSRem(L, R, "divtmp");
  } else {
    std::unordered_map<std::string, CmpInst::Predicate> srel2pred = {
        {"<", CmpInst::Predicate::ICMP_SLT},
        {"LE_OP", CmpInst::Predicate::ICMP_SLE},
        {">", CmpInst::Predicate::ICMP_SGT},
        {"GE_OP", CmpInst::Predicate::ICMP_SGE},
        {"EQ_OP", CmpInst::Predicate::ICMP_EQ},
        {"NE_OP", CmpInst::Predicate::ICMP_NE},
    };
    auto it = srel2pred.find(Op);
    if (it != srel2pred.end()) {
      L = Builder->CreateICmp(it->second, L, R, "cmptmp");
      return Builder->CreateSExt(L, Type::getInt32Ty(*TheContext), "i1_i32");
    } else {
      return LogErrorV("invalid binary operator");
    }
  }
}

Value *VarAssignAST::codegen() {
  auto val = RHS->codegen();
  auto var = NamedValues[VarName];
  Builder->CreateStore(val, var);
  return val;
}

Value *ReturnExprAST::codegen() {
  if (Value *RetVal = RHS->codegen()) {
    // Finish off the function.
    Builder->CreateRet(RetVal);
    return RetVal;
  }
  return nullptr;
}

Value *CallExprAST::codegen() {
  // Look up the name in the global module table.
  Function *CalleeF = getFunction(Callee);
  if (!CalleeF)
    return LogErrorV("Unknown function referenced");

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

Value *IfExprAST::codegen() {
  // TODO CFG simplification is welcome
  Value *CondV = Cond->codegen();
  if (!CondV)
    return nullptr;

  // Convert condition to a bool by comparing non-equal to 0.
  CondV = Builder->CreateICmpNE(
      CondV, ConstantInt::get(*TheContext, APInt(32, 0, true)), "ifcond");
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

Value* VarDefAST::codegen() {
  for (auto &&p : VarNames) {
    // alloc stack space
    auto alloc =
        Builder->CreateAlloca(Type::getInt32Ty(*TheContext), nullptr,
                                        p.first);
    // Record locals in the NamedValues map.
    NamedValues[p.first] = alloc;
    // InitVal
    if (p.second) {
      auto iv = p.second->codegen();
      Builder->CreateStore(iv, alloc);
    }
  }
  return nullptr; //fuckoff
}

Value *GlblVarDefAST::codegen() {
  Constant *rv = nullptr;
  for (auto &&p : VarNames) {
    // todo const init
    rv = TheModule->getOrInsertGlobal(p.first, Type::getInt32Ty(*TheContext));
    // Record in the NamedValues map.
    NamedValues[p.first] = rv;
  }
  return rv;
}

Function *PrototypeAST::codegen() {
  // Make the function type:  int(int,int) etc.
  std::vector<Type *> Ints(Args.size(), Type::getInt32Ty(*TheContext));
  FunctionType *FT =
      FunctionType::get(Type::getInt32Ty(*TheContext), Ints, false);

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
    auto alloc = Builder->CreateAlloca(Type::getInt32Ty(*TheContext), nullptr,
                                        Arg.getName());
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
    // append default terminator
    if (!BB.getTerminator()) {
      Builder->SetInsertPoint(&BB);
      Builder->CreateRet(ConstantInt::get(*TheContext, APInt(32, 1, true)));
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