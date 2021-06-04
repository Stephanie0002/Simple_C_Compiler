#include "Parser.h"

// Global variables
bool debug = false;
myHashSet symbol_table;

int semantic_error_num = 0;
int last_semantic_error_lineno = 0;

string cur_func_name;
vector<mySymbol *> func_field;

bool checkProduction(const grammarTree *parent, int node_num, ...)
{

    va_list valist;
    va_start(valist, node_num);
    bool flag = true;
    grammarTree *child = parent->left;

    for (int i = 0; i < node_num; i++)
    {
        if (child == nullptr)
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
    if (child != nullptr)
    {
        flag = false;
    }
    return flag;
}

void checkArray(mySymbol *symb, int lineno)
{
    int array_size = symb->type->array.size;
    int cur_size = 0;
    myData *it = symb->type->array.elem;
    while (it != nullptr)
    {
        it = it->array.elem;
        cur_size++;
    }
    if (cur_size < array_size)
    {
        int remain = array_size - cur_size;
        while (remain > 0)
        {
            myData *new_ele = new myData;
            new_ele->data_type = ARRAY;
            new_ele->basic = INT;
            new_ele->is_r_value = false;
            new_ele->value = 0;
            new_ele->array.size = symb->type->array.size;
            new_ele->array.elem = nullptr;
            addNewEleToArray(new_ele, symb);
            remain--;
        }
    }
    else if (cur_size > array_size)
    {
        fprintf(stderr, "Error [Semantic] at Line %d: Array %s initialization size %d > definition size %d.\n", lineno, symb->name.c_str(), cur_size, array_size);
    }
}

void checkRepeatDef(string name, int lineno)
{
    // for (int i = 0; i < symbol_table->size; i++)
    // {
    //     mySymbolList *p = symbol_table->buckets[i].symbol_list;
    //     while (p != nullptr)
    //     {
    //         mySymbol *s = p->symbol;
    //     }
    // }
}

int semanticAnalysis(const grammarTree *root)
{
    semanticInit(root);
    return semantic_error_num;
}

void semanticInit(const grammarTree *root)
{
    symbol_table = initHashSet(HASH_SIZE);

    if (debug)
    {
        printf("\n---------Sementic Analysis---------\n");
    }

    analyseCompUnit(root);
    if (debug)
    {
        printSymbolTable(symbol_table);
    }
}

void analyseCompUnit(const grammarTree *node)
{
    if (debug)
    {
        printf("analyse %d CompUnit:\t", node->id);
    }

    if (node == nullptr)
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

void analyseDecl(const grammarTree *node)
{
    if (debug)
    {
        printf("analyse %d Decl:\t", node->id);
    }

    if (node == nullptr)
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

void analyseConstDecl(const grammarTree *node)
{
    if (debug)
    {
        printf("analyse %d ConstDecl:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 5, "CONST", "BType", "ConstDef", "ConstDef_list", ";"))
    {
        myData *type = analyseBType(node->left->right);
        analyseConstDef(node->left->right->right, type);
        analyseConstDef_list(node->left->right->right->right, type);
    }
    else
    {
        printProductionError(node, "ConstDecl");
    }
}

void analyseConstDef_list(const grammarTree *node, myData *type)
{
    if (debug)
    {
        printf("analyse %d ConstDef_list:\t", node->id);
    }
    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 3, "ConstDef_list", ",", "ConstDef"))
    {
        analyseConstDef_list(node->left, type);
        analyseConstDef(node->left->right->right, type);
    }
    else if (checkProduction(node, 1, "Null"))
    {
    }
    else
    {
        printProductionError(node, "ConstDef_list");
    }
}

myData *analyseBType(const grammarTree *node)
{
    if (debug)
    {
        printf("analyse %d Btype:\t", node->id);
    }

    myData *type = new myData;
    if (checkProduction(node, 1, "INT"))
    {
        type->basic = INT;
    }
    else
    {
        printProductionError(node, "BType");
    }
    return type;
}

void analyseConstDef(const grammarTree *node, myData *type)
{
    if (debug)
    {
        printf("analyse %d ConstDef:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 3, "IDENT", "=", "ConstInitVal"))
    {
        // Infer: must be const int a = 1;
        // mySymbol *constant_symbol = createSymbol(cur_func_name + ":" + node->left->content, CONST);
        mySymbol *constant_symbol = createSymbol(node->left->content, CONST);
        constant_symbol->type = type;
        analyseConstInitVal(node->left->right->right, constant_symbol);

        constant_symbol->type->data_type = BASIC;
        constant_symbol->type->basic = INT;
        constant_symbol->type->is_r_value = false;

        // checkRepeatDef(constant_symbol->name, node->left->lineno);
        insert(symbol_table, constant_symbol);
    }
    else if (checkProduction(node, 6, "IDENT", "[", "ConstExp", "]", "=", "ConstInitVal"))
    {
        // Infer: must be const int a[2] = {1, 2};
        mySymbol *constant_symbol = createSymbol(node->left->content, CONST);
        constant_symbol->type = type;
        constant_symbol->type->data_type = ARRAY;
        constant_symbol->type->value = 65535;
        constant_symbol->type->array.size = 0;
        constant_symbol->type->array.elem = nullptr;

        analyseConstExp(node->left->right->right, constant_symbol);
        analyseConstInitVal(node->left->right->right->right->right->right, constant_symbol);

        checkArray(constant_symbol, node->left->lineno);
        insert(symbol_table, constant_symbol);
    }
    else
    {
        printProductionError(node, "ConstDef");
    }
}

void analyseConstInitVal(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d ConstInitVal:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "ConstExp"))
    {
        analyseConstExp(node->left, symb);
    }
    else if (checkProduction(node, 2, "{", "}"))
    {
    }
    else if (checkProduction(node, 4, "{", "ConstExp", "ConstExp_list", "}"))
    {
        analyseConstExp(node->left->right, symb);
        analyseConstExp_list(node->left->right->right, symb);
    }
    else
    {
        printProductionError(node, "ConstInitVal");
    }
}

void analyseConstExp_list(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d ConstExp_list:\t", node->id);
    }
    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 3, "ConstExp_list", ",", "ConstExp"))
    {
        analyseConstExp_list(node->left, symb);
        analyseConstExp(node->left->right->right, symb);
    }
    else if (checkProduction(node, 1, "Null"))
    {
    }
    else
    {
        printProductionError(node, "ConstExp_list");
    }
}

