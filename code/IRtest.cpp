#include "AST.hpp"
#include "IRgen.hpp"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include <memory>
#include <system_error>

using namespace llvm;

// drv
static void InitializeContext() {
  // JIT
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();
  TheJIT = ExitOnErr(KaleidoscopeJIT::Create());

  TheContext = std::make_unique<LLVMContext>();
  // Make the module, which holds all the code.
  TheModule = std::make_unique<Module>("SysY--", *TheContext);
  // Configure DL according to target
  TheModule->setDataLayout(TheJIT->getDataLayout());
  // Create a new builder for the module.
  Builder = std::make_unique<IRBuilder<>>(*TheContext);
  // Create a new pass manager attached to it.
  TheFPM = std::make_unique<legacy::FunctionPassManager>(TheModule.get());

  // Promote allocas to registers.
  TheFPM->add(createPromoteMemoryToRegisterPass());
  // Do simple "peephole" optimizations and bit-twiddling optzns.
  TheFPM->add(createInstructionCombiningPass());
  // Reassociate expressions.
  TheFPM->add(createReassociatePass());
  // Eliminate Common SubExpressions.
  TheFPM->add(createGVNPass());
  // Simplify the control flow graph (deleting unreachable blocks, etc).
  TheFPM->add(createCFGSimplificationPass());

  TheFPM->doInitialization();
}

int IR_entry(const grammarTree *root) {
  // return 0;
  InitializeContext();

  // IR codegen the CompUnit
  for (auto &&pAST : proc_CompUnit(root)) {
    if (auto ppExprAST = std::get_if<std::unique_ptr<ExprAST>>(&pAST)) {
      // ExprAST -known info-> GlblVarDefAST
      auto pGlblVarDefAST = (GlblVarDefAST *)((*ppExprAST).get());
      pGlblVarDefAST->codegen();
    } else {
      // FunctionAST
      std::get<std::unique_ptr<FunctionAST>>(pAST)->codegen();
    }
  }
  // Print out all of the generated code.
  TheModule->print(llvm::errs(), nullptr);
  // dump to file
  std::error_code ec;
  TheModule->print(raw_fd_ostream("main.ll", ec), nullptr);

  // target obj gen
  // Create a ResourceTracker to track JIT'd memory allocated
  auto RT = TheJIT->getMainJITDylib().createResourceTracker();
  auto TSM = ThreadSafeModule(std::move(TheModule), std::move(TheContext));
  ExitOnErr(TheJIT->addModule(std::move(TSM), RT));

  // locate target obj entry, cast to func ptr and call it
  auto ExprSymbol = ExitOnErr(TheJIT->lookup("main"));
  int (*FP)() = (int (*)())(intptr_t)ExprSymbol.getAddress();
  fprintf(stderr, "Target main() exited on %d\n", FP());
  ExitOnErr(RT->remove());

  return 0;
}