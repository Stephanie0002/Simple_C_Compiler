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
    const char *name;
    const char *content;
    int lineno;
    int id = -1;
    struct syntaxTree *left;
    struct syntaxTree *right;
};

syntaxTree *createSyntaxTree(const char *name, int num, ...);
syntaxTree *addNullNode(const char *name, int lineno, int col);
void destroySyntaxTree(syntaxTree *node);
void floorTraverse(syntaxTree *root);
void nodePrint(syntaxTree *root, string out_name, bool verbose);

#endif