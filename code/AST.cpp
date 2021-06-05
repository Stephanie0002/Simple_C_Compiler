#include "AST.hpp"
#include <cassert>
#include <memory>
#include <stack>
#include <string>
#include <vector>

// Translation from tailored grammarTree to AST
// basically recursive descent

std::unique_ptr<VarDefAST> get_Decl_AST(const grammarTree *r, bool isGlbl) {
  const grammarTree *d1 = r->left, *vd;
  bool isConst = false;
  //! assumed int
  if (d1->name == "ConstDecl") {
    isConst = true;
    vd = d1->left->right->right;
  } else {
    assert(d1->name == "VarDecl");
    vd = d1->left->right;
  }

  std::vector<VarDefAST::VN> varnames;
  for (; vd; vd = vd->right) {
    auto pIDENT = vd->left;
    std::string id = pIDENT->content;
    std::unique_ptr<ExprAST> len, iv;
    auto pEQ = pIDENT->right;
    if (pEQ) {
      // simple
      if (pEQ->name == "=") {
        iv = get_Exp_AST(pEQ->right->left); // simple InitVal
      } else {
        // array
        assert(pEQ->name == "[");
        auto pCExp = pEQ->right;
        len = get_Exp_AST(pCExp);
        pEQ = pCExp->right->right;
        std::vector<std::unique_ptr<ExprAST>> civs;
        // InitVal given
        if (pEQ && pEQ->name == "=") {
          auto pIV = pEQ->right;
          for (auto pExp = pIV->left->right; pExp->name != "}";
               pExp = pExp->right) {
            civs.push_back(get_Exp_AST(pExp->left));
          }
        }
        iv = std::make_unique<BlockAST>(std::move(civs));
      }
    }
    varnames.push_back(VarDefAST::VN{id, std::move(len), std::move(iv)});
  }
  if (isGlbl) {
    return std::make_unique<GlblVarDefAST>(std::move(varnames), isConst);
  } else {
    return std::make_unique<VarDefAST>(std::move(varnames), isConst);
  }
}

std::unique_ptr<VariableExprAST> get_LVal_AST(const grammarTree *r) {
  auto pIDENT = r->left;
  // arr idx
  if (auto pBK = pIDENT->right) {
    if (pBK->name == "[") {
      auto pIdx = pBK->right;
      return std::make_unique<VariableExprAST>(pIDENT->content, get_Exp_AST(pIdx));
    }
  } else {
    // simple
    return std::make_unique<VariableExprAST>(pIDENT->content);
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
      out.push(get_LVal_AST(r));
    } else if (r->name == "NUMBER") {
      out.push(std::make_unique<NumberExprAST>(
          std::strtol(r->content.c_str(), nullptr, 10)));
    }
    // maintain postorder
    for (r = r->right; r; r = r->left) {
      //todo nasty we need to control the degree of trav
      if (string("[]{}").find(r->name) != string::npos)
        break;
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
  return std::make_unique<FunctionAST>(
      std::make_unique<PrototypeAST>(name, args), get_Block_AST(c->right));
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

std::unique_ptr<ExprAST> get_Stmt_AST(const grammarTree *item) {
  auto s1 = item->left;
  if (s1->name == "LVal") {
    return std::make_unique<VarAssignAST>(get_LVal_AST(s1),
                                          get_Exp_AST(s1->right->right));
  } else if (s1->name.rfind("Exp") != std::string::npos) {
    // contains "Exp"; ends_with will be more accurate but sufferred from OF
    return get_Exp_AST(s1);
  } else if (s1->name == "Block") {
    return get_Block_AST(s1);
  } else if (s1->name == "IF") {
    //! Stmt is nullable
    std::unique_ptr<ExprAST> Then, Else;
    auto pCOND = s1->right, p = pCOND->right;
    if (p->name == "Stmt") {
      Then = get_Stmt_AST(p);
      p = p->right;
    } 
    if (p && p->name == "ELSE") {
      p = p->right;
      if (p && p->name == "Stmt") {
        Else = get_Stmt_AST(p);
      }
    }
    return std::make_unique<IfAST>(get_Exp_AST(pCOND->left),
                                       std::move(Then), std::move(Else));
  } else if (s1->name == "WHILE") {
    std::unique_ptr<ExprAST> Body;
    auto pCOND = s1->right, p = pCOND->right;
    if (p && p->name == "Stmt") {
      Body = get_Stmt_AST(p);
    }
    return std::make_unique<WhileAST>(get_Exp_AST(pCOND->left),
                                      std::move(Body));
  } else if (s1->name == "BREAK") {
    return std::make_unique<GotoAST>("__WEND__");
  } else if (s1->name == "CONTINUE") {
    return std::make_unique<GotoAST>("__WHILE__");
  } else if (s1->name == "RETURN") {
    return std::make_unique<ReturnAST>(get_Exp_AST(s1->right));
  } else {
    assert(false);
  }
}

std::unique_ptr<BlockAST> get_Block_AST(const grammarTree *r) {
  // body
  std::vector<std::unique_ptr<ExprAST>> body;
  for (auto item = r->left; item; item = item->right) {
    if (item->name == "Stmt") {
      body.push_back(get_Stmt_AST(item));
    } else if (item->name == "Decl") {
      body.push_back(get_Decl_AST(item));
    } else {
      assert(false);
    }
  }
  return std::make_unique<BlockAST>(std::move(body));
}