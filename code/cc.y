/* declarations */
%{
#include <cstdlib>
#include <cstdio>
#include <string>

#include "grammarTree.h"

using namespace std;

extern char *yytext;
extern int yycolumn;
extern FILE *yyin;
extern FILE *yyout;
grammarTree *root;
extern int yylineno;

int yylex(void);
void yyerror(const char *);
extern int IR_entry(const grammarTree *root);
%}

%union {
    struct grammarTree* tree;
}

%token <tree> NUMBER CONST IDENT
%token <tree> INT
%token <tree> IF ELSE WHILE BREAK CONTINUE RETURN
%token <tree> '+' '-' '*' '/' '%' '<' '>' '!' '='
%token <tree> LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP 
%token <tree> ';' ',' '[' ']' '(' ')' '{' '}'

%type <tree> CompUnit Decl 
%type <tree> ConstDecl VarDecl ConstDef ConstInitVal ConstExp
%type <tree> VarDef InitVal
%type <tree> Exp PrimaryExp UnaryExp LVal AddExp LOrExp UnaryOp MulExp RelExp EqExp LAndExp
%type <tree> FuncDef FuncFParam FuncFParams FuncRParams BType
%type <tree> Block BlockItem
%type <tree> ConstDef_list ConstExp_list VarDef_list Exp_list FuncFParam_list BlockItem_list
%type <tree> Stmt Cond

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%
/* rules */

// 编译单元
CompUnit: 
        CompUnit Decl{ root = $$ = createTree("CompUnit", 2, $1, $2);}
    |   Decl{ root = $$ = createTree("CompUnit", 1, $1);}
    |   CompUnit FuncDef{ root = $$ = createTree("CompUnit", 2, $1, $2);}
    |   FuncDef{ root = $$ = createTree("CompUnit", 1, $1);}
    ;

// 声明
Decl: 
        ConstDecl{$$ = createTree("Decl", 1, $1);}
    |   VarDecl{$$ = createTree("Decl", 1, $1);}
    ;

// 常量声明
ConstDecl:
        CONST BType ConstDef ConstDef_list ';'{$$ = createTree("ConstDecl", 5, $1, $2, $3, $4, $5);}
    ;

ConstDef_list:
        ConstDef_list ',' ConstDef{$$ = createTree("ConstDef_list", 3, $1, $2, $3);}
    |   {$$ = createTree("ConstDef_list", -1, yylineno);}
    ;

// 基本类型
BType:
        INT{$$ = createTree("BType", 1, $1);}
    ;

// 常数定义
ConstDef:
        IDENT '=' ConstInitVal{$$ = createTree("ConstDef", 3, $1, $2, $3);}
    |   IDENT '[' ConstExp ']' '=' ConstInitVal{$$ = createTree("ConstDef", 6, $1, $2, $3, $4, $5, $6);}
    ;

// 常量初值
ConstInitVal:
        ConstExp{$$ = createTree("ConstInitVal", 1, $1);}
    |   '{' '}'{$$ = createTree("ConstInitVal", 2, $1, $2);}
    |   '{' ConstExp ConstExp_list '}'{$$ = createTree("ConstInitVal", 4, $1, $2, $3, $4);}
    ;
ConstExp_list:
        ConstExp_list ',' ConstExp{$$ = createTree("ConstExp_list", 3, $1, $2, $3);}
    |   {$$ = createTree("ConstExp_list", -1, yylineno);}
    ;

// 变量声明
VarDecl:
        BType VarDef VarDef_list ';'{$$ = createTree("VarDecl", 4, $1, $2, $3, $4);}
    ;

VarDef_list:
        VarDef_list ',' VarDef{$$ = createTree("VarDef_list", 3, $1, $2, $3);}
    |   {$$ = createTree("VarDef_list", -1, yylineno);}
    ;

// 变量定义
VarDef: 
        IDENT{$$ = createTree("VarDef", 1, $1);}
    |   IDENT '[' ConstExp ']'{$$ = createTree("VarDef", 4, $1, $2, $3, $4);}
    |   IDENT '=' InitVal{$$ = createTree("VarDef", 3, $1, $2, $3);}
    |   IDENT '[' ConstExp ']' '=' InitVal{$$ = createTree("VarDef", 6, $1, $2, $3, $4, $5, $6);}
    ;

