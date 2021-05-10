#include "grammarTree.h"
#include "utils.h"

grammarTree *createTree(string name, int num, ...)
{
    va_list valist;
    grammarTree *root = new grammarTree();
    if (!root)
    {
        printf("Out of space \n");
        exit(0);
    }
    root->left = NULL;
    root->right = NULL;
    root->content = "";
    grammarTree *temp = NULL;
    root->name = name;
    va_start(valist, num);
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

void floorPrint(grammarTree *root, bool verbose)
{
    cout << endl;
    if (root == NULL)
        return;

    ofstream outfile("viewTree/test_tree.txt");
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
            id++;

            cout << p->name << " " << p->content << endl;

            tempVec.push_back(a);

            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
        }

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

void Clean(grammarTree *node)
{
    if (node == NULL)
        return;
    Clean(node->left);
    delete node;
    Clean(node->right);
}