void analyseVarDecl(const grammarTree *node)
{
    if (debug)
    {
        printf("analyse %d VarDecl:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 4, "BType", "VarDef", "VarDef_list", ";"))
    {
        myData *type = analyseBType(node->left);
        analyseVarDef(node->left->right, type);
        analyseVarDef_list(node->left->right->right, type);
    }
    else
    {
        printProductionError(node, "VarDecl");
    }
}

void analyseVarDef_list(const grammarTree *node, myData *type)
{
    if (debug)
    {
        printf("analyse %d VarDef_list:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 3, "VarDef_list", ",", "VarDef"))
    {
        analyseVarDef_list(node->left, type);
        analyseVarDef(node->left->right->right, type);
    }
    else if (checkProduction(node, 1, "Null"))
    {
    }
    else
    {
        printProductionError(node, "VarDef_list");
    }
}

void analyseVarDef(const grammarTree *node, myData *type)
{
    if (debug)
    {
        printf("analyse %d VarDef:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "IDENT"))
    {
        // Infer: int a;
        mySymbol *var_symbol = createSymbol(node->left->content, VAR);
        var_symbol->type = type;
        var_symbol->type->data_type = BASIC;

        insert(symbol_table, var_symbol);
    }
    else if (checkProduction(node, 4, "IDENT", "[", "ConstExp", "]"))
    {
        // Infer: int a[2];
        mySymbol *var_symbol = createSymbol(node->left->content, VAR);
        var_symbol->type = type;
        var_symbol->type->data_type = ARRAY;
        var_symbol->type->array.size = 0;
        var_symbol->type->array.elem = nullptr;

        analyseConstExp(node->left->right->right, var_symbol);

        checkArray(var_symbol, node->left->lineno);
        insert(symbol_table, var_symbol);
    }
    else if (checkProduction(node, 3, "IDENT", "=", "InitVal"))
    {
        // Infer: int a = 1;
        mySymbol *var_symbol = createSymbol(node->left->content, VAR);
        var_symbol->type = type;
        var_symbol->type->data_type = BASIC;

        analyseInitVal(node->left->right->right, var_symbol);

        insert(symbol_table, var_symbol);
    }
    else if (checkProduction(node, 6, "IDENT", "[", "ConstExp", "]", "=", "InitVal"))
    {
        // Infer: int a[2] = {1, 2};
        mySymbol *var_symbol = createSymbol(node->left->content, VAR);
        var_symbol->type = type;
        var_symbol->type->data_type = ARRAY;
        var_symbol->type->value = 65535;
        var_symbol->type->array.size = 0;
        var_symbol->type->array.elem = nullptr;

        analyseConstExp(node->left->right->right, var_symbol);
        analyseInitVal(node->left->right->right->right->right->right, var_symbol);

        checkArray(var_symbol, node->left->lineno);
        insert(symbol_table, var_symbol);
    }
    else
    {
        printProductionError(node, "VarDef");
    }
}

void analyseInitVal(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d InitVal:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "Exp"))
    {
        analyseExp(node->left, symb);
    }
    else if (checkProduction(node, 2, "{", "}"))
    {
    }
    else if (checkProduction(node, 4, "{", "Exp", "Exp_list", "}"))
    {
        analyseExp(node->left->right, symb);
        analyseExp_list(node->left->right->right, symb);
    }
    else
    {
        printProductionError(node, "InitVal");
    }
}

void analyseExp_list(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d Exp_list:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 3, "Exp_list", ",", "Exp"))
    {
        analyseExp_list(node->left, symb);
        analyseExp(node->left->right->right, symb);
    }
    else if (checkProduction(node, 1, "Null"))
    {
    }
    else
    {
        printProductionError(node, "Exp_list");
    }
}

void analyseFuncDef(const grammarTree *node)
{
    if (debug)
    {
        printf("analyse %d FuncDef:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 6, "BType", "IDENT", "(", "FuncFParams", ")", "Block"))
    {
        // Infer: int f(...){}
        mySymbol *func_symbol = createSymbol(node->left->right->content, FUNC);
        myData *func_ret_type = analyseBType(node->left);

        func_symbol->func->ret_type = func_ret_type;
        func_symbol->func->ret_type->data_type = BASIC;
        func_symbol->func->ret_type->basic = INT;
        func_symbol->func->ret_type->is_r_value = true;

        myParam *tmp = new myParam;
        tmp->type = nullptr;
        tmp->next = nullptr;
        func_symbol->func->param_list = tmp;

        analyseFuncFParams(node->left->right->right->right, func_symbol);
        myParam *p;
        int param_nums = 0;
        p = func_symbol->func->param_list->next;
        while (p != nullptr)
        {
            param_nums++;
            p = p->next;
        }
        func_symbol->func->param_num = param_nums;

        insert(symbol_table, func_symbol);

        analyseBlock(node->left->right->right->right->right->right, func_symbol);
    }
    else
    {
        printProductionError(node, "FuncDef");
    }
}

void analyseFuncFParams(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d FuncFParams:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 2, "FuncFParam", "FuncFParam_list"))
    {
        analyseFuncFParam(node->left, symb);
        analyseFuncFParam_list(node->left->right, symb);
    }
    else if (checkProduction(node, 1, "Null"))
    {
    }
    else
    {
        printProductionError(node, "FuncFParams");
    }
}

void analyseFuncFParam_list(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d FuncFParam_list:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 3, "FuncFParam_list", ",", "FuncFParam"))
    {
        analyseFuncFParam_list(node->left, symb);
        analyseFuncFParam(node->left->right->right, symb);
    }
    else if (checkProduction(node, 1, "Null"))
    {
    }
    else
    {
        printProductionError(node, "FuncFParam_list");
    }
}