// 变量初值
InitVal:
        Exp{$$ = createTree("InitVal", 1, $1);}
    |   '{' '}'{$$ = createTree("InitVal", 2, $1, $2);}
    |   '{' Exp Exp_list '}'{$$ = createTree("InitVal", 4, $1, $2, $3, $4);}
    ;

Exp_list:
        Exp_list ',' Exp{$$ = createTree("Exp_list", 3, $1, $2, $3);}
    |   {$$ = createTree("Exp_list", -1, yylineno);}
    ;

// 函数定义
FuncDef:
        BType IDENT '(' FuncFParams ')' Block{$$ = createTree("FuncDef", 6, $1, $2, $3, $4, $5, $6);}
    ;

// 函数形参表
FuncFParams: 
        FuncFParam FuncFParam_list{$$ = createTree("FuncFParams", 2, $1, $2);}
    |   {$$ = createTree("FuncFParams", -1, yylineno);}
    ;

FuncFParam_list:
        FuncFParam_list ',' FuncFParam{$$ = createTree("FuncFParam_list", 3, $1, $2, $3);}
    |   {$$ = createTree("FuncFParam_list", -1, yylineno);}
    ;

// 函数形参
FuncFParam:
        BType IDENT{$$ = createTree("FuncFparam", 2, $1, $2);}
    |   BType IDENT '[' ']'{$$ = createTree("FuncFparam", 4, $1, $2, $3, $4);}
    ;

// 语句块
Block:
        '{' BlockItem_list '}'{$$ = createTree("Block", 3, $1, $2, $3);}
    ;
    
BlockItem_list:
    BlockItem_list BlockItem{$$ = createTree("BlockItem_list", 2, $1, $2);}
    |   {$$ = createTree("BlockItem_list", -1, yylineno);}
    ;

// 语句块项
BlockItem:
        Decl{$$ = createTree("BlockItem", 1, $1);} 
    |   Stmt{$$ = createTree("BlockItem", 1, $1);}
    ;

// 语句
Stmt:
        LVal '=' Exp ';'{$$ = createTree("Stmt", 4, $1, $2, $3, $4);}
    |   Exp ';'{$$ = createTree("Stmt", 2, $1, $2);}
    |   ';'{$$ = createTree("Stmt", 1, $1);}
    |   Block{$$ = createTree("Stmt", 1, $1);}
    |   IF '(' Cond ')' Stmt{$$ = createTree("Stmt", 5, $1, $2, $3, $4, $5);}
    |   IF '(' Cond ')' Stmt ELSE Stmt{$$ = createTree("Stmt", 7, $1, $2, $3, $4, $5, $6, $7);}
    |   WHILE '(' Cond ')' Stmt{$$ = createTree("Stmt", 5, $1, $2, $3, $4, $5);}
    |   BREAK ';'{$$ = createTree("Stmt", 2, $1, $2);}
    |   CONTINUE ';'{$$ = createTree("Stmt", 2, $1, $2);}
    |   RETURN Exp ';'{$$ = createTree("Stmt", 3, $1, $2, $3);}
    ;

// 表达式
Exp:
        AddExp{$$ = createTree("Exp", 1, $1);}
    ;

// 条件表达式
Cond:
        LOrExp{$$ = createTree("Cond", 1, $1);}
    ;

// 左值表达式
LVal: 
        IDENT{$$ = createTree("LVal", 1, $1);}
    |   IDENT '[' Exp ']'{$$ = createTree("LVal", 4, $1, $2, $3, $4);}
    ;

// 基本表达式
PrimaryExp:
        '(' Exp ')'{$$ = createTree("PrimaryExp", 3, $1, $2, $3);}
    |   LVal{$$ = createTree("PrimaryExp", 1, $1);}
    |   NUMBER{$$ = createTree("PrimaryExp", 1, $1);}
    ;

