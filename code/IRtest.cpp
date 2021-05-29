#include "AST.hpp"
#include "IRgen.hpp"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
#include <memory>

using namespace llvm;

static void InitializeContext() {
  TheContext = std::make_unique<LLVMContext>();
  // Make the module, which holds all the code.
  TheModule = std::make_unique<Module>("my cool jit", *TheContext);
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
  InitializeContext();

  // Run the main "interpreter loop" now.
//   MainLoop();
  auto pf = get_FuncDef_AST(root->left);
  pf->codegen();

  // Print out all of the generated code.
  TheModule->print(llvm::errs(), nullptr);
  return 0;
}
