#include "IRgen.hpp"
#include <memory>

using namespace llvm;

auto TestCase() {
  auto r = std::make_unique<FunctionAST>()
}

int main(int argc, char *argv[]) {
  auto TheContext = std::make_unique<LLVMContext>();
  // Make the module, which holds all the code.
  TheModule = std::make_unique<Module>("my cool jit", *TheContext);
  // Create a new builder for the module.
  Builder = std::make_unique<IRBuilder<>>(*TheContext);

  // Run the main "interpreter loop" now.
//   MainLoop();

  // Print out all of the generated code.
  TheModule->dump();
  return 0;
}

