#ifndef __PARSER__
#define __PARSER__

#include "syntaxTree.h"
#include "Symbol.h"
#include "hashSet.h"
#include "utils.h"
using namespace std;

bool checkProduction(const syntaxTree *parent, int node_num, ...);

void semanticAnalysis(const syntaxTree *root);
void semanticInit(const syntaxTree *root);
void analyseProgram(const syntaxTree *root);
void analyseCompUnit(const syntaxTree *node);
void analyseDecl(const syntaxTree *node);
void analyseConstDecl(const syntaxTree *node);
void analyseConstDef_list(const syntaxTree *node);
void analyseBType(const syntaxTree *node);
void analyseConstDef(const syntaxTree *node);
void analyseConstInitVal(const syntaxTree *node);
void analyseConstExp_list(const syntaxTree *node);
void analyseVarDecl(const syntaxTree *node);
void analyseVarDef_list(const syntaxTree *node);
void analyseVarDef(const syntaxTree *node);
void analyseInitVal(const syntaxTree *node);
void analyseExp_list(const syntaxTree *node);
void analyseFuncDef(const syntaxTree *node);
void analyseFuncFParams(const syntaxTree *node);
void analyseFuncFParam_list(const syntaxTree *node);
void analyseFuncFParam(const syntaxTree *node);
void analyseBlock(const syntaxTree *node);
void analyseBlockItem_list(const syntaxTree *node);
void analyseBlockItem(const syntaxTree *node);
void analyseStmt(const syntaxTree *node);
void analyseExp(const syntaxTree *node);
void analyseCond(const syntaxTree *node);
void analyseLVal(const syntaxTree *node);
void analysePrimaryExp(const syntaxTree *node);
void analyseUnaryExp(const syntaxTree *node);
void analyseUnaryOp(const syntaxTree *node);
void analyseFuncRParams(const syntaxTree *node);
void analyseAddExp(const syntaxTree *node);
void analyseMulExp(const syntaxTree *node);
void analyseRelExp(const syntaxTree *node);
void analyseEqExp(const syntaxTree *node);
void analyseLAndExp(const syntaxTree *node);
void analyseLOrExp(const syntaxTree *node);
void analyseConstExp(const syntaxTree *node);

void printSemanticError(int error_type, int lineno, int col, char *msg);
void printProductionError(const syntaxTree *node, const char *msg);
void printSymbolTable(myHashSet symbol_table);

#endif