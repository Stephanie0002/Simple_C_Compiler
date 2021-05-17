#ifndef _PRASER_H
#define _PRASER_H
#include "grammarTree.h"
#include "utils.h"
#include <vector>
#include <set>

class Praser
{
public:
    Praser(grammarTree *root);
    ~Praser();

private:
    map<string, funcNode> func_pool; //函数池
    vector<block> block_stack;       //维护的栈
    // InnerCode innerCode;            //中间代码生成工具

    struct grammarTree *root;

    void praseTree(struct grammarTree *node);

    varNode praseAndExpression(struct grammarTree *and_exp);

    void print_error(int lineno, string error);
};

#endif
