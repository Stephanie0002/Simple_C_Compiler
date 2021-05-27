#include "grammarTree.h"
#include "utils.h"

grammarTree *createTree(string name, int num, ...)
{
    if (num == -1)
    {
        va_list valist;
        va_start(valist, 0);
        int lineno = va_arg(valist, int);
        grammarTree *root = new grammarTree();
        if (!root)
        {
            printf("Out of space \n");
            exit(0);
        }
        grammarTree *temp = new grammarTree();
        if (!temp)
        {
            printf("Out of space \n");
            exit(0);
        }
        temp->left = NULL;
        temp->right = NULL;
        temp->content = "none";
        temp->name = "none";
        temp->lineno = lineno;

        root->left = temp;
        root->right = NULL;
        root->content = "none";
        root->name = name;
        root->lineno = lineno;

        return root;
    }

    grammarTree *root = new grammarTree();
    if (!root)
    {
        printf("Out of space \n");
        exit(0);
    }
    root->left = NULL;
    root->right = NULL;
    root->content = "";
    root->name = name;

    va_list valist;
    va_start(valist, num);

    grammarTree *temp = NULL;
    if (num > 0)
    {
        temp = va_arg(valist, grammarTree *);
        root->left = temp;
        root->lineno = temp->lineno;
        if (num == 1)
        {
            if (temp->content.size() > 0)
            {
                root->content = temp->content;
            }
            else
                root->content = "";
        }
        else
        {
            for (int i = 1; i < num; i++)
            {
                temp->right = va_arg(valist, grammarTree *);
                temp = temp->right;
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
            //printf("%d",value);
        }
        else
        {
            root->content = yytext;
        }
    }
    return root;
}

void floorPrint(grammarTree *root, string filename, bool verbose)
{
    cout << endl;
    if (root == NULL)
        return;
    filename = "viewTree/" + filename + "_floor_tree.txt";
    ofstream outfile(filename);
    queue<grammarTree *> q;
    q.push(root);
    int id = 1;
    string tmp;
    while (!q.empty())
    {
        int currentSize = q.size();
        vector<vector<string>> tempVec;
        for (int j = 0; j < currentSize; j++)
        {
            grammarTree *p = q.front();
            q.pop();

            tmp = int2str(id);
            vector<string> a = {tmp, p->name};
            id = str2int(tmp);
            p->id = id;
            id++;

            tempVec.push_back(a);

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
        //  Floor print
        for (int i = 0; i < tempVec.size(); i++)
        {
            outfile << tempVec[i][0] << " " << tempVec[i][1] << " ";
            if (verbose)
                cout << tempVec[i][0] << " " << tempVec[i][1] << " ";
        }
        outfile << endl;
        if (verbose)
            cout << endl;
    }
}

void nodePrint(grammarTree *root, string filename, bool verbose)
{
    cout << endl;
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
                        cout << p->id << " " << p->name << " " << tmp->id << " " << tmp->name << ":" << tmp->content << endl;
                    }
                    else
                    {
                        cout << p->id << " " << p->name << " " << tmp->id << " " << tmp->name << endl;
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
                            cout << p->id << " " << p->name << " " << tmp->right->id << " " << tmp->right->name << ":" << tmp->right->content << endl;
                        }
                        else
                        {
                            cout << p->id << " " << p->name << " " << tmp->right->id << " " << tmp->right->name << endl;
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

void outputTree(grammarTree *root, int level)
{
    if (root != NULL)
    {
        string Name = root->name;
        if (root->lineno != -1)
        {
            for (int i = 0; i < level; ++i)
            {
                cout << ". ";
            }
            cout << root->name;

            if (root->name == "INT")
            {
                cout << ":" << root->content;
            }
            else if (root->name == "NUMBER")
            {
                cout << ":" << root->content << " ";
            }
            else if (root->name == "IDENT")
            {
                cout << ":" << root->content << " ";
            }
            else
            {
                cout << " <" << root->lineno << ">";
            }
            cout << endl;
        }
        outputTree(root->left, level + 1);
        outputTree(root->right, level);
    }
}

/* remove meaningless tokens;
   fold branches caused by precedence distinguishing;
 */
grammarTree *grammarTree::tailor()
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
        }
        else if (name == "PrimaryExp")
        {
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