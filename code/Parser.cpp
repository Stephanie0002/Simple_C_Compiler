#include "Parser.h"

// Global variables
bool debug = true;
myHashSet symbol_table;
myData INTtype;
myData FLOATtype;
int unnamedCount;

bool checkProduction(const syntaxTree *parent, int node_num, ...)
{

    va_list valist;
    va_start(valist, node_num);
    bool flag = true;
    syntaxTree *child = parent->left;

    for (int i = 0; i < node_num; i++)
    {
        if (child == NULL)
        {
            flag = false;
            break;
        }
        string node_name = va_arg(valist, const char *);
        if (node_name != child->name)
        {
            flag = false;
            break;
        }
        child = child->right;
    }
    va_end(valist);
    if (child != NULL)
    {
        flag = false;
    }
    return flag;
}

void semanticAnalysis(const syntaxTree *root)
{
    semanticInit(root);
}

void semanticInit(const syntaxTree *root)
{
    symbol_table = initHashSet(HASH_SIZE);

    INTtype.data_type = BASIC;
    INTtype.basic = INT;
    INTtype.is_r_value = false;
    FLOATtype.data_type = BASIC;
    FLOATtype.basic = FLOAT;
    FLOATtype.is_r_value = false;
    unnamedCount = 0;

    // add read and write
    mySymbol *read = createSymbol("read", FUNC);
    read->func->ret_type = &INTtype;
    read->func->param_num = 0;
    read->func->param_list = NULL;
    insert(symbol_table, read);

    mySymbol *write = createSymbol("write", FUNC);
    write->func->ret_type = &INTtype;
    write->func->param_num = 1;
    myParam *param = new myParam;
    param->type = &INTtype;
    param->next = NULL;
    write->func->param_list = param;
    insert(symbol_table, write);

    if (debug)
    {
        printf("\n---------Sementic Analysis---------\n");
    }

    analyseProgram(root);
    if (debug)
    {
        printSymbolTable(symbol_table);
    }
}

void analyseProgram(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse Program:\t");
    }

    if (node == NULL)
    {
        return;
    }

    if (checkProduction(node, 1, "CompUnit"))
    {
        analyseCompUnit(node->left);
    }
    else
    {
        printProductionError(node, "Program");
    }
}

void analyseCompUnit(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse CompUnit:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 2, "CompUnit", "Decl"))
    {
        analyseCompUnit(node->left);
        analyseDecl(node->left->right);
    }
    else if (checkProduction(node, 1, "Decl"))
    {
        analyseDecl(node->left);
    }
    else if (checkProduction(node, 2, "CompUnit", "FuncDef"))
    {
        analyseCompUnit(node->left);
        analyseFuncDef(node->left->right);
    }
    else if (checkProduction(node, 1, "FuncDef"))
    {
        analyseFuncDef(node->left);
    }
    else
    {
        printProductionError(node, "CompUnit");
    }
}

void analyseDecl(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse Decl:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "ConstDecl"))
    {
        analyseConstDecl(node->left);
    }
    else if (checkProduction(node, 1, "VarDecl"))
    {
        analyseVarDecl(node->left);
    }
    else
    {
        printProductionError(node, "Decl");
    }
}

void analyseConstDecl(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse ConstDecl:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 5, "CONST", "BType", "ConstDef", "ConstDef_list", ";"))
    {
        // Remains to be solved
        analyseBType(node->left->right);
        analyseConstDef(node->left->right->right);
        analyseConstDef_list(node->left->right->right->right);
    }
    else
    {
        printProductionError(node, "ConstDecl");
    }
}

void analyseConstDef_list(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse ConstDef_list:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 3, "ConstDef_list", ",", "ConstDef"))
    {
        analyseConstDef_list(node->left);
        analyseConstDef(node->left->right->right);
    }
    else if (checkProduction(node, 1, "Null"))
    {
    }
    else
    {
        printProductionError(node, "ConstDef_list");
    }
}

