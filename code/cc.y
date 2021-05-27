%{
#include <cstdlib>
#include <cstdio>
#include "syntaxTree.h"

using namespace std;

extern int yycolumn;
extern int yylineno;

int error_num = 0;
int last_error_lineno = 0;

struct syntaxTree *root = NULL;

int yylex(void);
void yyerror(const char *);
%}

%union {
    struct syntaxTree* node;
}

%token <node> NUMBER CONST IDENT
%token <node> INT FLOAT BOOL
%token <node> IF ELSE WHILE BREAK CONTINUE RETURN
%token <node> '+' '-' '*' '/' '%' '<' '>' '!' '='
%token <node> LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP 
%token <node> ';' ',' '[' ']' '(' ')' '{' '}'

%type <node> CompUnit Decl 
%type <node> ConstDecl VarDecl ConstDef ConstInitVal ConstExp
%type <node> VarDef InitVal
%type <node> Exp PrimaryExp UnaryExp LVal AddExp LOrExp UnaryOp MulExp RelExp EqExp LAndExp
%type <node> FuncDef FuncFParam FuncFParams FuncRParams BType
%type <node> Block BlockItem
%type <node> ConstDef_list ConstExp_list VarDef_list Exp_list FuncFParam_list BlockItem_list
%type <node> Stmt Cond

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

// 程序入口
Program:
        CompUnit{root = createSyntaxTree("Program", 1, $1);}
    ;

// 编译单元
CompUnit: 
        CompUnit Decl{root = createSyntaxTree("CompUnit", 2, $1, $2);}
    |   Decl{root = createSyntaxTree("CompUnit", 1, $1);}
    |   CompUnit FuncDef{root = createSyntaxTree("CompUnit", 2, $1, $2);}
    |   FuncDef{root = createSyntaxTree("CompUnit", 1, $1);}
    ;

// 声明
Decl: 
        ConstDecl{$$ = createSyntaxTree("Decl", 1, $1);}
    |   VarDecl{$$ = createSyntaxTree("Decl", 1, $1);}
    ;

// 常量声明
ConstDecl:
        CONST BType ConstDef ConstDef_list ';'{$$ = createSyntaxTree("ConstDecl", 5, $1, $2, $3, $4, $5);}
    ;

ConstDef_list:
        ConstDef_list ',' ConstDef{$$ = createSyntaxTree("ConstDef_list", 3, $1, $2, $3);}
    |   {$$ = createSyntaxTree("ConstDef_list", -1, yylineno);}
    ;

// 基本类型
BType:
        INT{$$ = createSyntaxTree("BType", 1, $1);}
    |   FLOAT{$$ = createSyntaxTree("BType", 1, $1);}
    |   BOOL{$$ = createSyntaxTree("BType", 1, $1);}
    ;

// 常数定义
ConstDef:
        IDENT '=' ConstInitVal{$$ = createSyntaxTree("ConstDef", 3, $1, $2, $3);}
    |   IDENT '[' ConstExp ']' '=' ConstInitVal{$$ = createSyntaxTree("ConstDef", 6, $1, $2, $3, $4, $5, $6);}
    ;

// 常量初值
ConstInitVal:
        ConstExp{$$ = createSyntaxTree("ConstInitVal", 1, $1);}
    |   '{' '}'{$$ = createSyntaxTree("ConstInitVal", 2, $1, $2);}
    |   '{' ConstExp ConstExp_list '}'{$$ = createSyntaxTree("ConstInitVal", 4, $1, $2, $3, $4);}
    ;
ConstExp_list:
        ConstExp_list ',' ConstExp{$$ = createSyntaxTree("ConstExp_list", 3, $1, $2, $3);}
    |   {$$ = createSyntaxTree("ConstExp_list", -1, yylineno);}
    ;

// 变量声明
VarDecl:
        BType VarDef VarDef_list ';'{$$ = createSyntaxTree("VarDecl", 4, $1, $2, $3, $4);}
    ;

VarDef_list:
        VarDef_list ',' VarDef{$$ = createSyntaxTree("VarDef_list", 3, $1, $2, $3);}
    |   {$$ = createSyntaxTree("VarDef_list", -1, yylineno);}
    ;

