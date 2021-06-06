#include "Parser.h"

// Global variables
bool debug = false;
myHashSet symbol_table;

// error
int semantic_error_num = 0;
int last_semantic_error_lineno = 0;

// Array
bool check_array_index = false;
bool check_array_init = false;

// Const init
bool check_const_init = false;
bool check_var_init = false;

// Exp
bool cal_exp_val = false;
bool check_assign = false;
myDataType cur_op = BASIC;
bool check_compare = false;
bool set_init = false;

// Func ret
bool cal_ret_val = false;
bool has_return = false;
myData *func_ret;

// Func call
bool cal_call_val = false;
vector<myParam *> func_call;

// Domain
bool is_last_domain_func = false;
string cur_domain_name;
int domain_id = 1;
vector<mySymbol *> domain;

// Array
bool cal_array_type = false;

// Control Sentences
bool while_stmt = false;

void addBiuldInFunc()
{
    myData *int_type = new myData;
    int_type->data_type = BASIC;
    int_type->basic = INT;
    int_type->is_r_value = false;

    mySymbol *getint = createSymbol("getint", FUNC);
    getint->func->ret_type = int_type;
    getint->func->param_num = 0;
    myParam *tmp = new myParam;
    tmp->type = nullptr;
    tmp->next = nullptr;
    getint->func->param_list = tmp;
    insert(symbol_table, getint);

    mySymbol *putint = createSymbol("putint", FUNC);
    putint->func->ret_type = int_type;
    putint->func->param_num = 1;
    myParam *tmp1 = new myParam;
    tmp1->type = nullptr;
    tmp1->next = nullptr;
    putint->func->param_list = tmp1;
    myParam *para1 = new myParam;
    para1->type = int_type;
    para1->next = nullptr;
    addNewParamToParamList(para1, putint->func->param_list);
    insert(symbol_table, putint);

    mySymbol *putch = createSymbol("putch", FUNC);
    putch->func->ret_type = int_type;
    putch->func->param_num = 1;
    myParam *tmp2 = new myParam;
    tmp2->type = nullptr;
    tmp2->next = nullptr;
    putch->func->param_list = tmp2;
    myParam *para2 = new myParam;
    para2->type = int_type;
    para2->next = nullptr;
    addNewParamToParamList(para2, putch->func->param_list);
    insert(symbol_table, putch);
}

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
    if (cur_size == 0)
    {
        if (symb->symbol_type == CONST)
        {
            if (isNewSemanticError(lineno))
            {
                fprintf(stderr, "Error [Semantic] at Line %d: Define const array %s without initialization.\n", lineno, symb->name.c_str());
                return;
            }
        }
        int remain = array_size - cur_size;
        while (remain > 0)
        {
            myData *new_ele = new myData;
            new_ele->data_type = ARRAY;
            new_ele->basic = INT;
            new_ele->is_r_value = false;
            new_ele->array.size = symb->type->array.size;
            new_ele->array.elem = nullptr;
            addNewEleToArray(new_ele, symb);
            remain--;
        }
        return;
    }
    if (cur_size < array_size)
    {
        if (symb->symbol_type == CONST)
        {
            if (isNewSemanticError(lineno))
            {
                fprintf(stderr, "Error [Semantic] at Line %d: Define const array %s with incomplete initialization size %d < %d.\n", lineno, symb->name.c_str(), cur_size, array_size);
                return;
            }
        }
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
        if (isNewSemanticError(lineno))
        {
            fprintf(stderr, "Error [Semantic] at Line %d: Define array %s with initialization size %d > %d.\n", lineno, symb->name.c_str(), cur_size, array_size);
        }
    }
}

bool checkRepeatFuncDef(mySymbol *symb, int lineno)
{
    string name = symb->name;
    if (!insert(symbol_table, symb))
    {
        if (isNewSemanticError(lineno))
        {
            fprintf(stderr, "Error [Semantic] at Line %d: FUNC name %s has already been declared.\n", lineno, name.c_str());
            return false;
        }
    }

    return true;
}

