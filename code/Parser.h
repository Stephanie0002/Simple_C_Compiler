#ifndef __PARSER__
#define __PARSER__

#include "grammarTree.h"
#include "Symbol.h"
#include "hashSet.h"
#include "utils.h"
#include <string>
#include <vector>
using namespace std;

bool checkProduction(const grammarTree *parent, int node_num, ...);
bool checkRepeatFuncDef(mySymbol *symb, int lineno);
void checkRepeatVarDef(mySymbol *symb, int lineno);
void checkArray(mySymbol *symb, int lineno);
void checkFuncRet(int lineno);
void checkFuncCall(string func_name, int lineno);
bool checkNotDef(string name, int lineno, string form);
void getDATA(myData *DATA, string name, string form);
void checkControl(int lineno, string type);

void addDomain(string domain_name, mySymbolType domain_type);
void addNewEleToArray(myData *new_ele, mySymbol *symb);
void addNewParamToParamList(myParam *new_param, myParam *param_list);

int semanticAnalysis(const grammarTree *root, bool verbose);
void semanticInit(const grammarTree *root);
// void analyseProgram(const syntaxTree *root);
void analyseCompUnit(const grammarTree *node);
void analyseDecl(const grammarTree *node);
void analyseConstDecl(const grammarTree *node);
void analyseConstDef_list(const grammarTree *node, myData *type);
myData *analyseBType(const grammarTree *node);
void analyseConstDef(const grammarTree *node, myData *type);
void analyseConstInitVal(const grammarTree *node, mySymbol *symb);
void analyseConstExp_list(const grammarTree *node, mySymbol *symb);
void analyseVarDecl(const grammarTree *node);
void analyseVarDef_list(const grammarTree *node, myData *type);
void analyseVarDef(const grammarTree *node, myData *type);
void analyseInitVal(const grammarTree *node, mySymbol *symb);
void analyseExp_list(const grammarTree *node, mySymbol *symb);
void analyseFuncDef(const grammarTree *node);
void analyseFuncFParams(const grammarTree *node, mySymbol *symb);
void analyseFuncFParam_list(const grammarTree *node, mySymbol *symb);
void analyseFuncFParam(const grammarTree *node, mySymbol *symb);
void analyseBlock(const grammarTree *node, mySymbol *symb);
void analyseBlockItem_list(const grammarTree *node, mySymbol *symb);
void analyseBlockItem(const grammarTree *node, mySymbol *symb);
void analyseStmt(const grammarTree *node, mySymbol *symb);
void analyseExp(const grammarTree *node, mySymbol *symb);
void analyseCond(const grammarTree *node, mySymbol *symb);
void analyseLVal(const grammarTree *node, mySymbol *symb);
void analysePrimaryExp(const grammarTree *node, mySymbol *symb);
void analyseUnaryExp(const grammarTree *node, mySymbol *symb);
void analyseUnaryOp(const grammarTree *node, mySymbol *symb);
void analyseFuncRParams(const grammarTree *node, mySymbol *symb);
void analyseAddExp(const grammarTree *node, mySymbol *symb);
void analyseMulExp(const grammarTree *node, mySymbol *symb);
void analyseRelExp(const grammarTree *node, mySymbol *symb);
void analyseEqExp(const grammarTree *node, mySymbol *symb);
void analyseLAndExp(const grammarTree *node, mySymbol *symb);
void analyseLOrExp(const grammarTree *node, mySymbol *symb);
void analyseConstExp(const grammarTree *node, mySymbol *symb);
void destroySymbolTable();

void printProductionError(const grammarTree *node, const char *msg);
int isNewSemanticError(int last_semantic_error_lineno);
void printSymbolTable(myHashSet symbol_table);
void printDomain();

#endif