// 变量定义
VarDef: 
        IDENT{$$ = createSyntaxTree("VarDef", 1, $1);}
    |   IDENT '[' ConstExp ']'{$$ = createSyntaxTree("VarDef", 4, $1, $2, $3, $4);}
    |   IDENT '=' InitVal{$$ = createSyntaxTree("VarDef", 3, $1, $2, $3);}
    |   IDENT '[' ConstExp ']' '=' InitVal{$$ = createSyntaxTree("VarDef", 6, $1, $2, $3, $4, $5, $6);}
    ;

// 变量初值
InitVal:
        Exp{$$ = createSyntaxTree("InitVal", 1, $1);}
    |   '{' '}'{$$ = createSyntaxTree("InitVal", 2, $1, $2);}
    |   '{' Exp Exp_list '}'{$$ = createSyntaxTree("InitVal", 4, $1, $2, $3, $4);}
    ;

Exp_list:
        Exp_list ',' Exp{$$ = createSyntaxTree("Exp_list", 3, $1, $2, $3);}
    |   {$$ = createSyntaxTree("Exp_list", -1, yylineno);}
    ;

// 函数定义
FuncDef:
        BType IDENT '(' FuncFParams ')' Block{$$ = createSyntaxTree("FuncDef", 6, $1, $2, $3, $4, $5, $6);}
    ;

// 函数形参表
FuncFParams: 
        FuncFParam FuncFParam_list{$$ = createSyntaxTree("FuncFParams", 2, $1, $2);}
    |   {$$ = createSyntaxTree("FuncFParams", -1, yylineno);}
    ;

FuncFParam_list:
        FuncFParam_list ',' FuncFParam{$$ = createSyntaxTree("FuncFParam_list", 3, $1, $2, $3);}
    |   {$$ = createSyntaxTree("FuncFParam_list", -1, yylineno);}
    ;

// 函数形参
FuncFParam:
        BType IDENT{$$ = createSyntaxTree("FuncFparam", 2, $1, $2);}
    |   BType IDENT '[' ']'{$$ = createSyntaxTree("FuncFparam", 4, $1, $2, $3, $4);}
    ;

// 语句块
Block:
        '{' BlockItem_list '}'{$$ = createSyntaxTree("Block", 3, $1, $2, $3);}
    ;
    
BlockItem_list:
    BlockItem_list BlockItem{$$ = createSyntaxTree("BlockItem_list", 2, $1, $2);}
    |   {$$ = createSyntaxTree("BlockItem_list", -1, yylineno);}
    ;

// 语句块项
BlockItem:
        Decl{$$ = createSyntaxTree("BlockItem", 1, $1);} 
    |   Stmt{$$ = createSyntaxTree("BlockItem", 1, $1);}
    ;

// 语句
Stmt:
        LVal '=' Exp ';'{$$ = createSyntaxTree("Stmt", 4, $1, $2, $3, $4);}
    |   Exp ';'{$$ = createSyntaxTree("Stmt", 2, $1, $2);}
    |   ';'{$$ = createSyntaxTree("Stmt", 1, $1);}
    |   Block{$$ = createSyntaxTree("Stmt", 1, $1);}
    |   IF '(' Cond ')' Stmt{$$ = createSyntaxTree("Stmt", 5, $1, $2, $3, $4, $5);}
    |   IF '(' Cond ')' Stmt ELSE Stmt{$$ = createSyntaxTree("Stmt", 7, $1, $2, $3, $4, $5, $6, $7);}
    |   WHILE '(' Cond ')' Stmt{$$ = createSyntaxTree("Stmt", 5, $1, $2, $3, $4, $5);}
    |   BREAK ';'{$$ = createSyntaxTree("Stmt", 2, $1, $2);}
    |   CONTINUE ';'{$$ = createSyntaxTree("Stmt", 2, $1, $2);}
    |   RETURN ';'{$$ = createSyntaxTree("Stmt", 2, $1, $2);}
    |   RETURN Exp ';'{$$ = createSyntaxTree("Stmt", 3, $1, $2, $3);}
    ;

// 表达式
Exp:
        AddExp{$$ = createSyntaxTree("Exp", 1, $1);}
    ;

// 条件表达式
Cond:
        LOrExp{$$ = createSyntaxTree("Cond", 1, $1);}
    ;