myData *analyseBType(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse Btype:\t");
    }

    myData *type = new myData;
    if (checkProduction(node, 1, "INT"))
    {

        type->data_type = BASIC;
        type->basic = INT;
        type->is_r_value = false;
    }
    else if (checkProduction(node, 1, "FLOAT"))
    {
        type->data_type = BASIC;
        type->basic = FLOAT;
        type->is_r_value = false;
    }
    else if (checkProduction(node, 1, "BOOL"))
    {
        type->data_type = BASIC;
        type->basic = BOOL;
        type->is_r_value = false;
    }
    else
    {
        printProductionError(node, "BType");
    }
    return type;
}

void analyseConstDef(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse ConstDef:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 3, "IDENT", "=", "ConstInitVal"))
    {
        // myData* ele =
        // mySymbol* ele = createSymbol(node->left->content, type);
        analyseConstInitVal(node->left->right->right);
    }
    else if (checkProduction(node, 6, "IDENT", "[", "ConstExp", "]", "=", "ConstInitVal"))
    {
        //
        //
        analyseConstExp(node->left->right->right);
        //
        //
        analyseConstInitVal(node->left->right->right->right->right->right);
    }
    else
    {
        printProductionError(node, "ConstDef");
    }
}

void analyseConstInitVal(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse ConstInitVal:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "ConstExp"))
    {
        analyseConstExp(node->left);
    }
    else if (checkProduction(node, 2, "{", "}"))
    {
        //
        //
    }
    else if (checkProduction(node, 4, "{", "ConstExp", "ConstExp_list", "}"))
    {
        //
        analyseConstExp(node->left->right);
        analyseConstExp_list(node->left->right->right);
        //
    }
    else
    {
        printProductionError(node, "ConstInitVal");
    }
}

void analyseConstExp_list(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse ConstExp_list:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 3, "ConstExp_list", ",", "ConstExp"))
    {
        analyseConstExp_list(node->left);
        //
        analyseConstExp(node->left->right);
    }
    else if (checkProduction(node, 1, "Null"))
    {
        //
    }
    else
    {
        printProductionError(node, "ConstExp_list");
    }
}

void analyseVarDecl(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse VarDecl:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 4, "BType", "VarDef", "VarDef_list", ";"))
    {
        analyseBType(node->left);
        analyseVarDef(node->left->right);
        analyseVarDef_list(node->left->right->right);
        // No need to analyse ";"
    }
    else
    {
        printProductionError(node, "VarDecl");
    }
}

void analyseVarDef_list(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse VarDef_list:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 3, "VarDef_list", ",", "VarDef"))
    {
        analyseVarDef_list(node->left);
        //
        analyseVarDef(node->left->right->right);
    }
    else if (checkProduction(node, 1, "Null"))
    {
        //
    }
    else
    {
        printProductionError(node, "VarDef_list");
    }
}

void analyseVarDef(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse VarDef:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "IDENT"))
    {
        // analyseIDENT(node->left);
    }
    else if (checkProduction(node, 4, "IDENT", "[", "ConstExp", "]"))
    {
        //
        //
        analyseConstExp(node->left->right->right);
        //
    }
    else if (checkProduction(node, 3, "IDENT", "=", "InitVal"))
    {
        //
        //
        analyseInitVal(node->left->right->right);
    }
    else if (checkProduction(node, 6, "IDENT", "[", "ConstExp", "]", "=", "InitVal"))
    {
        //
        //
        analyseConstExp(node->left->right->right);
        //
        //
        analyseInitVal(node->left->right->right->right->right->right);
    }
    else
    {
        printProductionError(node, "VarDef");
    }
}

void analyseInitVal(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse InitVal:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "Exp"))
    {
        analyseExp(node->left);
    }
    else if (checkProduction(node, 2, "{", "}"))
    {
        //
        //
    }
    else if (checkProduction(node, 4, "{", "Exp", "Exp_list", "}"))
    {
        //
        analyseExp(node->left->right);
        analyseExp_list(node->left->right->right);
        //
    }
    else
    {
        printProductionError(node, "InitVal");
    }
}

void analyseExp_list(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse Exp_list:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 3, "Exp_list", ",", "Exp"))
    {
        analyseExp_list(node->left);
        //
        analyseExp(node->left->right->right);
    }
    else if (checkProduction(node, 1, "Null"))
    {
        //
    }
    else
    {
        printProductionError(node, "Exp_list");
    }
}