void checkRepeatVarDef(mySymbol *symb, int lineno)
{
    string name = symb->name;
    string symbol_type[] = {"VAR", "FUNC", "CONST"};
    mySymbol *cur_domain = domain.back();

    if (cur_domain->symbol_type == FUNC)
    {
        myParam *p = cur_domain->func->param_list->next;
        while (p != nullptr)
        {
            if (name == p->para_name)
            {
                if (isNewSemanticError(lineno))
                {
                    fprintf(stderr, "Error [Semantic] at Line %d: %s name %s has already been declared in FUNC %s's param.\n", lineno, symbol_type[symb->symbol_type].c_str(), name.c_str(), cur_domain_name.c_str());
                    return;
                }
            }
            p = p->next;
        }
    }

    if (!insert(symbol_table, symb))
    {
        if (isNewSemanticError(lineno))
        {
            fprintf(stderr, "Error [Semantic] at Line %d: %s name %s has already been declared.\n", lineno, symbol_type[symb->symbol_type].c_str(), name.c_str());
            return;
        }
    }
}

void checkFuncRet(int lineno)
{
    has_return = true;
    string data_type[] = {"BASIC", "ARRAY"};
    mySymbol *cur_domain = new mySymbol;
    for (unsigned int i = domain.size() - 1; i >= 0; i--)
    {
        if (domain.at(i)->symbol_type == FUNC)
        {
            cur_domain = domain.at(i);
            break;
        }
    }
    if (func_ret->data_type != cur_domain->func->ret_type->data_type)
    {
        if (isNewSemanticError(lineno))
        {
            fprintf(stderr, "Error [Semantic] at Line %d: Return type %s mismatchs with FUNC %s definition type %s.\n", lineno, data_type[func_ret->data_type].c_str(), cur_domain->name.c_str(), data_type[cur_domain->func->ret_type->data_type].c_str());
        }
    }
}

void checkFuncCall(string func_name, int lineno)
{
    string data_type[] = {"BASIC", "ARRAY"};
    for (int i = 0; i < symbol_table->size; i++)
    {
        mySymbolList *p = symbol_table->buckets[i].symbol_list;
        while (p != nullptr)
        {
            mySymbol *s = p->symbol;
            if (func_name == s->name)
            {
                if (func_call.size() != s->func->param_num)
                {
                    if (isNewSemanticError(lineno))
                    {
                        fprintf(stderr, "Error [Semantic] at Line %d: The number of function call arguments %d does not match the definition %d.\n", lineno, func_call.size(), s->func->param_num);
                        return;
                    }
                }

                vector<myParam *>::iterator p1 = func_call.begin();
                myParam *p2 = s->func->param_list->next;
                while (p2 != nullptr)
                {
                    if ((*p1)->type->data_type != p2->type->data_type)
                    {
                        if (isNewSemanticError(lineno))
                        {
                            fprintf(stderr, "Error [Semantic] at Line %d: Func %s call %s(%s) mismatches with definition %s(%s).\n", lineno, func_name.c_str(), (*p1)->para_name.c_str(), data_type[(*p1)->type->data_type].c_str(), p2->para_name.c_str(), data_type[p2->type->data_type].c_str());
                            return;
                        }
                    }

                    p1++;
                    p2 = p2->next;
                }
            }
            p = p->next;
        }
    }
}