// 左值表达式
LVal: 
        IDENT{$$ = createSyntaxTree("LVal", 1, $1);}
    |   IDENT '[' Exp ']'{$$ = createSyntaxTree("LVal", 4, $1, $2, $3, $4);}
    ;

// 基本表达式
PrimaryExp:
        '(' Exp ')'{$$ = createSyntaxTree("PrimaryExp", 3, $1, $2, $3);}
    |   LVal{$$ = createSyntaxTree("PrimaryExp", 1, $1);}
    |   NUMBER{$$ = createSyntaxTree("PrimaryExp", 1, $1);}
    ;

// 一元表达式
UnaryExp:
        PrimaryExp{$$ = createSyntaxTree("UnaryExp", 1, $1);}
    |   IDENT '(' FuncRParams ')'{$$ = createSyntaxTree("UnaryExp", 4, $1, $2, $3, $4);}
    |   UnaryOp UnaryExp{$$ = createSyntaxTree("UnaryExp", 2, $1, $2);}
    ;

// 单目运算符
UnaryOp:
        '+'{$$ = createSyntaxTree("UnaryOP", 1, $1);}
    |   '-'{$$ = createSyntaxTree("UnaryOP", 1, $1);}
    |   '!'{$$ = createSyntaxTree("UnaryOP", 1, $1);}
    ;

// 函数实参表
FuncRParams:
        Exp Exp_list{$$ = createSyntaxTree("FuncRParams", 2, $1, $2);}
    |   {$$ = createSyntaxTree("FuncRParams", -1, yylineno);}
    ;

// 加减表达式
AddExp: 
        MulExp{$$ = createSyntaxTree("AddExp", 1, $1);}
    |   AddExp '+' MulExp{$$ = createSyntaxTree("AddExp", 3, $1, $2, $3);}
    |   AddExp '-' MulExp{$$ = createSyntaxTree("AddExp", 3, $1, $2, $3);}
    ;

// 乘除模表达式
MulExp:
        UnaryExp{$$ = createSyntaxTree("MulExp", 1, $1);}
    |   MulExp '*' UnaryExp{$$ = createSyntaxTree("MulExp", 3, $1, $2, $3);}
    |   MulExp '/' UnaryExp{$$ = createSyntaxTree("MulExp", 3, $1, $2, $3);}
    |   MulExp '%' UnaryExp{$$ = createSyntaxTree("MulExp", 3, $1, $2, $3);}
    ;

// 关系表达式
RelExp:
        AddExp{$$ = createSyntaxTree("RelExp", 1, $1);}
    |   RelExp '<' AddExp{$$ = createSyntaxTree("RelExp", 3, $1, $2, $3);}
    |   RelExp '>' AddExp{$$ = createSyntaxTree("RelExp", 3, $1, $2, $3);}
    |   RelExp LE_OP AddExp{$$ = createSyntaxTree("RelExp", 3, $1, $2, $3);}
    |   RelExp GE_OP AddExp{$$ = createSyntaxTree("RelExp", 3, $1, $2, $3);}
    ;

// 相等性表达式
EqExp:
        RelExp{$$ = createSyntaxTree("EqExp", 1, $1);}
    |   EqExp EQ_OP RelExp{$$ = createSyntaxTree("EqExp", 3, $1, $2, $3);}
    |   EqExp NE_OP RelExp{$$ = createSyntaxTree("EqExp", 3, $1, $2, $3);}
    ;

// 逻辑与表达式
LAndExp:
        EqExp{$$ = createSyntaxTree("LAndExp", 1, $1);}
    |   LAndExp AND_OP EqExp{$$ = createSyntaxTree("LAndExp", 3, $1, $2, $3);}
    ;

// 逻辑或表达式
LOrExp:
        LAndExp{$$ = createSyntaxTree("LOrExp", 1, $1);}
    |   LOrExp OR_OP LAndExp{$$ = createSyntaxTree("LOrExp", 3, $1, $2, $3);}
    ;

// 表达式
ConstExp:
        AddExp{$$ = createSyntaxTree("ConstExp", 1, $1);}
    ;
%%

void yyerror(char const *s)
{
	fflush(stdout);
	fprintf(stderr, "Error [Syntax] at Line %d, col %d: %s.\n", yylineno, yycolumn, s);
    exit(0);
}