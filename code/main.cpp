#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "syntaxTree.h"
#include "Parser.h"

using namespace std;

extern int yyparse(void);
extern void yyrestart(FILE *input_file);

extern int error_num;
extern int last_error_lineno;
extern struct syntaxTree *root;

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("Error [Others]: No input files.");
        return 1;
    }

    bool verbose = false; // default is false
    string tmp = argv[1];
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    if (tmp == "true")
    {
        verbose = true;
    }

    int start = 1;
    if (tmp == "true" || tmp == "false")
    {
        if (argc == 2)
        {
            fprintf(stderr, "Error [Others]: No input files.");
            return 1;
        }
        start = 2;
    }
    for (int i = start; i < argc; i++)
    {
        string filename = argv[i];

        FILE *file = fopen(argv[i], "r");
        if (!file)
        {
            perror(argv[i]);
            return 1;
        }

        printf("\n---Compile file %s:---\n", filename.c_str());

        yyrestart(file);
        yyparse();

        if (error_num == 0)
        {
            syntaxTree *syntax = root;
            syntaxTree *semantic = root;
            nodePrint(syntax, filename, verbose);
            semanticAnalysis(semantic);

            delete root;
            destroySymbolTable();
        }
        else
        {
            if (error_num != 1)
                fprintf(stderr, "%d errors occured when compiling.\n", error_num);
            else
                fprintf(stderr, "1 error occured when compiling.\n");
            error_num = 0;
            last_error_lineno = 0;
        }

        yylineno = 1;
        fclose(file);
    }
    return 0;
}