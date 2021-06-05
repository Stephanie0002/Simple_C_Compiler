%{
#include <cstdlib>
#include <cstdio>
#include "grammarTree.h"

using namespace std;

extern int yycolumn;
extern int yylineno;

int error_num = 0;
int last_error_lineno = 0;

struct grammarTree *root = NULL;

int yylex(void);
void yyerror(const char *);
int isNewError(int error_lineno);
%}

%union {
    struct grammarTree* node;
}

%token <node> NUMBER CONST IDENT WrongNumberFormat
%token <node> INT UNDESIGNED
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

%nonassoc error

// %left '[' ']' '(' ')'
%right '!'
%left '/' '*' '%' 
%left '+' '-'
%left '>' GE_OP '<' LE_OP EQ_OP NE_OP
%left AND_OP OR_OP
%right '='
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

// 编译单元
CompUnit: 
        CompUnit Decl{ root = $$ = createGrammarTree("CompUnit", 2, $1, $2);}
    |   Decl{ root = $$ = createGrammarTree("CompUnit", 1, $1);}
    |   CompUnit FuncDef{ root = $$ = createGrammarTree("CompUnit", 2, $1, $2);}
    |   FuncDef{ root = $$ = createGrammarTree("CompUnit", 1, $1);}
    ;

// 声明
Decl: 
        ConstDecl{$$ = createGrammarTree("Decl", 1, $1);}
    |   VarDecl{$$ = createGrammarTree("Decl", 1, $1);}
    ;

// 常量声明
ConstDecl:
        CONST BType ConstDef ConstDef_list ';'{$$ = createGrammarTree("ConstDecl", 5, $1, $2, $3, $4, $5);}
    ;

ConstDef_list:
        ConstDef_list ',' ConstDef{$$ = createGrammarTree("ConstDef_list", 3, $1, $2, $3);}
    |   {$$ = addNullNode("ConstDef_list", yylineno, yycolumn);}
    ;

// 基本类型
BType:
        INT{$$ = createGrammarTree("BType", 1, $1);}
    |   UNDESIGNED{}
    ;

// 常数定义
ConstDef:
        IDENT '=' ConstInitVal{$$ = createGrammarTree("ConstDef", 3, $1, $2, $3);}
    |   IDENT '[' ConstExp ']' '=' ConstInitVal{$$ = createGrammarTree("ConstDef", 6, $1, $2, $3, $4, $5, $6);}
    ;

// 常量初值
ConstInitVal:
        ConstExp{$$ = createGrammarTree("ConstInitVal", 1, $1);}
    |   '{' '}'{$$ = createGrammarTree("ConstInitVal", 2, $1, $2);}
    |   '{' ConstExp ConstExp_list '}'{$$ = createGrammarTree("ConstInitVal", 4, $1, $2, $3, $4);}
    ;
ConstExp_list:
        ConstExp_list ',' ConstExp{$$ = createGrammarTree("ConstExp_list", 3, $1, $2, $3);}
    |   {$$ = addNullNode("ConstExp_list", yylineno, yycolumn);}
    ;

// 变量声明
VarDecl:
        BType VarDef VarDef_list ';'{$$ = createGrammarTree("VarDecl", 4, $1, $2, $3, $4);}
    ;

VarDef_list:
        VarDef_list ',' VarDef{$$ = createGrammarTree("VarDef_list", 3, $1, $2, $3);}
    |   {$$ = addNullNode("VarDef_list", yylineno, yycolumn);}
    ;

// 变量定义
VarDef: 
        IDENT{$$ = createGrammarTree("VarDef", 1, $1);}
    |   IDENT '[' ConstExp ']'{$$ = createGrammarTree("VarDef", 4, $1, $2, $3, $4);}
    |   IDENT '=' InitVal{$$ = createGrammarTree("VarDef", 3, $1, $2, $3);}
    |   IDENT '[' ConstExp ']' '=' InitVal{$$ = createGrammarTree("VarDef", 6, $1, $2, $3, $4, $5, $6);}
    ;

