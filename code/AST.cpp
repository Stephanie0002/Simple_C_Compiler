#include "AST.hpp"
#include <cassert>
#include <memory>
#include <stack>
#include <string>
#include <vector>

// TODO IF WHILE BREAK CONT 函数 数组索引 short-circuit

// Translation from tailored grammarTree to AST

std::unique_ptr<VarDefAST> get_Decl_AST(const grammarTree *r, bool isGlbl) {
  auto d1 = r->left;
  if (d1->name == "VarDecl") {
    std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> varnames;
    //! assumed int
    for (auto vd = d1->left->right; vd; vd = vd->right) {
      auto pIDENT = vd->left;
      std::string id = pIDENT->content;
      std::unique_ptr<ExprAST> iv;
      auto pEQ = pIDENT->right;
      if (pEQ && pEQ->name == "=") {
        iv = std::move(get_Exp_AST(pEQ->right)); // todo array
      }
      varnames.push_back(std::make_pair(id, std::move(iv)));
    }
    if (isGlbl) {
      return std::make_unique<GlblVarDefAST>(std::move(varnames));
    } else {
      return std::make_unique<VarDefAST>(std::move(varnames));
    }
  } else {
    assert(false);
  }
}

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
        out.push(std::make_unique<CallExprAST>(callee, std::move(args)));
      }
      // !0x0
      else {
        assert(u1->name == "UnaryOp");
        auto opr = std::move(out.top());
        out.pop();
        out.push(
            std::make_unique<UnaryExprAST>(u1->left->name[0], std::move(opr)));
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
  assert(out.size() == 1);
  return std::move(out.top());
}

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
  std::vector<std::unique_ptr<ExprAST>> body;
  c = c->right; // Block
  for (auto item = c->left; item; item = item->right) {
    if (item->name == "Stmt") {
      auto s1 = item->left;
      if (s1->name == "LVal") {
        body.push_back(std::make_unique<VarAssignAST>(s1->left->content,
                                                      get_Exp_AST(s1->right)));
      }
      // ends_with "Exp"
      else if (s1->name.rfind("Exp") == s1->name.length() - 3) {
        body.push_back(get_Exp_AST(s1));
      } else if (s1->name == "RETURN") {
        body.push_back(std::make_unique<ReturnExprAST>(get_Exp_AST(s1->right)));
      } else {
        assert(false);
      }
    } else {
      assert(item->name == "Decl");
      body.push_back(get_Decl_AST(item));
    }
  }
  return std::make_unique<FunctionAST>(std::move(proto), std::move(body));
}

std::vector<
    std::variant<std::unique_ptr<FunctionAST>, std::unique_ptr<ExprAST>>>
proc_CompUnit(const grammarTree *r) {
  std::vector<
      std::variant<std::unique_ptr<FunctionAST>, std::unique_ptr<ExprAST>>>
      q;
  for (auto c = r->left; c; c = c->right) {
    if (c->name == "Decl") {
      q.push_back(get_Decl_AST(c, true));
    } else {
      assert(c->name == "FuncDef");
      q.push_back(get_FuncDef_AST(c));
    }
  }
  return q;
}