void analyseFuncFParam(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d FuncFParam:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 2, "BType", "IDENT"))
    {
        myData *param_type = analyseBType(node->left);
        param_type->data_type = BASIC;
        myParam *new_param = new myParam;
        new_param->type = param_type;
        new_param->next = nullptr;

        addNewParamToFunc(new_param, symb);

        // Param's name is not important
    }
    else if (checkProduction(node, 4, "BType", "IDENT", "[", "]"))
    {
        myData *param_type = analyseBType(node->left);
        param_type->data_type = ARRAY;
        myParam *new_param = new myParam;
        new_param->type = param_type;
        new_param->next = nullptr;

        addNewParamToFunc(new_param, symb);

        // Param's name is not important
    }
    else
    {
        printProductionError(node, "FuncFParam");
    }
}

void analyseBlock(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d Block:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 3, "{", "BlockItem_list", "}"))
    {
        analyseBlockItem_list(node->left->right, symb);
    }
    else
    {
        printProductionError(node, "Block");
    }
}

void analyseBlockItem_list(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d BlockItem_list:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 2, "BlockItem_list", "BlockItem"))
    {
        analyseBlockItem_list(node->left, symb);
        analyseBlockItem(node->left->right, symb);
    }
    else if (checkProduction(node, 1, "Null"))
    {
    }
    else
    {
        printProductionError(node, "BlockItem_list");
    }
}