// 变量初值
InitVal:
        Exp{$$ = createGrammarTree("InitVal", 1, $1);}
    |   '{' '}'{$$ = createGrammarTree("InitVal", 2, $1, $2);}
    |   '{' Exp Exp_list '}'{$$ = createGrammarTree("InitVal", 4, $1, $2, $3, $4);}
    ;

Exp_list:
        Exp_list ',' Exp{$$ = createGrammarTree("Exp_list", 3, $1, $2, $3);}
    |   {$$ = addNullNode("Exp_list", yylineno, yycolumn);}
    ;

// 函数定义
FuncDef:
        BType IDENT '(' FuncFParams ')' Block{$$ = createGrammarTree("FuncDef", 6, $1, $2, $3, $4, $5, $6);}
    ;

// 函数形参表
FuncFParams: 
        FuncFParam FuncFParam_list{$$ = createGrammarTree("FuncFParams", 2, $1, $2);}
    |   {$$ = addNullNode("FuncFParams", yylineno, yycolumn);}
    ;

FuncFParam_list:
        FuncFParam_list ',' FuncFParam{$$ = createGrammarTree("FuncFParam_list", 3, $1, $2, $3);}
    |   {$$ = addNullNode("FuncFParam_list", yylineno, yycolumn);}
    ;

// 函数形参
FuncFParam:
        BType IDENT{$$ = createGrammarTree("FuncFParam", 2, $1, $2);}
    |   BType IDENT '[' ']'{$$ = createGrammarTree("FuncFParam", 4, $1, $2, $3, $4);}
    ;

// 语句块
Block:
        '{' BlockItem_list '}'{$$ = createGrammarTree("Block", 3, $1, $2, $3);}
    ;
    
BlockItem_list:
    BlockItem_list BlockItem{$$ = createGrammarTree("BlockItem_list", 2, $1, $2);}
    |   {$$ = addNullNode("BlockItem_list", yylineno, yycolumn);}
    ;

// 语句块项
BlockItem:
        Decl{$$ = createGrammarTree("BlockItem", 1, $1);} 
    |   Stmt{$$ = createGrammarTree("BlockItem", 1, $1);}
    ;

// 语句
Stmt:
        LVal '=' Exp ';'{$$ = createGrammarTree("Stmt", 4, $1, $2, $3, $4);}
    |   Exp ';'{$$ = createGrammarTree("Stmt", 2, $1, $2);}
    |   ';'{$$ = createGrammarTree("Stmt", 1, $1);}
    |   Block{$$ = createGrammarTree("Stmt", 1, $1);}
    |   IF '(' Cond ')' Stmt{$$ = createGrammarTree("Stmt", 5, $1, $2, $3, $4, $5);}
    |   IF '(' Cond ')' Stmt ELSE Stmt{$$ = createGrammarTree("Stmt", 7, $1, $2, $3, $4, $5, $6, $7);}
    |   WHILE '(' Cond ')' Stmt{$$ = createGrammarTree("Stmt", 5, $1, $2, $3, $4, $5);}
    |   BREAK ';'{$$ = createGrammarTree("Stmt", 2, $1, $2);}
    |   CONTINUE ';'{$$ = createGrammarTree("Stmt", 2, $1, $2);}
    |   RETURN Exp ';'{$$ = createGrammarTree("Stmt", 3, $1, $2, $3);}
    |   error ';' {if(isNewError(yylineno)) fprintf(stderr, "Error [Syntax] at Line %d Col %d: Syntax error \'%s\'.\n", yylineno, yycolumn, yytext);}
    ;

// 表达式
Exp:
        AddExp{$$ = createGrammarTree("Exp", 1, $1);}
    ;

// 条件表达式
Cond:
        LOrExp{$$ = createGrammarTree("Cond", 1, $1);}
    ;

// 左值表达式
LVal: 
        IDENT{$$ = createGrammarTree("LVal", 1, $1);}
    |   IDENT '[' Exp ']'{$$ = createGrammarTree("LVal", 4, $1, $2, $3, $4);}
    ;