void analyseFuncDef(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse FuncDef:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 5, "BType", "IDENT", "(", ")", "Block"))
    {
        myData *func_ret_type = analyseBType(node->left);
        mySymbol *func_symbol = createSymbol(node->left->right->content, FUNC);
        func_symbol->func->ret_type = func_ret_type;
        func_symbol->func->param_num = 0;
        func_symbol->func->param_list = NULL;
        insert(symbol_table, func_symbol);

        analyseBlock(node->left->right->right->right->right);
        // printf("1");
    }
    else if (checkProduction(node, 6, "BType", "IDENT", "(", "FuncFParams", ")", "Block"))
    {
        analyseBType(node->left);
        //
        //
        analyseFuncFParams(node->left->right->right->right);
        //
        analyseBlock(node->left->right->right->right->right->right);
    }
    else
    {
        printProductionError(node, "FuncDef");
    }
}

void analyseFuncFParams(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse FuncFParams:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 2, "FuncFParam", "FuncFParam_list"))
    {
        analyseFuncFParam(node->left);
        analyseFuncFParam_list(node->left->right);
    }
    else
    {
        printProductionError(node, "FuncFParams");
    }
}

void analyseFuncFParam_list(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse FuncFParam_list:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 3, "FuncFParam_list", ",", "FuncFParam"))
    {
        analyseFuncFParam_list(node->left);
        //
        analyseFuncFParam(node->left->right->right);
    }
    else if (checkProduction(node, 1, "Null"))
    {
        //
    }
    else
    {
        printProductionError(node, "FuncFParam_list");
    }
}

void analyseFuncFParam(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse FuncFparam:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 2, "BType", "IDENT"))
    {
        analyseBType(node->left);
        //
    }
    else if (checkProduction(node, 4, "BType", "IDENT", "[", "]"))
    {
        analyseBType(node->left);
        //
        //
        //
    }
    else
    {
        printProductionError(node, "FuncFParam");
    }
}

void analyseBlock(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse Block:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 3, "{", "BlockItem_list", "}"))
    {
        //
        analyseBlockItem_list(node->left->right);
        //
    }
    else
    {
        printProductionError(node, "Block");
    }
}

void analyseBlockItem_list(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse BlockItem_list:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 2, "BlockItem_list", "BlockItem"))
    {
        analyseBlockItem_list(node->left);
        analyseBlockItem(node->left->right);
    }
    else if (checkProduction(node, 1, "Null"))
    {
        //
    }
    else
    {
        printProductionError(node, "BlockItem_list");
    }
}

void analyseBlockItem(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse BlockItem:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "Decl"))
    {
        analyseDecl(node->left);
    }
    else if (checkProduction(node, 1, "Stmt"))
    {
        analyseStmt(node->left);
    }
    else
    {
        printProductionError(node, "BlockItem");
    }
}

void analyseStmt(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse Stmt:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 4, "LVal", "=", "Exp", ";"))
    {
        analyseLVal(node->left);
        //
        analyseExp(node->left->right->right);
        // No need to analyse ";"
    }
    else if (checkProduction(node, 2, "Exp", ";"))
    {
        analyseExp(node->left);
        // No need to analyse ";"
    }
    else if (checkProduction(node, 1, ";"))
    {
        // No need to analyse ";"
    }
    else if (checkProduction(node, 1, "Block"))
    {
        analyseBlock(node->left);
    }
    else if (checkProduction(node, 5, "IF", "(", "Cond", ")", "Stmt"))
    {
        //
        //
        analyseCond(node->left->right->right);
        //
        analyseStmt(node->left->right->right->right->right);
    }
    else if (checkProduction(node, 7, "IF", "(", "Cond", ")", "Stmt", "ELSE", "Stmt"))
    {
        //
        //
        analyseCond(node->left->right->right);
        //
        analyseStmt(node->left->right->right->right->right);
        //
        analyseStmt(node->left->right->right->right->right->right);
    }
    else if (checkProduction(node, 5, "WHILE", "(", "Cond", ")", "Stmt"))
    {
        //
        //
        analyseCond(node->left->right->right);
        //
        analyseStmt(node->left->right->right->right->right);
    }
    else if (checkProduction(node, 2, "BREAK", ";"))
    {
        //
        // No need to analyse ";"
    }
    else if (checkProduction(node, 2, "CONTINUE", ";"))
    {
        //
        // No need to analyse ";"
    }
    else if (checkProduction(node, 2, "RETURN", ";"))
    {
        //
        // No need to analyse ";"
    }
    else if (checkProduction(node, 3, "RETURN", "Exp", ";"))
    {
        //
        analyseExp(node->left->right);
        // No need to analyse ";"
    }
    else
    {
        printProductionError(node, "Stmt");
    }
}