void analyseBlockItem(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d BlockItem:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "Decl"))
    {
        analyseDecl(node->left);
    }
    else if (checkProduction(node, 1, "Stmt"))
    {
        analyseStmt(node->left, symb);
    }
    else
    {
        printProductionError(node, "BlockItem");
    }
}

void analyseStmt(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d Stmt:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 4, "LVal", "=", "Exp", ";"))
    {
        analyseLVal(node->left, symb);
        analyseExp(node->left->right->right, symb);
    }
    else if (checkProduction(node, 2, "Exp", ";"))
    {
        analyseExp(node->left, symb);
    }
    else if (checkProduction(node, 1, ";"))
    {
    }
    else if (checkProduction(node, 1, "Block"))
    {
        analyseBlock(node->left, symb);
    }
    else if (checkProduction(node, 5, "IF", "(", "Cond", ")", "Stmt"))
    {
        analyseCond(node->left->right->right, symb);
        analyseStmt(node->left->right->right->right->right, symb);
    }
    else if (checkProduction(node, 7, "IF", "(", "Cond", ")", "Stmt", "ELSE", "Stmt"))
    {

        analyseCond(node->left->right->right, symb);
        analyseStmt(node->left->right->right->right->right, symb);
        analyseStmt(node->left->right->right->right->right->right, symb);
    }
    else if (checkProduction(node, 5, "WHILE", "(", "Cond", ")", "Stmt"))
    {
        analyseCond(node->left->right->right, symb);
        analyseStmt(node->left->right->right->right->right, symb);
    }
    else if (checkProduction(node, 2, "BREAK", ";"))
    {
    }
    else if (checkProduction(node, 2, "CONTINUE", ";"))
    {
    }
    else if (checkProduction(node, 2, "RETURN", ";"))
    {
    }
    else if (checkProduction(node, 3, "RETURN", "Exp", ";"))
    {
        analyseExp(node->left->right, symb);
    }
    else
    {
        printProductionError(node, "Stmt");
    }
}

void analyseExp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d Exp:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "AddExp"))
    {
        analyseAddExp(node->left, symb);
    }
    else
    {
        printProductionError(node, "AddExp");
    }
}

void analyseCond(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d Cond:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "LOrExp"))
    {
        analyseLOrExp(node->left, symb);
    }
    else
    {
        printProductionError(node, "Cond");
    }
}

void analyseLVal(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d LVal:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "IDENT"))
    {
    }
    else if (checkProduction(node, 4, "IDENT", "[", "Exp", "]"))
    {
        analyseExp(node->left->right->right, symb);
    }
    else
    {
        printProductionError(node, "LVal");
    }
}

