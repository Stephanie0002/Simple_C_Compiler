#include "AST.hpp"
#include "IRgen.hpp"
#include <memory>

using namespace llvm;

int IR_entry(const grammarTree *root) {
  auto TheContext = std::make_unique<LLVMContext>();
  // Make the module, which holds all the code.
  TheModule = std::make_unique<Module>("my cool jit", *TheContext);
  // Create a new builder for the module.
  Builder = std::make_unique<IRBuilder<>>(*TheContext);

  // Run the main "interpreter loop" now.
//   MainLoop();
  auto pf = get_FuncDef_AST(root->left);
  pf->codegen();

  // Print out all of the generated code.
  TheModule->dump();
  return 0;
}
