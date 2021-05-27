#include "syntaxTree.h"

syntaxTree *createSyntaxTree(string name, int num, ...)
{
    syntaxTree *root = new syntaxTree();
    if (!root)
    {
        fprintf(stderr, "Error [Syntax] Syntax tree out of space when creating it.\n");
        exit(0);
    }
    root->left = NULL;
    root->right = NULL;
    root->content = "";
    root->name = name;

    va_list valist;
    va_start(valist, num);

    syntaxTree *tmp = NULL;
    if (num > 0)
    {
        tmp = va_arg(valist, syntaxTree *);
        root->left = tmp;
        root->lineno = tmp->lineno;
        if (num == 1)
        {
            if (tmp->content.size() > 0)
            {
                root->content = tmp->content;
            }
            else
                root->content = "";
        }
        else
        {
            for (int i = 1; i < num; i++)
            {
                tmp->right = va_arg(valist, syntaxTree *);
                tmp = tmp->right;
            }
        }
    }
    else
    {
        int lineno = va_arg(valist, int);
        root->lineno = lineno;

        if (root->name == "NUMBER")
        {
            int value;
            if (strlen(yytext) > 1 && yytext[0] == '0' && yytext[1] != 'x')
            {
                sscanf(yytext, "%o", &value); //8进制整数
            }
            else if (strlen(yytext) > 1 && yytext[1] == 'x')
            {
                sscanf(yytext, "%x", &value); //16进制整数
            }
            else
                value = atoi(yytext); //10进制整数
            root->content = int2str(value);
        }
        else if (root->name == "TRUE")
        {
            root->content = int2str(1);
        }
        else if (root->name == "FALSE")
        {
            root->content = int2str(0);
        }
        else
        {
            root->content = yytext;
        }
    }
    return root;
}

syntaxTree *addNullNode(string name, int lineno, int col)
{
    syntaxTree *root = new syntaxTree;
    if (!root)
    {
        fprintf(stderr, "Error [Syntax] Syntax tree out of space when adding ε node.\n");
        exit(0);
    }

    syntaxTree *tmp = new syntaxTree;
    if (!tmp)
    {
        fprintf(stderr, "Error [Syntax] Syntax tree out of space when adding ε node.\n");
        exit(0);
    }

    tmp->left = NULL;
    tmp->right = NULL;
    tmp->content = "Null";
    tmp->name = "Null";
    tmp->lineno = lineno;

    root->left = tmp;
    root->right = NULL;
    root->name = name;
    root->content = "";
    root->lineno = lineno;

    return root;
}

void floorTraverse(syntaxTree *root)
{
    if (root == NULL)
    {
        return;
    }
    queue<syntaxTree *> q;
    q.push(root);
    int id = 1;
    while (!q.empty())
    {
        int currentSize = q.size();
        for (int j = 0; j < currentSize; j++)
        {
            syntaxTree *p = q.front();
            q.pop();

            p->id = id;
            id++;

            syntaxTree *tmp = p->left;
            if (tmp)
            {
                q.push(tmp);
                while (tmp->right)
                {
                    q.push(tmp->right);
                    tmp = tmp->right;
                }
            }
        }
    }
}

