#include "grammarTree.h"

extern char *yytext;

grammarTree *createGrammarTree(string name, int num, ...)
{
    grammarTree *root = new grammarTree();
    if (!root)
    {
        fprintf(stderr, "Error [Syntax] Syntax tree out of space when creating it.\n");
        exit(0);
    }
    root->left = nullptr;
    root->right = nullptr;
    root->content = "";
    root->name = name;
    root->id = -1;

    va_list valist;
    va_start(valist, num);
    grammarTree *tmp = nullptr;
    if (num > 0)
    {
        tmp = va_arg(valist, grammarTree *);
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
                tmp->right = va_arg(valist, grammarTree *);
                tmp = tmp->right;
            }
        }
    }
    else
    {
        int lineno = va_arg(valist, int);
        root->lineno = lineno;
        root->id = -1;

        if (root->name == "NUMBER")
        {
            int value;
            if (strlen(yytext) > 1 && yytext[0] == '0' && (yytext[1] != 'x' || yytext[1] != 'X'))
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
        else
        {
            root->content = yytext;
        }
    }
    return root;
}

grammarTree *addNullNode(string name, int lineno, int col)
{
	grammarTree *root = new grammarTree;
	if (!root)
	{
		fprintf(stderr, "Error [Syntax] Syntax tree out of space when adding ε node.\n");
		exit(0);
	}

	grammarTree *tmp = new grammarTree;
	if (!tmp)
	{
		fprintf(stderr, "Error [Syntax] Syntax tree out of space when adding ε node.\n");
		exit(0);
	}

	tmp->left = nullptr;
	tmp->right = nullptr;
	tmp->content = "none";
	tmp->name = "none";
	tmp->lineno = lineno;
	tmp->id = -1;

	root->left = tmp;
	root->right = nullptr;
	root->name = name;
	root->content = "";
	root->lineno = lineno;
	tmp->id = -1;

	return root;
}

void floorTraverse(grammarTree *root)
{
    if (root == nullptr)
    {
        return;
    }
    queue<grammarTree *> q;
    q.push(root);
    int id = 1;
    while (!q.empty())
    {
        int currentSize = q.size();
        for (int j = 0; j < currentSize; j++)
        {
            grammarTree *p = q.front();
            q.pop();

            p->id = id;
            id++;

            grammarTree *tmp = p->left;
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

void nodePrint(grammarTree *root, string filename, bool verbose)
{
    if (root->id == -1)
    {
        grammarTree *tmp = root;
        floorTraverse(tmp);
    }
    // verbose = true;
    if (verbose)
    {
        printf("\n");
    }
    if (root == nullptr)
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
    queue<grammarTree *> q;
    q.push(root);
    while (!q.empty())
    {
        int currentSize = q.size();
        for (int j = 0; j < currentSize; j++)
        {
            grammarTree *p = q.front();
            q.pop();

            grammarTree *tmp = p->left;
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

// tailor_inner() + folding "CompUnit"
void grammarTree::tailor()
{
	tailor_inner();
	while (left->name == "CompUnit")
	{
		left = left->fold_lchain();
	}
}

/* remove meaningless tokens;
   fold branches caused by precedence distinguishing;
 */
grammarTree *grammarTree::tailor_inner()
{
	// postorder
	if (left)
	{
		left = left->tailor_inner();
	}
	if (right)
	{
		right = right->tailor_inner();
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
		}
		else if (name == "PrimaryExp")
		{
			if (nb_child() == 1)
			{
				return fold_lchain();
			}
		}
		else if (name == "Exp" || name == "ConstExp")
		{
			if (nb_child() == 1)
			{
				return fold_lchain();
			}
		}
		else if (name == "Stmt")
		{
			if (nb_child() == 0)
			{
				return fold_rchain();
			}
		}
		else if (name == "BlockItem")
		{
			return fold_lchain();
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
		break;
	}
	return this;
}