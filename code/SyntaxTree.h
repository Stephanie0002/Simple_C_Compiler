#ifndef _SYNTAXTREE_H
#define _SYNTAXTREE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <queue>
#include <fstream>
#include "utils.h"

using namespace std;

extern char *yytext;
extern int yylineno;

struct syntaxTree
{
    string name;
    string content;
    int lineno;
    int id = -1;
    struct syntaxTree *left;
    struct syntaxTree *right;
    // prep for tailor; classified on Nb_opr
    using Type_t = enum { BinExpr,
                          List,
                          Garbage,
                          NA };
    Type_t type()
    {
        if (string(",;none").find(name) != string::npos)
        {
            return Garbage;
        }
        else if (name.find("list") != string::npos)
        {
            return List;
        }
        else
        {
            for (string &&s : {"AddExp", "MulExp", "RelExp", "EqExp", "LAndExp", "LOrExp"})
            {
                if (name == s)
                {
                    return BinExpr;
                }
            }
            return NA;
        }
    }
    bool orphan() { return right == nullptr; }
    int nb_child()
    {
        int cnt = 0;
        if (auto c = left)
        {
            while (c)
            {
                cnt++;
                c = c->right;
            }
        }
        return cnt;
    }
    syntaxTree *fold_lchain()
    {
        syntaxTree *rv = this->left;
        // rebuild sibling ptr
        syntaxTree *sib = rv;
        while (sib->right)
        {
            sib = sib->right;
        }
        sib->right = this->right;
        // isolate & delete
        this->left = this->right = nullptr;
        delete this;
        return rv;
    }
    syntaxTree *fold_rchain()
    {
        syntaxTree *rv = this->right;
        this->left = this->right = nullptr;
        delete this;
        return rv;
    }
    syntaxTree *tailor();
    // cascading deletion
    ~syntaxTree()
    {
        delete left;
        delete right;
    }
};

syntaxTree *createSyntaxTree(string name, int num, ...);
syntaxTree *addNullNode(string name, int lineno, int col);
void destroySyntaxTree(syntaxTree *node);
void floorTraverse(syntaxTree *root);
void nodePrint(syntaxTree *root, string out_name, bool verbose);

#endif