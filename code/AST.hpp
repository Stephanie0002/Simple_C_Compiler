#ifndef AST_H
#define AST_H

#include "grammarTree.h"
#include "llvm/IR/Value.h"
#include <memory>
#include <stack>
#include <string>
#include <variant>
#include <vector>

using namespace llvm;

/* ExprAST - Base class for all ? nodes.
 * What is an expression? An expression can be evaluated, i.e. it has a value.
 */
class ExprAST {
public:
  virtual ~ExprAST() = default;

  virtual Value *codegen() = 0;
};

class VarDefAST;
class GlblVarDefAST;

/// BlockAST - contains a series of ExprAST; marks a new scope.
class BlockAST : public ExprAST {
  std::vector<std::unique_ptr<ExprAST>> items;

public:
  BlockAST(std::vector<std::unique_ptr<ExprAST>> items)
      : items(std::move(items)) {}

  Value *codegen() override;

  friend class VarDefAST;
  friend class GlblVarDefAST;
};

/// NumberExprAST - Expression class for numeric literals like "1".
class NumberExprAST : public ExprAST {
  int Val; // positive according to spec

public:
  NumberExprAST(int Val) : Val(Val) {}

  Value *codegen() override;
};

class VarAssignAST;

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  std::string Name;
  std::unique_ptr<ExprAST> idx; // array ref

public:
  VariableExprAST(const std::string &Name, std::unique_ptr<ExprAST> idx = nullptr)
      : Name(Name), idx(std::move(idx)) {}

  Value *codegen() override;
  const std::string &getName() const { return Name; }

  friend class VarAssignAST;
};

/// UnaryExprAST - Expression class for a unary operator.
class UnaryExprAST : public ExprAST {
  char Opcode;
  std::unique_ptr<ExprAST> Operand;

public:
  UnaryExprAST(char Opcode, std::unique_ptr<ExprAST> Operand)
      : Opcode(Opcode), Operand(std::move(Operand)) {}

  Value *codegen() override;
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  std::string Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(std::string Op, std::unique_ptr<ExprAST> LHS,
                std::unique_ptr<ExprAST> RHS)
      : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

  Value *codegen() override;
};

/* VarAssignAST - Expression class for "a = 1"
 * "a = b = 1" is not allowed, but we leave it here.
 */
class VarAssignAST : public ExprAST {
  std::unique_ptr<VariableExprAST> LHS;
  std::unique_ptr<ExprAST> RHS;

public:
  VarAssignAST(std::unique_ptr<VariableExprAST> LHS,
               std::unique_ptr<ExprAST> RHS)
      : LHS(std::move(LHS)), RHS(std::move(RHS)) {}

  Value *codegen() override;
};

/// ReturnAST - class for "return a+b"
class ReturnAST : public ExprAST {
  std::unique_ptr<ExprAST> RHS;

public:
  ReturnAST(std::unique_ptr<ExprAST> RHS) : RHS(std::move(RHS)) {}

  Value *codegen() override;
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const std::string &Callee,
              std::vector<std::unique_ptr<ExprAST>> Args)
      : Callee(Callee), Args(std::move(Args)) {}

  Value *codegen() override;
};

/// IfAST - class for if/then/else.
class IfAST : public ExprAST {
  std::unique_ptr<ExprAST> Cond, Then, Else;

public:
  IfAST(std::unique_ptr<ExprAST> Cond, std::unique_ptr<ExprAST> Then,
            std::unique_ptr<ExprAST> Else)
      : Cond(std::move(Cond)), Then(std::move(Then)), Else(std::move(Else)) {}

  Value *codegen() override;
};

/// WhileAST - class for while (1) {}
class WhileAST : public ExprAST {
  std::unique_ptr<ExprAST> End, Body;

public:
  WhileAST(std::unique_ptr<ExprAST> End, std::unique_ptr<ExprAST> Body)
      : End(std::move(End)), Body(std::move(Body)) {}

  Value *codegen() override;
};

/// GotoAST - class covering break and continue
class GotoAST : public ExprAST {
  std::string label;

public:
  GotoAST(std::string label) : label(label) {}

  Value *codegen() override;
};

/* VarDefAST - Expression class for "int a = 1"
 * The return value is not usable.
 */
class VarDefAST : public ExprAST {
public:
  struct VN {
    std::string Name;
    std::unique_ptr<ExprAST> len; // nullptr means simple;
    std::unique_ptr<ExprAST> iv;  // For array, it owns BlockAST
  };

protected:
  std::vector<VN> VarNames;
  bool isConst;

public:
  VarDefAST(std::vector<VN> VarNames, bool isConst = false)
      : VarNames(std::move(VarNames)), isConst(isConst) {}

  Value *codegen() override;
};

/// Global Variable needs different codegen
class GlblVarDefAST : public VarDefAST {
public:
  GlblVarDefAST(std::vector<VN> VarNames, bool isConst = false)
      : VarDefAST(std::move(VarNames), isConst) {}
  
  Value *codegen() override;
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;

public:
  PrototypeAST(const std::string &Name, std::vector<std::string> Args)
      : Name(Name), Args(std::move(Args)) {}

  Function *codegen();
  const std::string &getName() const { return Name; }
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<BlockAST> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<BlockAST> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {}

  Function *codegen();
};

std::vector<
    std::variant<std::unique_ptr<FunctionAST>, std::unique_ptr<ExprAST>>>
proc_CompUnit(const grammarTree *r);
std::unique_ptr<FunctionAST> get_FuncDef_AST(const grammarTree *r);
std::unique_ptr<VarDefAST> get_Decl_AST(const grammarTree *r,
                                        bool isGlbl = false);
std::unique_ptr<ExprAST> get_Stmt_AST(const grammarTree *r);
std::unique_ptr<BlockAST> get_Block_AST(const grammarTree *r);
std::unique_ptr<ExprAST> get_Exp_AST(const grammarTree *r);
std::unique_ptr<VariableExprAST> get_LVal_AST(const grammarTree *r);
std::unique_ptr<BinaryExprAST>
get_BinExpr_AST(const grammarTree *r,
                std::stack<std::unique_ptr<ExprAST>> &out);

#endif