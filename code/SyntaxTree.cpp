@ @-1, 41 + 1, 9 @ @
#include "grammarTree.h"
#include "syntaxTree.h"
#include "utils.h"

    grammarTree *
    createTree(string name, int num, ...) syntaxTree *createSyntaxTree(const char *name, int num, ...)
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
    syntaxTree *root = new syntaxTree();
    if (!root)
    {
        printf("Out of space \n");
        @-49, 17 + 17, 17 @ @grammarTree *createTree(string name, int num, ...) va_list valist;
        va_start(valist, num);

        grammarTree *temp = NULL;
        syntaxTree *tmp = NULL;
        if (num > 0)
        {
            temp = va_arg(valist, grammarTree *);
            root->left = temp;
            root->lineno = temp->lineno;
            tmp = va_arg(valist, syntaxTree *);
            root->left = tmp;
            root->lineno = tmp->lineno;
            if (num == 1)
            {
                if (temp->content.size() > 0)
                    if (strlen(tmp->content) > 0)
                    {
                        root->content = temp->content;
                        root->content = tmp->content;
                    }
                    else
                        root->content = "";
                @-68, 8 + 36, 8 @ @grammarTree *createTree(string name, int num, ...)
                {
                    for (int i = 1; i < num; i++)
                    {
                        temp->right = va_arg(valist, grammarTree *);
                        temp = temp->right;
                        tmp->right = va_arg(valist, syntaxTree *);
                        tmp = tmp->right;
                    }
                }
            }
            @-91, 7 + 59, 6 @ @grammarTree *createTree(string name, int num, ...) else value = atoi(yytext); //10进制整数
            root->content = int2str(value);
            //printf("%d",value);
        }
        else
        {
            @-101, 35 + 68, 67 @ @grammarTree *createTree(string name, int num, ...) return root;
        }

        void floorPrint(grammarTree * root, string filename, bool verbose)
            syntaxTree *
            addNullNode(const char *name, int lineno, int col)
        {
            syntaxTree *root = new syntaxTree();
            if (!root)
            {
                printf("Error [Others] at line %d, col %d: Construct syntax tree out of space.\n", lineno, col);
                exit(0);
            }
            syntaxTree *temp = new syntaxTree();
            if (!temp)
            {
                printf("Error [Others] at line %d, col %d: Construct syntax tree out of space.\n", lineno, col);
                exit(0);
            }

            temp->name = "Null";
            temp->content = "Null";
            temp->lineno = lineno;
            temp->left = NULL;
            temp->right = NULL;

            root->name = name;
            root->content = name;
            root->lineno = lineno;
            root->left = temp;
            root->right = NULL;

            return root;
        }

        void destroySyntaxTree(syntaxTree * node)
        {
            if (node == NULL)
            {
                return;
            }
            destroySyntaxTree(node->left);
            delete node;
            destroySyntaxTree(node->right);
        }

        void floorTraverse(syntaxTree * root)
        {
            cout << endl;
            if (root == NULL)
                return;
            filename = "viewTree/" + filename + "_floor_tree.txt";
            ofstream outfile(filename);
            queue<grammarTree *> q;
            queue<syntaxTree *> q;
            q.push(root);
            int id = 1;
            string tmp;
            const char *tmp;
            while (!q.empty())
            {
                int currentSize = q.size();
                vector<vector<string>> tempVec;
                for (int j = 0; j < currentSize; j++)
                {
                    grammarTree *p = q.front();
                    syntaxTree *p = q.front();
                    q.pop();

                    tmp = int2str(id);
                    vector<string> a = {tmp, p->name};
                    id = str2int(tmp);
                    p->id = id;
                    id++;

                    tempVec.push_back(a);

                    grammarTree *tmp = p->left;
                    syntaxTree *tmp = p->left;
                    if (tmp)
                    {
                        q.push(tmp);
                        @-140, 46 + 139, 43 @ @ void floorPrint(grammarTree * root, string filename, bool verbose)
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

    void nodePrint(grammarTree * root, string filename, bool verbose) void nodePrint(syntaxTree * root, string out_name, bool verbose)
    {
        cout << endl;
        if (root->id == -1)
        {
            syntaxTree *tmp = root;
            floorTraverse(tmp);
        }
        if (verbose)
        {
            cout << endl;
        }
        if (root == NULL)
            return;
        // remove dir/ preceding
        for (auto i = filename.size(); i != 0; i--)
            for (auto i = out_name.size(); i != 0; i--)
            {
                if (filename[i] == '\\' || filename[i] == '/')
                    if (out_name[i] == '\\' || out_name[i] == '/')
                    {
                        filename = filename.substr(i + 1);
                        out_name = out_name.substr(i + 1);
                        break;
                    }
            }
        filename = "viewTree/" + filename + "_node_tree.txt";
        ofstream outfile(filename);
        queue<grammarTree *> q;
        out_name = "viewTree/" + out_name + "_node_tree.txt";
        ofstream outfile(out_name);
        queue<syntaxTree *> q;
        q.push(root);
        while (!q.empty())
        {
            int currentSize = q.size();
            for (int j = 0; j < currentSize; j++)
            {
                grammarTree *p = q.front();
                syntaxTree *p = q.front();
                q.pop();

                grammarTree *tmp = p->left;
                syntaxTree *tmp = p->left;
                if (tmp)
                {
                    if (verbose)
                        @-232, 48 + 228, 3 @ @ void nodePrint(grammarTree * root, string filename, bool verbose)
                }
            }
        }

        void outputTree(grammarTree * root, int level)
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

        void Clean(grammarTree * node)
        {
            if (node)
            {
                Clean(node->left);
                Clean(node->right);
                delete node;
            }
        }