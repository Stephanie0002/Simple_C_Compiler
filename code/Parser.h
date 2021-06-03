#ifndef __PARSER__
#define __PARSER__

#include "syntaxTree.h"
#include "Symbol.h"
#include "hashSet.h"
#include "utils.h"
#include <string>
using namespace std;

bool checkProduction(const syntaxTree *parent, int node_num, ...);
bool checkType(myData *t1, myData *t2);
bool checkArgs(myParam *args, myParam *params, int param_num);
void checkArray(mySymbol *symb);

void addNewEleToArray(myData *new_ele, mySymbol *symb);
void addNewParamToFunc(myParam *new_param, mySymbol *symb);

void semanticAnalysis(const syntaxTree *root);
void semanticInit(const syntaxTree *root);
// void analyseProgram(const syntaxTree *root);
void analyseCompUnit(const syntaxTree *node);
void analyseDecl(const syntaxTree *node);
void analyseConstDecl(const syntaxTree *node);
void analyseConstDef_list(const syntaxTree *node, myData *type);
myData *analyseBType(const syntaxTree *node);
void analyseConstDef(const syntaxTree *node, myData *type);
void analyseConstInitVal(const syntaxTree *node, mySymbol *symb);
void analyseConstExp_list(const syntaxTree *node, mySymbol *symb);
void analyseVarDecl(const syntaxTree *node);
void analyseVarDef_list(const syntaxTree *node, myData *type);
void analyseVarDef(const syntaxTree *node, myData *type);
void analyseInitVal(const syntaxTree *node, mySymbol *symb);
void analyseExp_list(const syntaxTree *node, mySymbol *symb);
void analyseFuncDef(const syntaxTree *node);
void analyseFuncFParams(const syntaxTree *node, mySymbol *symb);
void analyseFuncFParam_list(const syntaxTree *node, mySymbol *symb);
void analyseFuncFParam(const syntaxTree *node, mySymbol *symb);
void analyseBlock(const syntaxTree *node, mySymbol *symb);
void analyseBlockItem_list(const syntaxTree *node, mySymbol *symb);
void analyseBlockItem(const syntaxTree *node, mySymbol *symb);
void analyseStmt(const syntaxTree *node, mySymbol *symb);
void analyseExp(const syntaxTree *node, mySymbol *symb);
void analyseCond(const syntaxTree *node, mySymbol *symb);
void analyseLVal(const syntaxTree *node, mySymbol *symb);
void analysePrimaryExp(const syntaxTree *node, mySymbol *symb);
void analyseUnaryExp(const syntaxTree *node, mySymbol *symb);
void analyseUnaryOp(const syntaxTree *node, mySymbol *symb);
void analyseFuncRParams(const syntaxTree *node, mySymbol *symb);
void analyseAddExp(const syntaxTree *node, mySymbol *symb);
void analyseMulExp(const syntaxTree *node, mySymbol *symb);
void analyseRelExp(const syntaxTree *node, mySymbol *symb);
void analyseEqExp(const syntaxTree *node, mySymbol *symb);
void analyseLAndExp(const syntaxTree *node, mySymbol *symb);
void analyseLOrExp(const syntaxTree *node, mySymbol *symb);
void analyseConstExp(const syntaxTree *node, mySymbol *symb);
void destroySymbolTable();

void printProductionError(const syntaxTree *node, const char *msg);
void printSymbolTable(myHashSet symbol_table);

#endif