#ifndef AST_H
#define AST_H

#include "grammarTree.h"
#include "llvm/IR/Value.h"
#include <cassert>
#include <memory>
#include <stack>
#include <string>
#include <vector>

using namespace llvm;

/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() = default;

  virtual Value *codegen() = 0;
};

/// NumberExprAST - Expression class for numeric literals like "1".
class NumberExprAST : public ExprAST {
  int Val;

public:
  NumberExprAST(int Val) : Val(Val) {}

  Value *codegen() override;
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {}

  Value *codegen() override;
  const std::string &getName() const { return Name; }
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

/// VarAssignAST - Expression class for "a = 1"
class VarAssignAST : public ExprAST {
  std::string VarName;
  std::unique_ptr<ExprAST> RHS;

public:
  VarAssignAST(std::string VarName, std::unique_ptr<ExprAST> RHS)
      : VarName(std::move(VarName)), RHS(std::move(RHS)) {}

  Value *codegen() override;
};

/// ReturnAST - Expression class for "return a+b"
class ReturnExprAST : public ExprAST {
  std::unique_ptr<ExprAST> RHS;

public:
  ReturnExprAST(std::unique_ptr<ExprAST> RHS) : RHS(std::move(RHS)) {}

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

/// IfExprAST - Expression class for if/then/else.
class IfExprAST : public ExprAST {
  std::unique_ptr<ExprAST> Cond, Then, Else;

public:
  IfExprAST(std::unique_ptr<ExprAST> Cond, std::unique_ptr<ExprAST> Then,
            std::unique_ptr<ExprAST> Else)
      : Cond(std::move(Cond)), Then(std::move(Then)), Else(std::move(Else)) {}

  Value *codegen() override;
};

/// VarDefAST - Expression class for "int a = 1"
class VarDefAST : public ExprAST {
  std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> VarNames;

public:
  VarDefAST(
      std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> VarNames)
      : VarNames(std::move(VarNames)) {}

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
  std::vector<std::unique_ptr<ExprAST>> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::vector<std::unique_ptr<ExprAST>> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {}

  Function *codegen();
};

std::unique_ptr<FunctionAST> get_FuncDef_AST(const grammarTree *r);
std::unique_ptr<VarDefAST> get_Decl_AST(const grammarTree *r);
std::unique_ptr<ExprAST> get_Exp_AST(const grammarTree *r);
std::unique_ptr<BinaryExprAST>
get_BinExpr_AST(const grammarTree *r,
                std::stack<std::unique_ptr<ExprAST>> &out);

#endif