// 基本表达式
PrimaryExp:
        '(' Exp ')'{$$ = createGrammarTree("PrimaryExp", 3, $1, $2, $3);}
    |   LVal{$$ = createGrammarTree("PrimaryExp", 1, $1);}
    |   NUMBER{$$ = createGrammarTree("PrimaryExp", 1, $1);}
    |   WrongNumberFormat{}
    
    ;

// 一元表达式
UnaryExp:
        PrimaryExp{$$ = createGrammarTree("UnaryExp", 1, $1);}
    |   IDENT '(' FuncRParams ')'{$$ = createGrammarTree("UnaryExp", 4, $1, $2, $3, $4);}
    |   UnaryOp UnaryExp{$$ = createGrammarTree("UnaryExp", 2, $1, $2);}
    ;

// 单目运算符
UnaryOp:
        '+'{$$ = createGrammarTree("UnaryOp", 1, $1);}
    |   '-'{$$ = createGrammarTree("UnaryOp", 1, $1);}
    |   '!'{$$ = createGrammarTree("UnaryOp", 1, $1);}
    ;

// 函数实参表
FuncRParams:
        Exp Exp_list{$$ = createGrammarTree("FuncRParams", 2, $1, $2);}
    |   {$$ = addNullNode("FuncRParams", yylineno, yycolumn);}
    ;

// 加减表达式
AddExp: 
        MulExp{$$ = createGrammarTree("AddExp", 1, $1);}
    |   AddExp '+' MulExp{$$ = createGrammarTree("AddExp", 3, $1, $2, $3);}
    |   AddExp '-' MulExp{$$ = createGrammarTree("AddExp", 3, $1, $2, $3);}
    ;

// 乘除模表达式
MulExp:
        UnaryExp{$$ = createGrammarTree("MulExp", 1, $1);}
    |   MulExp '*' UnaryExp{$$ = createGrammarTree("MulExp", 3, $1, $2, $3);}
    |   MulExp '/' UnaryExp{$$ = createGrammarTree("MulExp", 3, $1, $2, $3);}
    |   MulExp '%' UnaryExp{$$ = createGrammarTree("MulExp", 3, $1, $2, $3);}
    ;

// 关系表达式
RelExp:
        AddExp{$$ = createGrammarTree("RelExp", 1, $1);}
    |   RelExp '<' AddExp{$$ = createGrammarTree("RelExp", 3, $1, $2, $3);}
    |   RelExp '>' AddExp{$$ = createGrammarTree("RelExp", 3, $1, $2, $3);}
    |   RelExp LE_OP AddExp{$$ = createGrammarTree("RelExp", 3, $1, $2, $3);}
    |   RelExp GE_OP AddExp{$$ = createGrammarTree("RelExp", 3, $1, $2, $3);}
    ;

// 相等性表达式
EqExp:
        RelExp{$$ = createGrammarTree("EqExp", 1, $1);}
    |   EqExp EQ_OP RelExp{$$ = createGrammarTree("EqExp", 3, $1, $2, $3);}
    |   EqExp NE_OP RelExp{$$ = createGrammarTree("EqExp", 3, $1, $2, $3);}
    ;

// 逻辑与表达式
LAndExp:
        EqExp{$$ = createGrammarTree("LAndExp", 1, $1);}
    |   LAndExp AND_OP EqExp{$$ = createGrammarTree("LAndExp", 3, $1, $2, $3);}
    ;

// 逻辑或表达式
LOrExp:
        LAndExp{$$ = createGrammarTree("LOrExp", 1, $1);}
    |   LOrExp OR_OP LAndExp{$$ = createGrammarTree("LOrExp", 3, $1, $2, $3);}
    ;

// 表达式
ConstExp:
        AddExp{$$ = createGrammarTree("ConstExp", 1, $1);}
    ;
%%

void yyerror(char const *s)
{
    if (isNewError(yylineno)){
        fprintf(stderr, "Error [Syntax] at Line %d, Col %d: %s \'%s\'.\n", yylineno, yycolumn, s, yytext);
    }
}

int isNewError(int error_lineno){
    if (last_error_lineno != error_lineno){
        error_num++;
        last_error_lineno = error_lineno;
        return 1;
    }
    else{
        return 0;
    }
}