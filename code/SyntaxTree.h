#ifndef _SYNTAXTREE_H
#define _SYNTAXTREE_H

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

struct syntaxTree
{
    const char *name;
    const char *content;
    int lineno;
    int id = -1;
    struct syntaxTree *left;
    struct syntaxTree *right;
};

struct syntaxTree *createSyntaxTree(const char *name, int num, ...);
struct syntaxTree *addNullNode(const char *name, int lineno, int col);
void destroySyntaxTree(syntaxTree *node);
void floorTraverse(syntaxTree *root);
void nodePrint(syntaxTree *root, string out_name, bool verbose);

#endif