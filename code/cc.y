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
%}

%union {
    struct grammarTree* tree;
}

%token <tree> NUMBER CONST IDENT
%token <tree> INT VOID
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
%type <tree> TempA TempB TempC TempD TempE TempF TempG
%type <tree> Stmt Cond

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%
/* rules */

// 编译单元
CompUnit: 
        CompUnit Decl{root = createTree("CompUnit", 1, $1);}
    |   Decl{root = createTree("CompUnit", 1, $1);}
    |   CompUnit FuncDef{root = createTree("CompUnit", 2, $1, $2);}
    |   FuncDef{root = createTree("CompUnit", 1, $1);}
    ;

// 声明
Decl: 
        ConstDecl{$$ = createTree("Decl", 1, $1);}
    |   VarDecl{$$ = createTree("Decl", 1, $1);}
    ;

// 常量声明
ConstDecl:
        CONST BType ConstDef TempA ';'{$$ = createTree("ConstDecl", 5, $1, $2, $3, $4, $5);}
    ;

TempA:
        TempA ',' ConstDef{$$ = createTree("TempA", 3, $1, $2, $3);}
    |   {$$ = createTree("TempA", -1, yylineno);}
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
    |   '{' ConstExp TempB '}'{$$ = createTree("ConstInitVal", 4, $1, $2, $3, $4);}
    ;
TempB:
        TempB ',' ConstExp{$$ = createTree("TempB", 3, $1, $2, $3);}
    |   {$$ = createTree("TempB", -1, yylineno);}
    ;

// 变量声明
VarDecl:
        BType VarDef TempC ';'{$$ = createTree("VarDecl", 4, $1, $2, $3, $4);}
    ;

TempC:
        TempC ',' VarDef{$$ = createTree("Tempc", 3, $1, $2, $3);}
    |   {$$ = createTree("TempC", -1, yylineno);}
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
    |   '{' Exp TempD '}'{$$ = createTree("InitVal", 4, $1, $2, $3, $4);}
    ;

TempD:
        TempD ',' Exp{$$ = createTree("TempD", 3, $1, $2, $3);}
    |   {$$ = createTree("TempD", -1, yylineno);}
    ;

// 函数定义
FuncDef:
        BType IDENT '(' ')' Block{$$ = createTree("FuncDef", 5, $1, $2, $3, $4, $5);}
    |   BType IDENT '(' FuncFParams ')' Block{$$ = createTree("FuncDef", 6, $1, $2, $3, $4, $5, $6);}
    ;

// 函数形参表
FuncFParams: 
        FuncFParam TempE{$$ = createTree("FuncFparams", 2, $1, $2);}
    ;

TempE:
        TempE ',' FuncFParam{$$ = createTree("TempE", 3, $1, $2, $3);}
    |   {$$ = createTree("TempE", -1, yylineno);}
    ;

// 函数形参
FuncFParam:
        BType IDENT{$$ = createTree("FuncFparam", 2, $1, $2);}
    |   BType IDENT '[' ']'{$$ = createTree("FuncFparam", 4, $1, $2, $3, $4);}
    ;

// 语句块
Block:
        '{' TempF '}'{$$ = createTree("block", 3, $1, $2, $3);}
    ;
    
TempF:
    TempF BlockItem{$$ = createTree("TempF", 2, $1, $2);}
    |   {$$ = createTree("TempF", -1, yylineno);}
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
    |   RETURN ';'{$$ = createTree("Stmt", 2, $1, $2);}
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
    |   IDENT '(' ')'{$$ = createTree("UnaryExp", 3, $1, $2, $3);}
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
        Exp TempG{$$ = createTree("FuncFParams", 2, $1, $2);}
    ;
TempG:
        TempG ',' Exp{$$ = createTree("TempG", 3, $1, $2, $3);}
    |   {$$ = createTree("TempG", -1, yylineno);}
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
    yydebug = 1;
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
        
        printf("The source code of %s is: \n", argv[i]);
        yyparse();

        grammarTree* tmp = root;
        // if (verbose)
        //     outputTree(root, 0);
        floorPrint(root, filename, verbose);
        nodePrint(tmp, filename, verbose);
        Clean(root);

        fclose(yyin);
        printf("\n");
    }
    return 0;
}