#include "grammarTree.h"
#include "llvm/IR/Value.h"
#include <cassert>
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <variant>
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
  std::unique_ptr<ExprAST> Body;

public:
  VarDefAST(
      std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> VarNames,
      std::unique_ptr<ExprAST> Body)
      : VarNames(std::move(VarNames)), Body(std::move(Body)) {}

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
  std::unique_ptr<ExprAST> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<ExprAST> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {}

  Function *codegen();
};

std::unique_ptr<BinaryExprAST>
get_BinExpr_AST(const grammarTree *r,
                std::stack<std::unique_ptr<ExprAST>> &out) {
  auto rhs = std::move(out.top());
  out.pop();
  auto lhs = std::move(out.top());
  out.pop();
  auto op = r->left->right->name;
  return std::make_unique<BinaryExprAST>(op, std::move(lhs), std::move(rhs));
}

std::unique_ptr<ExprAST> get_Exp_AST(const grammarTree *r) {
  assert(r->name.rfind("Exp") == r->name.length() - 3); // ends_with
  // postorder: proc child from left to right, before root
  std::stack<const grammarTree *> in;
  std::stack<std::unique_ptr<ExprAST>> out;
  // maintain postorder
  while (r) {
    in.push(r);
    r = r->left;
  }
  while (!in.empty()) {
    r = in.top();
    in.pop();
    // proc r
    if (r->type() == grammarTree::BinExpr) {
      out.push(get_BinExpr_AST(r, out));
    } else if (r->name == "UnaryExp") {
      auto u1 = r->left;
      // func(rp)
      if (u1->name == "IDENT") {
        auto callee = u1->content;
        auto nb_args = u1->right->nb_child();
        std::vector<std::unique_ptr<ExprAST>> args(nb_args);
        // last rparam on the top
        for (size_t i = nb_args; i != 0; i--) {
          args[i - 1] = std::move(out.top());
          out.pop();
        }
        out.push(std::make_unique<CallExprAST>(callee, args));
      }
      // !0x0
      else {
        assert(u1->name == "UnaryOp");
        auto opr = std::move(out.top());
        out.pop();
        out.push(
            std::make_unique<UnaryExprAST>(u1->left->name, std::move(opr)));
      }
    }
    // terminal AST gen
    else if (r->name == "LVal") {
      out.push(std::make_unique<VariableExprAST>(r->left->content));
    } else if (r->name == "NUMBER") {
      out.push(std::make_unique<NumberExprAST>(
          std::strtol(r->content.c_str(), nullptr, 10)));
    }
    // maintain postorder
    for (r = r->right; r; r = r->left) {
      in.push(r);
    }
  }

}

/*
      std::variant<>, std::unique_ptr<PrototypeAST>,
                   std::unique_ptr<FunctionAST> */

std::unique_ptr<FunctionAST> get_FuncDef_AST(const grammarTree *r) {
  assert(r->name == "FuncDef");
  // proto
  //! assumed int
  auto c = r->left;
  c = c->right; // IDENT
  auto name = c->content;
  c = c->right; // FParams
  std::vector<std::string> args;
  for (auto fparam = c->left; fparam; fparam = fparam->right) {
    args.push_back(fparam->left->right->content);
  }
  auto proto = std::make_unique<PrototypeAST>(name, args);
  // body
  c = c->right; // Block
  for (auto item = c->left; item; item = item->right) {
    if (item->name == "Stmt") {
      auto s1 = item->left;

    } else {
      assert(item->name == "Decl");
    }
  }
}

/*

 */