#include "AST.hpp"
#include "IRgen.hpp"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
#include <memory>

using namespace llvm;

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// lib
/// putchari - putchar that takes a int and returns 0.
extern "C" DLLEXPORT int putchari(int X) {
  fputc((char)X, stderr);
  return 0;
}

extern "C" DLLEXPORT int putint(int i) {
  fprintf(stderr, "%d", i);
  return 0;
}

// drv
static void InitializeContext() {
  TheContext = std::make_unique<LLVMContext>();
  // Make the module, which holds all the code.
  TheModule = std::make_unique<Module>("SysY--", *TheContext);
  // Create a new builder for the module.
  Builder = std::make_unique<IRBuilder<>>(*TheContext);
  // Create a new pass manager attached to it.
  TheFPM = std::make_unique<legacy::FunctionPassManager>(TheModule.get());

  // Promote allocas to registers.
  TheFPM->add(createPromoteMemoryToRegisterPass());
  //// Do simple "peephole" optimizations and bit-twiddling optzns.
  //TheFPM->add(createInstructionCombiningPass());
  //// Reassociate expressions.
  //TheFPM->add(createReassociatePass());
  //// Eliminate Common SubExpressions.
  //TheFPM->add(createGVNPass());
  //// Simplify the control flow graph (deleting unreachable blocks, etc).
  //TheFPM->add(createCFGSimplificationPass());

  TheFPM->doInitialization();
}

int IR_entry(const grammarTree *root) {
  // return 0;
  InitializeContext();

  // Run the main "interpreter loop" now.
//   MainLoop();
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
  return 0;
}