// 一元表达式
UnaryExp:
        PrimaryExp{$$ = createTree("UnaryExp", 1, $1);}
    |   IDENT '(' FuncRParams ')'{$$ = createTree("UnaryExp", 4, $1, $2, $3, $4);}
    |   UnaryOp UnaryExp{$$ = createTree("UnaryExp", 2, $1, $2);}
    ;

// 单目运算符
UnaryOp:
        '+'{$$ = createTree("UnaryOP", 1, $1);}
    |   '-'{$$ = createTree("UnaryOP", 1, $1);}
    |   '!'{$$ = createTree("UnaryOP", 1, $1);}
    ;

// 函数实参表
FuncRParams:
        Exp Exp_list{$$ = createTree("FuncRParams", 2, $1, $2);}
    |   {$$ = createTree("FuncRParams", -1, yylineno);}
    ;

// 加减表达式
AddExp: 
        MulExp{$$ = createTree("AddExp", 1, $1);}
    |   AddExp '+' MulExp{$$ = createTree("AddExp", 3, $1, $2, $3);}
    |   AddExp '-' MulExp{$$ = createTree("AddExp", 3, $1, $2, $3);}
    ;

// 乘除模表达式
MulExp:
        UnaryExp{$$ = createTree("MulExp", 1, $1);}
    |   MulExp '*' UnaryExp{$$ = createTree("MulExp", 3, $1, $2, $3);}
    |   MulExp '/' UnaryExp{$$ = createTree("MulExp", 3, $1, $2, $3);}
    |   MulExp '%' UnaryExp{$$ = createTree("MulExp", 3, $1, $2, $3);}
    ;

// 关系表达式
RelExp:
        AddExp{$$ = createTree("RelExp", 1, $1);}
    |   RelExp '<' AddExp{$$ = createTree("RelExp", 3, $1, $2, $3);}
    |   RelExp '>' AddExp{$$ = createTree("RelExp", 3, $1, $2, $3);}
    |   RelExp LE_OP AddExp{$$ = createTree("RelExp", 3, $1, $2, $3);}
    |   RelExp GE_OP AddExp{$$ = createTree("RelExp", 3, $1, $2, $3);}
    ;

// 相等性表达式
EqExp:
        RelExp{$$ = createTree("EqExp", 1, $1);}
    |   EqExp EQ_OP RelExp{$$ = createTree("EqExp", 3, $1, $2, $3);}
    |   EqExp NE_OP RelExp{$$ = createTree("EqExp", 3, $1, $2, $3);}
    ;

// 逻辑与表达式
LAndExp:
        EqExp{$$ = createTree("LAndExp", 1, $1);}
    |   LAndExp AND_OP EqExp{$$ = createTree("LAndExp", 3, $1, $2, $3);}
    ;

// 逻辑或表达式
LOrExp:
        LAndExp{$$ = createTree("LOrExp", 1, $1);}
    |   LOrExp OR_OP LAndExp{$$ = createTree("LOrExp", 3, $1, $2, $3);}
    ;

// 表达式
ConstExp:
        AddExp{$$ = createTree("ConstExp", 1, $1);}
    ;
%%

/* programs */
/* allows for printing of an error message */
void yyerror(char const *s)
{
	fflush(stdout);
	printf("\nRow No.%d, Col No.%d: [Yacc]%s\n", yylineno, yycolumn, s);
    exit(0);
}

int main(int argc, char* argv[]) {
    /* Read test file from command line */
    bool verbose = false;
    string tmp = argv[1];
    if (tmp == "true"){
        verbose = true;
    }
    
    int start = 1;
    if (tmp != "true" || tmp != "false"){
        start = 2;
    }
    
    if (verbose){
        for (int i=1; i<argc; i++){
            cout << "Argument " << i << " is " << argv[i] << endl;
        }
    }

    for (int i=start; i<argc; i++){
        string filename = argv[i];
        yyin = fopen(argv[i], "r");
        
        printf("\nThe source code of %s is:\n ", argv[i]);
        yyparse();

        grammarTree* tmp = root;
        // if (verbose)
        //     outputTree(root, 0);
        root->tailor();
        floorPrint(root, filename, verbose);
        nodePrint(tmp, filename, verbose);

        fclose(yyin);
        printf("\n");
        /* IR_entry(root); */
        delete root;
    }
    return 0;
}