void analyseExp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse Exp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "AddExp"))
    {
        analyseAddExp(node->left);
    }
    else
    {
        printProductionError(node, "AddExp");
    }
}

void analyseCond(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse Cond:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "LOrExp"))
    {
        analyseLOrExp(node->left);
    }
    else
    {
        printProductionError(node, "Cond");
    }
}

void analyseLVal(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse LVal:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "IDENT"))
    {
        //
    }
    else if (checkProduction(node, 4, "IDENT", "[", "Exp", "]"))
    {
        //
        //
        analyseExp(node->left->right->right);
        //
    }
    else
    {
        printProductionError(node, "LVal");
    }
}

void analysePrimaryExp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse PrimaryExp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 3, "(", "Exp", ")"))
    {
        //
        analyseExp(node->left->right);
        //
    }
    else if (checkProduction(node, 1, "LVal"))
    {
        analyseLVal(node->left);
    }
    else if (checkProduction(node, 1, "NUMBER"))
    {
        //
    }
    else
    {
        printProductionError(node, "PrimaryExp");
    }
}

void analyseUnaryExp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse UnaryExp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "PrimaryExp"))
    {
        analysePrimaryExp(node->left);
    }
    else if (checkProduction(node, 3, "IDENT", "(", ")"))
    {
        //
        //
        //
    }
    else if (checkProduction(node, 4, "IDENT", "(", "FuncRParams", ")"))
    {
        //
        //
        analyseFuncRParams(node->left->right->right);
        //
    }
    else if (checkProduction(node, 2, "UnaryOp", "UnaryExp"))
    {
        analyseUnaryOp(node->left);
        analyseUnaryExp(node->left->right);
    }
    else
    {
        printProductionError(node, "UnaryExp");
    }
}

void analyseUnaryOp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse UnaryOp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "+"))
    {
        //
    }
    else if (checkProduction(node, 1, "-"))
    {
        //
    }
    else if (checkProduction(node, 1, "!"))
    {
        //
    }
    else
    {
        printProductionError(node, "UnaryOp");
    }
}

void analyseFuncRParams(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse FuncRParams:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 2, "Exp", "Exp_list"))
    {
        analyseExp(node->left);
        analyseExp_list(node->left->right);
    }
    else
    {
        printProductionError(node, "FuncRParams");
    }
}

void analyseAddExp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse AddExp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "MulExp"))
    {
        analyseMulExp(node->left);
    }
    else if (checkProduction(node, 3, "AddExp", "+", "MulExp"))
    {
        analyseAddExp(node->left);
        //
        analyseMulExp(node->left->right->right);
    }
    else if (checkProduction(node, 3, "AddExp", "-", "MulExp"))
    {
        analyseAddExp(node->left);
        //
        analyseMulExp(node->left->right->right);
    }
    else
    {
        printProductionError(node, "AddExp");
    }
}

void analyseMulExp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse MulExp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "UnaryExp"))
    {
        analyseUnaryExp(node->left);
    }
    else if (checkProduction(node, 3, "MulExp", "*", "UnaryExp"))
    {
        analyseMulExp(node->left);
        //
        analyseUnaryExp(node->left->right->right);
    }
    else if (checkProduction(node, 3, "MulExp", "/", "UnaryExp"))
    {
        analyseMulExp(node->left);
        //
        analyseUnaryExp(node->left->right->right);
    }
    else if (checkProduction(node, 3, "MulExp", "%", "UnaryExp"))
    {
        analyseMulExp(node->left);
        //
        analyseUnaryExp(node->left->right->right);
    }
    else
    {
        printProductionError(node, "MulExp");
    }
}

