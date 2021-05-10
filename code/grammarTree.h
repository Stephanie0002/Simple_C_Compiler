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
    struct grammarTree *left;
    struct grammarTree *right;
};

extern struct grammarTree *root;

struct grammarTree *createTree(string name, int num, ...);
void outputTree(grammarTree *root, int level);
void floorPrint(grammarTree *root, bool verbose);
void Clean(grammarTree *node);

#endif