bool checkNotDef(string name, int lineno, string form)
{
    // Check in Current Domain, then the upper domain
    mySymbol *cur_domain = new mySymbol;
    string cur_name;
    vector<mySymbol *>::reverse_iterator iter = domain.rbegin();
    for (; iter != domain.rend(); ++iter)
    {

        cur_domain = *iter;
        string cur_name;
        if (form != "FUNC") // Func itself as a domain
        {
            cur_name = cur_domain->name + ":" + name;
        }
        else
        {
            cur_name = name;
        }
        for (int i = 0; i < symbol_table->size; i++)
        {
            mySymbolList *p = symbol_table->buckets[i].symbol_list;
            while (p != nullptr)
            {
                mySymbol *s = p->symbol;

                if (cur_name == s->name)
                {
                    if (form == "ARRAY" && s->type->data_type != ARRAY)
                    {
                        if (isNewSemanticError(lineno))
                        {
                            fprintf(stderr, "Error [Semantic] at Line %d: %s is not an ARRAY.\n", lineno, name.c_str());
                            return false;
                        }
                    }
                    if (form == "FUNC" && s->symbol_type != FUNC)
                    {

                        if (isNewSemanticError(lineno))
                        {
                            fprintf(stderr, "Error [Semantic] at Line %d: %s is not an FUNC.\n", lineno, name.c_str());
                            return false;
                        }
                    }
                    getDATA(s->type, cur_name, form, lineno);
                    return true;
                }
                p = p->next;
            }
        }
        // Check in Func Param List
        // Suppose func can't be func's param
        if (cur_domain->symbol_type == FUNC && form != "FUNC")
        {
            myParam *param = cur_domain->func->param_list->next;
            while (param != nullptr)
            {
                if (param->para_name == cur_name)
                {
                    getDATA(param->type, cur_name, form, lineno);
                    return true;
                }
                param = param->next;
            }
        }
    }
    if (isNewSemanticError(lineno))
    {
        fprintf(stderr, "Error [Semantic] at Line %d: Undefined reference to %s %s.\n", lineno, form.c_str(), name.c_str());
        return false;
    }
    return false;
}

void getDATA(myData *DATA, string name, string form, int lineno)
{
    if (check_var_init)
    {
        if (DATA->data_type == ARRAY)
        {
            if (isNewSemanticError(lineno))
            {
                fprintf(stderr, "Error [Semantic] at Line %d: Can't initialize var with ARRAY %s.\n", lineno, name.c_str());
            }
        }
    }

    if (form == "VAR")
    {
        if (cal_array_type)
        {
            if (!cal_call_val) // avoid array[func(array)]
            {
                if (DATA->data_type == ARRAY)
                {
                    if (isNewSemanticError(lineno))
                    {
                        fprintf(stderr, "Error [Semantic] at Line %d: ARRAY %s can't be another array's index.\n", lineno, name.c_str());
                    }
                }
            }
        }
        if (cal_exp_val)
        {
            if (!cal_call_val)
            { //  avoid func(array) + a + b
                if (DATA->data_type == ARRAY)
                {
                    if (isNewSemanticError(lineno))
                    {
                        fprintf(stderr, "Error [Semantic] at Line %d: Can't mix ARRAY %s in INT expression.\n", lineno, name.c_str());
                    }
                }
            }
            if (check_assign)
            {
                if (DATA->is_r_value == true)
                {
                    if (isNewSemanticError(lineno))
                    {
                        fprintf(stderr, "Error [Semantic] at Line %d: Can't mix a LVal %s in calculation.\n", lineno, name.c_str());
                    }
                }
            }
            if (check_compare)
            {
                if (!set_init)
                {
                    cur_op = DATA->data_type;
                    set_init = true;
                }
                else
                {
                    if (cur_op != DATA->data_type)
                    {
                        if (isNewSemanticError(lineno))
                        {
                            fprintf(stderr, "Error [Semantic] at Line %d: Can't compare between two different types.\n", lineno);
                        }
                    }
                }
            }
        }
        if (cal_ret_val)
        {
            func_ret = DATA;
        }
        if (cal_call_val)
        {
            myParam *new_param = new myParam;
            new_param->type = DATA;
            new_param->next = nullptr;
            new_param->para_name = name;
            func_call.push_back(new_param);
        }
    }
    else if (form == "ARRAY")
    {
        // Return an ele of the array
        if (cal_exp_val)
        {
            if (check_assign)
            {
                if (DATA->is_r_value)
                {
                    if (isNewSemanticError(lineno))
                    {
                        fprintf(stderr, "Error [Semantic] at Line %d: Can't mix ARRAY %s in INT expression.\n", lineno, name.c_str());
                    }
                }
            }
            if (check_compare)
            {
                if (!set_init)
                {
                    cur_op = DATA->data_type;
                    set_init = true;
                }
                else
                {
                    if (cur_op != DATA->data_type)
                    {
                        if (isNewSemanticError(lineno))
                        {
                            fprintf(stderr, "Error [Semantic] at Line %d: Can't compare between two different types.\n", lineno);
                        }
                    }
                }
            }
        }
        if (cal_ret_val)
        {
            myData *tmp_data = new myData;
            tmp_data->data_type = BASIC;
            tmp_data->basic = INT;
            tmp_data->is_r_value = DATA->is_r_value;
            func_ret = tmp_data;
        }
        if (cal_call_val)
        {
            myParam *tmp_param = new myParam;
            myData *tmp_data = new myData;
            tmp_data->data_type = BASIC;
            tmp_data->basic = INT;
            tmp_data->is_r_value = DATA->is_r_value;
            tmp_param->type = tmp_data;
            tmp_param->next = nullptr;
            tmp_param->para_name = name + ":ele";
            func_call.push_back(tmp_param);
        }
    }
    else
    {
        // Means we call func
        if (cal_exp_val)
        {
            // Func must return int;
            if (check_assign)
            {
                if (isNewSemanticError(lineno))
                {
                    fprintf(stderr, "Error [Semantic] at Line %d: Can't assign value to FUNC %s", lineno, name.c_str());
                }
            }
            if (check_compare)
            {
                if (!set_init)
                {
                    cur_op = DATA->data_type;
                    set_init = true;
                }
                else
                {
                    if (cur_op != DATA->data_type)
                    {
                        if (isNewSemanticError(lineno))
                        {
                            fprintf(stderr, "Error [Semantic] at Line %d: Can't compare between two different types.\n", lineno);
                        }
                    }
                }
            }
        }
        if (cal_ret_val)
        {
            myData *tmp = new myData;
            tmp->data_type = BASIC;
            tmp->is_r_value = DATA->is_r_value;
            tmp->basic = INT;
            func_ret = tmp;
        }
        if (cal_call_val)
        {
            myData *tmp = new myData;
            tmp->data_type = BASIC;
            tmp->is_r_value = false;
            tmp->basic = INT;
            myParam *tmp_param = new myParam;
            tmp_param->type = tmp;
            tmp_param->para_name = name + ":return";
            tmp_param->next = nullptr;
            func_call.push_back(tmp_param);
        }
    }
}