void nodePrint(syntaxTree *root, string filename, bool verbose)
{
    if (root->id == -1)
    {
        syntaxTree *tmp = root;
        floorTraverse(tmp);
    }
    verbose = true;
    printf("\n");
    if (root == NULL)
        return;
    // remove dir/ preceding
    for (auto i = filename.size(); i != 0; i--)
    {
        if (filename[i] == '\\' || filename[i] == '/')
        {
            filename = filename.substr(i + 1);
            break;
        }
    }
    filename = "viewTree/" + filename + "_node_tree.txt";
    ofstream outfile(filename);
    queue<syntaxTree *> q;
    q.push(root);
    while (!q.empty())
    {
        int currentSize = q.size();
        for (int j = 0; j < currentSize; j++)
        {
            syntaxTree *p = q.front();
            q.pop();

            syntaxTree *tmp = p->left;
            if (tmp)
            {
                if (verbose)
                {
                    if (tmp->name == "INT" || tmp->name == "IDENT" || tmp->name == "NUMBER")
                    {
                        printf("%d %s %d %s:%s\n", p->id, p->name.c_str(), tmp->id, tmp->name.c_str(), tmp->content.c_str());
                    }
                    else
                    {
                        printf("%d %s %d %s\n", p->id, p->name.c_str(), tmp->id, tmp->name.c_str());
                    }
                }
                if (tmp->name == "INT" || tmp->name == "IDENT" || tmp->name == "NUMBER")
                {
                    outfile << p->id << " " << p->name << " " << tmp->id << " " << tmp->name << ":" << tmp->content << endl;
                }
                else
                {
                    outfile << p->id << " " << p->name << " " << tmp->id << " " << tmp->name << endl;
                }
                q.push(tmp);

                while (tmp->right)
                {
                    if (verbose)
                    {
                        if (tmp->right->name == "INT" || tmp->right->name == "IDENT" || tmp->right->name == "NUMBER")
                        {
                            printf("%d %s %d %s:%s\n", p->id, p->name.c_str(), tmp->right->id, tmp->right->name.c_str(), tmp->right->content.c_str());
                        }
                        else
                        {
                            printf("%d %s %d %s\n", p->id, p->name.c_str(), tmp->right->id, tmp->right->name.c_str());
                        }
                    }
                    if (tmp->right->name == "INT" || tmp->right->name == "IDENT" || tmp->right->name == "NUMBER")
                    {
                        outfile << p->id << " " << p->name << " " << tmp->right->id << " " << tmp->right->name << ":" << tmp->right->content << endl;
                    }
                    else
                    {
                        outfile << p->id << " " << p->name << " " << tmp->right->id << " " << tmp->right->name << endl;
                    }

                    q.push(tmp->right);
                    tmp = tmp->right;
                }
            }
        }
    }
}

void destroySyntaxTree(syntaxTree *node)
{
    delete node->left;
    delete node->right;
}

/* remove meaningless tokens;
   fold branches caused by precedence distinguishing;
 */
syntaxTree *syntaxTree::tailor()
{
    // postorder
    if (left)
    {
        left = left->tailor();
    }
    if (right)
    {
        right = right->tailor();
    }
    /* Case 1: Add -> Mul -> Unary -> Primary -> .
     * Case 2: list -> list -> none
     */
    switch (type())
    {
    case Garbage:
    {
        return fold_rchain();
    }
    break;
    case List:
        if (nb_child() == 0)
        {
            return fold_rchain();
        }
        else
        {
            return fold_lchain();
        }
        break;
    case BinExpr:
        if (nb_child() == 1)
        {
            return fold_lchain();
        }
        break;
    default:
        if (name == "UnaryExp")
        {
            if (nb_child() == 1)
            {
                return fold_lchain();
            }
            else if (nb_child() == 4)
            {
                auto c = left;
                c->right = c->right->fold_rchain(); // '('
                c = c->right;
                c->right = c->right->fold_rchain(); // ')'
            }
        }
        else if (name == "PrimaryExp")
        {
            if (nb_child() == 3)
            {
                // get Exp child
                left = left->fold_rchain();               // '('
                left->right = left->right->fold_rchain(); // ')'
            }
            if (nb_child() == 1)
            {
                return fold_lchain();
            }
        }
        else if (name == "Exp")
        {
            if (nb_child() == 1)
            {
                return fold_lchain();
            }
        }
        else if (name == "Block")
        {
            left = left->fold_rchain(); // '{'
            auto c = left;
            while (c->right)
            {
                if (c->right->name == "}")
                {
                    c->right = c->right->fold_rchain(); // '}'
                    break;
                }
                c = c->right;
            }
        }
        else if (name == "FuncDef")
        {
            auto c = left->right;
            c->right = c->right->fold_rchain(); // '('
            c = c->right;
            c->right = c->right->fold_rchain(); // ')'
        }
        break;
    }
    return this;
}