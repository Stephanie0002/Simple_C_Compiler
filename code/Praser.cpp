#include "Praser.h"

using namespace std;

Praser::Praser(grammarTree *root)
{
    this->root = root;
    block whole_block;
    block_stack.push_back(whole_block);

    //  事先内置函数print和read
    funcNode write_node;
    write_node.name = "print";
    write_node.return_type = "void";
    varNode pnode;
    pnode.type = "int";
    write_node.para_list.push_back(pnode);

    func_pool.insert({"print", write_node});

    funcNode read_node;
    read_node.name = "read";
    read_node.return_type = "int";
    func_pool.insert({"read", read_node});

    praseTree(root); //开始分析语法树
}

Praser::~Praser()
{
    // printMap();
    // printInnerCode();
}

Praser::praseTree(struct grammarTree *node)
{
    cout << "at " << node->name << endl;
    if (node == NULL || node->lineno == -1)
    {
        return;
    }
    if (node->name == "declaration")
    {
        node = praseDeclaration(node);
    }
    else if (node->name == "function_definition")
    {
        node = praseFunctionDefinition(node);
    }
    else if (node->name == "statement")
    {
        node = praseStatement(node);
    }

    //继续向下分析
    if (node != NULL)
    {
        praseTree(node->left);
        praseTree(node->right);
    }
}

varNode Praser::praseAndExpression(struct grammarTree *and_exp)
{
    if (and_exp->left->name == "")
    {
    }
}

void Praser::print_error(int lineno, string error)
{

    cout << "Error at line " << lineno << ": ";
    cout << error << endl;
    exit(1);
}