void checkControl(int lineno, string type)
{
    // Check in Current Domain, then the upper domain
    mySymbol *cur_domain = new mySymbol;
    bool error = true;
    vector<mySymbol *>::reverse_iterator iter = domain.rbegin();
    for (; iter != domain.rend(); ++iter)
    {
        if ((*iter)->symbol_type == VAR)
        { // while domain
            error = false;
            break;
        }
    }
    if (error)
    {
        if (isNewSemanticError(lineno))
        {
            fprintf(stderr, "Error [Semantic] at Line %d: \'%s\' can be only used in loop.\n", lineno, type.c_str());
        }
    }
}

int semanticAnalysis(const grammarTree *root, bool verbose = false)
{
    debug = verbose;
    const grammarTree *syntax = root;
    semanticInit(syntax);
    return semantic_error_num;
}

void semanticInit(const grammarTree *root)
{
    symbol_table = initHashSet(HASH_SIZE);
    addDomain("global", CONST);
    addBiuldInFunc();

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

void addDomain(string domain_name, mySymbolType domain_type)
{
    /*Add a special func: global domain*/
    mySymbol *const_domain = createSymbol(domain_name, domain_type);

    myData *tmp = new myData;
    tmp->data_type = BASIC;
    tmp->basic = INT;
    tmp->is_r_value = true;
    const_domain->type = tmp;

    insert(symbol_table, const_domain);
    domain.push_back(const_domain);
    cur_domain_name = domain.back()->name;
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
    else if (checkProduction(node, 1, "none"))
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
        mySymbol *constant_symbol = createSymbol(cur_domain_name + ":" + node->left->content, CONST);
        constant_symbol->type = type;

        check_const_init = true;
        analyseConstInitVal(node->left->right->right, constant_symbol);
        check_const_init = false;

        constant_symbol->type->data_type = BASIC;
        constant_symbol->type->is_r_value = true;

        checkRepeatVarDef(constant_symbol, node->left->lineno);
    }
    else if (checkProduction(node, 6, "IDENT", "[", "ConstExp", "]", "=", "ConstInitVal"))
    {
        // Infer: must be const int a[2] = {1, 2};
        mySymbol *constant_symbol = createSymbol(cur_domain_name + ":" + node->left->content, CONST);
        constant_symbol->type = type;
        constant_symbol->type->data_type = ARRAY;
        constant_symbol->type->is_r_value = true;

        constant_symbol->type->value = 65535;
        constant_symbol->type->array.size = 0;
        constant_symbol->type->array.elem = nullptr;

        check_array_index = true;
        analyseConstExp(node->left->right->right, constant_symbol);
        check_array_index = false;

        check_array_init = true;
        analyseConstInitVal(node->left->right->right->right->right->right, constant_symbol);
        check_array_init = false;

        checkArray(constant_symbol, node->left->lineno);
        checkRepeatVarDef(constant_symbol, node->left->lineno);
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
    else if (checkProduction(node, 1, "none"))
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
    else if (checkProduction(node, 1, "none"))
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
        mySymbol *var_symbol = createSymbol(cur_domain_name + ":" + node->left->content, VAR);
        var_symbol->type = type;
        var_symbol->type->data_type = BASIC;
        var_symbol->type->is_r_value = false;
        checkRepeatVarDef(var_symbol, node->left->lineno);
    }
    else if (checkProduction(node, 4, "IDENT", "[", "ConstExp", "]"))
    {
        // Infer: int a[2];
        mySymbol *var_symbol = createSymbol(cur_domain_name + ":" + node->left->content, VAR);
        var_symbol->type = type;
        var_symbol->type->data_type = ARRAY;
        var_symbol->type->is_r_value = false;
        var_symbol->type->array.size = 0;
        var_symbol->type->array.elem = nullptr;

        check_array_index = true;
        analyseConstExp(node->left->right->right, var_symbol);
        check_array_index = false;

        checkArray(var_symbol, node->left->lineno);
        checkRepeatVarDef(var_symbol, node->left->lineno);
    }
    else if (checkProduction(node, 3, "IDENT", "=", "InitVal"))
    {
        // Infer: int a = 1;
        mySymbol *var_symbol = createSymbol(cur_domain_name + ":" + node->left->content, VAR);
        var_symbol->type = type;
        var_symbol->type->data_type = BASIC;
        var_symbol->type->is_r_value = false;

        check_var_init = true;
        analyseInitVal(node->left->right->right, var_symbol);
        check_var_init = false;

        checkRepeatVarDef(var_symbol, node->left->lineno);
    }
    else if (checkProduction(node, 6, "IDENT", "[", "ConstExp", "]", "=", "InitVal"))
    {
        // Infer: int a[2] = {1, 2};
        mySymbol *var_symbol = createSymbol(cur_domain_name + ":" + node->left->content, VAR);
        var_symbol->type = type;
        var_symbol->type->data_type = ARRAY;
        var_symbol->type->is_r_value = false;
        var_symbol->type->value = 65535;
        var_symbol->type->array.size = 0;
        var_symbol->type->array.elem = nullptr;

        check_array_index = true;
        analyseConstExp(node->left->right->right, var_symbol);
        check_array_index = false;

        check_array_init = true;
        analyseInitVal(node->left->right->right->right->right->right, var_symbol);
        check_array_init = false;

        checkArray(var_symbol, node->left->lineno);
        checkRepeatVarDef(var_symbol, node->left->lineno);
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
    else if (checkProduction(node, 1, "none"))
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
        func_symbol->func->ret_type->is_r_value = true;

        // FUNC try to gen a new domain
        // If FUNC definition wrong, no domain, so only update name
        cur_domain_name = func_symbol->name;

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

        if (checkRepeatFuncDef(func_symbol, node->left->lineno))
        {
            is_last_domain_func = true;
            domain.push_back(func_symbol);
            cur_domain_name = domain.back()->name;

            // Only success FUNC definition will lead on analyse
            // However, variables not act like this
            analyseBlock(node->left->right->right->right->right->right, func_symbol);

            domain.pop_back();
            cur_domain_name = domain.back()->name;

            if (!has_return)
            {
                if (isNewSemanticError(node->left->lineno))
                {
                    fprintf(stderr, "Error [Semantic] at Line %d: FUNC %s doesn't return.\n", node->left->lineno, func_symbol->name.c_str());
                }
            }
            else
            {
                has_return = false;
            }
        }
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
    else if (checkProduction(node, 1, "none"))
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
    else if (checkProduction(node, 1, "none"))
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
        param_type->is_r_value = false;
        myParam *new_param = new myParam;
        new_param->type = param_type;
        new_param->next = nullptr;
        new_param->para_name = cur_domain_name + ":" + node->left->right->content;

        addNewParamToParamList(new_param, symb->func->param_list);
    }
    else if (checkProduction(node, 4, "BType", "IDENT", "[", "]"))
    {
        myData *param_type = analyseBType(node->left);
        param_type->data_type = ARRAY;
        param_type->is_r_value = false;
        myParam *new_param = new myParam;
        new_param->type = param_type;
        new_param->next = nullptr;
        new_param->para_name = cur_domain_name + ":" + node->left->right->content;

        addNewParamToParamList(new_param, symb->func->param_list);
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
    else if (checkProduction(node, 1, "none"))
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
        // Infer: a=b;
        cal_exp_val = true;

        check_assign = true;
        analyseLVal(node->left, symb);
        check_assign = false;

        analyseExp(node->left->right->right, symb);
        cal_exp_val = false;
    }
    else if (checkProduction(node, 2, "Exp", ";"))
    {
        // Infer: a;
        analyseExp(node->left, symb);
    }
    else if (checkProduction(node, 1, ";"))
    {
        // Infer: ;
    }
    else if (checkProduction(node, 1, "Block"))
    {
        // Infer: {}
        if (!is_last_domain_func)
        {
            string domain_name = "Block" + int2str(domain_id);
            if (while_stmt)
            {
                addDomain(domain_name, VAR);
                while_stmt = false;
            }
            else
            {
                addDomain(domain_name, CONST);
            }
            domain_id++;
            cur_domain_name = domain.back()->name;
            analyseBlock(node->left, symb);
            domain.pop_back();
            cur_domain_name = domain.back()->name;
        }
        else
        {
            is_last_domain_func = false;
        }
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
        analyseStmt(node->left->right->right->right->right->right->right, symb);
    }
    else if (checkProduction(node, 5, "WHILE", "(", "Cond", ")", "Stmt"))
    {
        analyseCond(node->left->right->right, symb);
        while_stmt = true;
        analyseStmt(node->left->right->right->right->right, symb);
        while_stmt = false;
    }
    else if (checkProduction(node, 2, "BREAK", ";"))
    {
        checkControl(node->left->lineno, "break");
    }
    else if (checkProduction(node, 2, "CONTINUE", ";"))
    {
        checkControl(node->left->lineno, "continue");
    }
    else if (checkProduction(node, 3, "RETURN", "Exp", ";"))
    {
        // One function may have many return
        cal_ret_val = true;
        analyseExp(node->left->right, symb);
        // printf("\n\n%d\n\n", );
        checkFuncRet(node->left->lineno);
        cal_ret_val = false;
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
        // Infer: BASIC
        myData *DATA = analyseBType(node->left);
        if (!checkNotDef(node->left->content, node->left->lineno, "VAR"))
        {
            return;
        }
        if (check_array_index)
        {
            if (isNewSemanticError(node->left->lineno))
            {
                fprintf(stderr, "Error [Semantic] at Line %d: Can't define an array's size with NOT-NUMBER %s.\n", node->left->lineno, node->left->content.c_str());
            }
        }
        if (check_array_init)
        {
            if (isNewSemanticError(node->left->lineno))
            {
                fprintf(stderr, "Error [Semantic] at Line %d: Can't initialize an array with NOT-NUMBER %s.\n", node->left->lineno, node->left->content.c_str());
            }
        }
        if (check_const_init)
        {
            if (isNewSemanticError(node->left->lineno))
            {
                fprintf(stderr, "Error [Semantic] at Line %d: Can't initialize const with NOT-NUMBER %s.\n", node->left->lineno, node->left->content.c_str());
            }
        }
    }
    else if (checkProduction(node, 4, "IDENT", "[", "Exp", "]"))
    {
        // Infer: ARRAY
        myData *DATA = analyseBType(node->left);
        if (!checkNotDef(node->left->content, node->left->lineno, "ARRAY"))
        {
            return;
        }
        if (check_array_index)
        {
            if (isNewSemanticError(node->left->lineno))
            {
                fprintf(stderr, "Error [Semantic] at Line %d: Can't define an array's size with NOT-NUMBER %s.\n", node->left->lineno, node->left->content.c_str());
            }
        }
        if (check_array_init)
        {
            if (isNewSemanticError(node->left->lineno))
            {
                fprintf(stderr, "Error [Semantic] at Line %d: Can't initialize an array with NOT-NUMBER %s.\n", node->left->lineno, node->left->content.c_str());
            }
        }
        if (check_var_init)
        {
            if (isNewSemanticError(node->left->lineno))
            {
                fprintf(stderr, "Error [Semantic] at Line %d: Can't initialize var with ARRAY %s.\n", node->left->lineno, node->left->content.c_str());
            }
        }
        cal_array_type = true;
        analyseExp(node->left->right->right, symb);
        cal_array_type = false;
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
        if (cal_array_type)
        {
            if (cal_call_val)
            {
                myData *param_type = new myData;
                param_type->data_type = BASIC;
                param_type->is_r_value = false;
                param_type->basic = INT;
                param_type->value = str2int(node->left->content);
                myParam *new_param = new myParam;
                new_param->type = param_type;
                new_param->next = nullptr;
                new_param->para_name = cur_domain_name + ":" + node->left->content;
                func_call.push_back(new_param);
            }
        }
        else
        {
            if (cal_exp_val)
            {
                // LVal is a number
                if (check_assign)
                {
                    if (isNewSemanticError(node->left->lineno))
                    {
                        fprintf(stderr, "Error [Semantic] at Line %d: NUMBER %s can't be used as left value.\n", node->left->lineno, node->left->content.c_str());
                    }
                }
                if (check_compare)
                {
                    if (!set_init)
                    {
                        cur_op = BASIC;
                        set_init = true;
                    }
                    else
                    {
                        if (cur_op != BASIC)
                        {
                            if (isNewSemanticError(node->left->lineno))
                            {
                                fprintf(stderr, "Error [Semantic] at Line %d: Can't compare between two different types.\n", node->left->lineno);
                            }
                        }
                    }
                }
            }
            if (cal_call_val)
            {
                myData *param_type = new myData;
                param_type->data_type = BASIC;
                param_type->is_r_value = false;
                param_type->basic = INT;
                param_type->value = str2int(node->left->content);
                myParam *new_param = new myParam;
                new_param->type = param_type;
                new_param->next = nullptr;
                new_param->para_name = cur_domain_name + ":" + node->left->content;
                func_call.push_back(new_param);
            }
            if (cal_ret_val)
            {
                myData *tmp = new myData;
                tmp->data_type = BASIC;
                tmp->basic = INT;
                tmp->is_r_value = true;
                tmp->value = str2int(node->left->content);
                func_ret = tmp;
            }
        }

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
                    fprintf(stderr, "Error [Semantic] at Line %d: Array %s has a size of %d.\n", node->left, symb->name.c_str(), array_size);
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
    else if (checkProduction(node, 4, "IDENT", "(", "FuncRParams", ")"))
    {
        if (!checkNotDef(node->left->content, node->left->lineno, "FUNC"))
        {
            return;
        }

        cal_call_val = true;
        analyseFuncRParams(node->left->right->right, symb);
        // printFuncCall();
        checkFuncCall(node->left->content, node->left->lineno);
        func_call.clear();
        cal_call_val = false;
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
    else if (checkProduction(node, 1, "none"))
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
        cal_exp_val = true;
        analyseAddExp(node->left, symb);
        analyseMulExp(node->left->right->right, symb);
        cal_exp_val = false;
    }
    else if (checkProduction(node, 3, "AddExp", "-", "MulExp"))
    {
        cal_exp_val = true;
        analyseAddExp(node->left, symb);
        analyseMulExp(node->left->right->right, symb);
        cal_exp_val = false;
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
        cal_exp_val = true;
        analyseMulExp(node->left, symb);
        analyseUnaryExp(node->left->right->right, symb);
        cal_exp_val = false;
    }
    else if (checkProduction(node, 3, "MulExp", "/", "UnaryExp"))
    {
        cal_exp_val = true;
        analyseMulExp(node->left, symb);
        analyseUnaryExp(node->left->right->right, symb);
        cal_exp_val = false;
    }
    else if (checkProduction(node, 3, "MulExp", "%", "UnaryExp"))
    {
        cal_exp_val = true;
        analyseMulExp(node->left, symb);
        analyseUnaryExp(node->left->right->right, symb);
        cal_exp_val = false;
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
        cal_exp_val = true;
        analyseRelExp(node->left, symb);
        analyseAddExp(node->left->right->right, symb);
        cal_exp_val = false;
    }
    else if (checkProduction(node, 3, "RelExp", ">", "AddExp"))
    {
        cal_exp_val = true;
        analyseRelExp(node->left, symb);
        analyseAddExp(node->left->right->right, symb);
        cal_exp_val = false;
    }
    else if (checkProduction(node, 3, "RelExp", "LE_OP", "AddExp"))
    {
        cal_exp_val = true;
        analyseRelExp(node->left, symb);
        analyseAddExp(node->left->right->right, symb);
        cal_exp_val = false;
    }
    else if (checkProduction(node, 3, "RelExp", "GE_OP", "AddExp"))
    {
        cal_exp_val = true;
        analyseRelExp(node->left, symb);
        analyseAddExp(node->left->right->right, symb);
        cal_exp_val = false;
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
        check_compare = true;
        cal_exp_val = true;
        analyseEqExp(node->left, symb);
        analyseRelExp(node->left->right->right, symb);
        check_compare = false;
        cal_exp_val = false;
    }
    else if (checkProduction(node, 3, "EqExp", "NE_OP", "RelExp"))
    {
        check_compare = true;
        cal_exp_val = true;
        analyseEqExp(node->left, symb);
        analyseRelExp(node->left->right->right, symb);
        check_compare = false;
        cal_exp_val = false;
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
    func_call.clear();

    semantic_error_num = 0;
    last_semantic_error_lineno = 0;
    has_return = false;
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
                    printf("none\n");
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

void printDomain()
{
    printf("\n\ndomain:");
    for (unsigned int i = 0; i < domain.size(); i++)
    {
        printf(" %s", domain.at(i)->name.c_str());
    }
    printf("\n\n");
}

void printFuncCall()
{
    printf("\n\nFunc Call:");
    for (unsigned int i = 0; i < func_call.size(); i++)
    {
        printf(" %s", func_call.at(i)->para_name.c_str());
    }
    printf("\n\n");
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

void addNewParamToParamList(myParam *new_param, myParam *param_list)
{
    myParam *rear;

    rear = param_list;
    while (rear->next != nullptr)
    {
        rear = rear->next;
    }
    rear->next = new_param;
}