void analysePrimaryExp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d PrimaryExp:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 3, "(", "Exp", ")"))
    {
        analyseExp(node->left->right, symb);
    }
    else if (checkProduction(node, 1, "LVal"))
    {
        analyseLVal(node->left, symb);
    }
    else if (checkProduction(node, 1, "NUMBER"))
    {
        if (symb->type->data_type == BASIC)
        {
            symb->type->value = str2int(node->left->content);
        }
        else if (symb->type->data_type == ARRAY)
        {
            if (symb->type->array.size == 0)
            {
                int array_size = str2int(node->left->content);
                if (array_size <= 0)
                {
                    fprintf(stderr, "Error [Semantic] at Line %d, Col %d: Wrong array size %d.\n", 1, 1, array_size);
                }
                else
                {
                    symb->type->array.size = array_size;
                    symb->type->array.elem = nullptr;
                }
            }
            else if (symb->type->array.size > 0)
            {
                myData *new_ele = new myData;
                new_ele->data_type = ARRAY;
                new_ele->basic = INT;
                new_ele->is_r_value = false;
                new_ele->value = str2int(node->left->content);
                new_ele->array.size = symb->type->array.size;
                new_ele->array.elem = nullptr;
                addNewEleToArray(new_ele, symb);
            }
        }
    }
    else
    {
        printProductionError(node, "PrimaryExp");
    }
}

void analyseUnaryExp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d UnaryExp:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "PrimaryExp"))
    {
        analysePrimaryExp(node->left, symb);
    }
    else if (checkProduction(node, 3, "IDENT", "(", ")"))
    {
    }
    else if (checkProduction(node, 4, "IDENT", "(", "FuncRParams", ")"))
    {
        analyseFuncRParams(node->left->right->right, symb);
    }
    else if (checkProduction(node, 2, "UnaryOp", "UnaryExp"))
    {
        analyseUnaryOp(node->left, symb);
        analyseUnaryExp(node->left->right, symb);
    }
    else
    {
        printProductionError(node, "UnaryExp");
    }
}

void analyseUnaryOp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d UnaryOp:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "+"))
    {
    }
    else if (checkProduction(node, 1, "-"))
    {
    }
    else if (checkProduction(node, 1, "!"))
    {
    }
    else
    {
        printProductionError(node, "UnaryOp");
    }
}

void analyseFuncRParams(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d FuncRParams:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 2, "Exp", "Exp_list"))
    {
        analyseExp(node->left, symb);
        analyseExp_list(node->left->right, symb);
    }
    else if (checkProduction(node, 1, "Null"))
    {
    }
    else
    {
        printProductionError(node, "FuncRParams");
    }
}

void analyseAddExp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d AddExp:\t", node->id);
    }
    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "MulExp"))
    {
        analyseMulExp(node->left, symb);
    }
    else if (checkProduction(node, 3, "AddExp", "+", "MulExp"))
    {
        analyseAddExp(node->left, symb);
        analyseMulExp(node->left->right->right, symb);
    }
    else if (checkProduction(node, 3, "AddExp", "-", "MulExp"))
    {
        analyseAddExp(node->left, symb);
        analyseMulExp(node->left->right->right, symb);
    }
    else
    {
        printProductionError(node, "AddExp");
    }
}

void analyseMulExp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d MulExp:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "UnaryExp"))
    {
        analyseUnaryExp(node->left, symb);
    }
    else if (checkProduction(node, 3, "MulExp", "*", "UnaryExp"))
    {
        analyseMulExp(node->left, symb);
        analyseUnaryExp(node->left->right->right, symb);
    }
    else if (checkProduction(node, 3, "MulExp", "/", "UnaryExp"))
    {
        analyseMulExp(node->left, symb);
        analyseUnaryExp(node->left->right->right, symb);
    }
    else if (checkProduction(node, 3, "MulExp", "%", "UnaryExp"))
    {
        analyseMulExp(node->left, symb);
        analyseUnaryExp(node->left->right->right, symb);
    }
    else
    {
        printProductionError(node, "MulExp");
    }
}