void analyseRelExp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse RelExp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "AddExp"))
    {
        analyseAddExp(node->left);
    }
    else if (checkProduction(node, 3, "RelExp", "<", "AddExp"))
    {
        analyseRelExp(node->left);
        //
        analyseAddExp(node->left->right->right);
    }
    else if (checkProduction(node, 3, "RelExp", ">", "AddExp"))
    {
        analyseRelExp(node->left);
        //
        analyseAddExp(node->left->right->right);
    }
    else if (checkProduction(node, 3, "RelExp", "LE_OP", "AddExp"))
    {
        analyseRelExp(node->left);
        //
        analyseAddExp(node->left->right->right);
    }
    else if (checkProduction(node, 3, "RelExp", "GE_OP", "AddExp"))
    {
        analyseRelExp(node->left);
        //
        analyseAddExp(node->left->right->right);
    }
    else
    {
        printProductionError(node, "RelExp");
    }
}

void analyseEqExp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse EqExp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "RelExp"))
    {
        analyseRelExp(node->left);
    }
    else if (checkProduction(node, 3, "EqExp", "EQ_OP", "RelExp"))
    {
        analyseEqExp(node->left);
        //
        analyseRelExp(node->left->right->right);
    }
    else if (checkProduction(node, 3, "EqExp", "NE_OP", "RelExp"))
    {
        analyseEqExp(node->left);
        //
        analyseRelExp(node->left->right->right);
    }
    else
    {
        printProductionError(node, "EqExp");
    }
}

void analyseLAndExp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse LAndExp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "EqExp"))
    {
        analyseEqExp(node->left);
    }
    else if (checkProduction(node, 3, "LAndExp", "AND_OP", "EqExp"))
    {
        analyseLAndExp(node->left);
        //
        analyseEqExp(node->left->right->right);
    }
    else
    {
        printProductionError(node, "LAndExp");
    }
}

void analyseLOrExp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse LOrExp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "LAndExp"))
    {
        analyseLAndExp(node->left);
    }
    else if (checkProduction(node, 3, "LOrExp", "OR_OP", "LAndExp"))
    {
        analyseLOrExp(node->left);
        //
        analyseLAndExp(node->left->right->right);
    }
    else
    {
        printProductionError(node, "LOrExp");
    }
}

void analyseConstExp(const syntaxTree *node)
{
    if (debug)
    {
        printf("analyse ConstExp:\t");
    }

    if (node == NULL)
    {
        return;
    }
    if (checkProduction(node, 1, "AddExp"))
    {
        analyseAddExp(node->left);
    }
    else
    {
        printProductionError(node, "ConstExp");
    }
}

void printProductionError(const syntaxTree *node, const char *msg)
{
    syntaxTree *child = node->left;
    if (!child)
    {
        return;
    }

    fprintf(stderr, "Error [Semantic] when analyse %s: No matched production [%s ---> %s", msg, node->name.c_str(), child->name.c_str());
    while (child->right)
    {
        fprintf(stderr, " %s", child->right->name.c_str());
        child = child->right;
    }
    fprintf(stderr, "].\n");
}

void printSymbolTable(myHashSet symbol_table)
{
    printf("\n-----------Symbol Table-----------\n");
    int count = 0;
    for (int i = 0; i < symbol_table->size; i++)
    {
        mySymbolList *p = symbol_table->buckets[i].symbol_list;
        while (p != NULL)
        {
            count++;
            printf("[Symbol %d]\n", count);
            mySymbol *s = p->symbol;
            string symbol_type[] = {"VAR", "FUNC"};
            printf("Name: %s\nSymbol Type: %s\n", s->name.c_str(), symbol_type[s->symbol_type].c_str());
            if (s->symbol_type == FUNC)
            {
                printf("Return Type: \n");
                printDataType(s->func->ret_type);
                printf("Parameter Nums: %d\n", s->func->param_num);
                printf("Parameter List: ");
                myParam *pl = s->func->param_list;
                if (pl == NULL)
                {
                    printf("Null\n");
                }
                else
                {
                    printf("\n");
                    int i = 1;
                    for (myParam *pa = pl; pa != NULL; pa = pa->next)
                    {
                        printf("Param: %d\n", i);
                        printDataType(pa->type);
                        i++;
                    }
                }
            }
            else
            {
                printf("Type: \n");
                printDataType(s->type);
            }
            p = p->next;
        }
    }
    printf("\n");
}