#ifndef _GRAMMARTREE_H
#define _GRAMMARTREE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <iostream>
#include <string>
#include <queue>
#include <fstream>

extern char *yytext;
extern int yylineno;

using namespace std;

struct grammarTree
{
    string content;
    string name;
    int lineno;
    int id = -1;
    struct grammarTree *left; // 1st child
    struct grammarTree *right; // next sibling
    // prep for tailor; classified on Nb_opr
    using Type_t = enum { BinExpr, List, Garbage, NA };
    Type_t type() const {
      if (string("(),;none").find(name) != string::npos) {
        return Garbage;
      } else if (name.find("list") != string::npos) {
        return List;
      } else {
        for (string &&s : {"AddExp", "MulExp", "RelExp", "EqExp", "LAndExp", "LOrExp"}) {
          if (name == s) {
            return BinExpr;
          }
        }
        return NA;
      }
    }
    bool orphan() { return right == nullptr; }
    int nb_child() {
      int cnt = 0;
      if (auto c = left) {
        while (c) {
          cnt++;
          c = c->right;
        }
      }
      return cnt;
    }
    grammarTree *fold_lchain() {
      grammarTree *rv = this->left;
      // rebuild sibling ptr
      grammarTree *sib = rv;
      while (sib->right) {
        sib = sib->right;
      }
      sib->right = this->right;
      // isolate & delete
      this->left = this->right = nullptr;
      delete this;
      return rv;
    }
    grammarTree *fold_rchain() {
      grammarTree *rv = this->right;
      this->left = this->right = nullptr;
      delete this;
      return rv;
    }
    grammarTree *tailor();
    // cascading deletion
    ~grammarTree() {
      delete left;
      delete right;
    }
};

extern struct grammarTree *root;

struct grammarTree *createTree(string name, int num, ...);
void outputTree(grammarTree *root, int level);
void floorPrint(grammarTree *root, string filename, bool verbose);
void nodePrint(grammarTree *root, string filename, bool verbose);

#endif