void analyseRelExp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d RelExp:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "AddExp"))
    {
        analyseAddExp(node->left, symb);
    }
    else if (checkProduction(node, 3, "RelExp", "<", "AddExp"))
    {
        analyseRelExp(node->left, symb);
        analyseAddExp(node->left->right->right, symb);
    }
    else if (checkProduction(node, 3, "RelExp", ">", "AddExp"))
    {
        analyseRelExp(node->left, symb);
        analyseAddExp(node->left->right->right, symb);
    }
    else if (checkProduction(node, 3, "RelExp", "LE_OP", "AddExp"))
    {
        analyseRelExp(node->left, symb);
        analyseAddExp(node->left->right->right, symb);
    }
    else if (checkProduction(node, 3, "RelExp", "GE_OP", "AddExp"))
    {
        analyseRelExp(node->left, symb);
        analyseAddExp(node->left->right->right, symb);
    }
    else
    {
        printProductionError(node, "RelExp");
    }
}

void analyseEqExp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d EqExp:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "RelExp"))
    {
        analyseRelExp(node->left, symb);
    }
    else if (checkProduction(node, 3, "EqExp", "EQ_OP", "RelExp"))
    {
        analyseEqExp(node->left, symb);
        analyseRelExp(node->left->right->right, symb);
    }
    else if (checkProduction(node, 3, "EqExp", "NE_OP", "RelExp"))
    {
        analyseEqExp(node->left, symb);
        analyseRelExp(node->left->right->right, symb);
    }
    else
    {
        printProductionError(node, "EqExp");
    }
}

void analyseLAndExp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d LAndExp:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "EqExp"))
    {
        analyseEqExp(node->left, symb);
    }
    else if (checkProduction(node, 3, "LAndExp", "AND_OP", "EqExp"))
    {
        analyseLAndExp(node->left, symb);
        analyseEqExp(node->left->right->right, symb);
    }
    else
    {
        printProductionError(node, "LAndExp");
    }
}

void analyseLOrExp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d LOrExp:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "LAndExp"))
    {
        analyseLAndExp(node->left, symb);
    }
    else if (checkProduction(node, 3, "LOrExp", "OR_OP", "LAndExp"))
    {
        analyseLOrExp(node->left, symb);
        analyseLAndExp(node->left->right->right, symb);
    }
    else
    {
        printProductionError(node, "LOrExp");
    }
}

void analyseConstExp(const grammarTree *node, mySymbol *symb)
{
    if (debug)
    {
        printf("analyse %d ConstExp:\t", node->id);
    }

    if (node == nullptr)
    {
        return;
    }
    if (checkProduction(node, 1, "AddExp"))
    {
        analyseAddExp(node->left, symb);
    }
    else
    {
        printProductionError(node, "ConstExp");
    }
}

void destroySymbolTable()
{
    delete symbol_table;
}

void printProductionError(const grammarTree *node, const char *msg)
{
    grammarTree *child = node->left;
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
        while (p != nullptr)
        {
            count++;
            printf("[Symbol %d]\n", count);
            mySymbol *s = p->symbol;
            string symbol_type[] = {"VAR", "FUNC", "CONST"};
            printf("Name: %s\nSymbol Type: %s\n", s->name.c_str(), symbol_type[s->symbol_type].c_str());
            if (s->symbol_type == FUNC)
            {
                printf("Return Type: \n");
                printDataType(s->func->ret_type);
                printf("Parameter Nums: %d\n", s->func->param_num);
                printf("Parameter List: ");
                myParam *pl = s->func->param_list->next;
                if (pl == nullptr)
                {
                    printf("Null\n");
                }
                else
                {
                    printf("\n");
                    int i = 1;
                    for (myParam *pa = pl; pa != nullptr; pa = pa->next)
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

void addNewEleToArray(myData *new_ele, mySymbol *symb)
{
    myData *rear;

    rear = symb->type;
    while (rear->array.elem != nullptr)
    {
        rear = rear->array.elem;
    }
    rear->array.elem = new_ele;
}

void addNewParamToFunc(myParam *new_param, mySymbol *symb)
{
    myParam *rear;

    rear = symb->func->param_list;
    while (rear->next != nullptr)
    {
        rear = rear->next;
    }
    rear->next = new_param;
}

int isNewSemanticError(int error_lineno)
{
    if (last_semantic_error_lineno != error_lineno)
    {
        semantic_error_num++;
        last_semantic_error_lineno = error_lineno;
        return 1;
    }
    else
    {
        return 0;
    }
}