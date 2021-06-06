#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "grammarTree.h"
#include "Parser.h"

using namespace std;

extern int yyparse(void);
extern void yyrestart(FILE *input_file);

extern int error_num;
extern int last_error_lineno;
extern int yylineno;
extern int yycolumn;
extern struct grammarTree *root;

int success_file_num = 0;
int input_file_num = 0;
int cmd_file_num = 0;

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("Error [Others]: No input files.");
        return 1;
    }

    bool verbose = false;
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
        cmd_file_num++;

        FILE *yyin = fopen(argv[i], "r");
        if (!yyin)
        {
            fprintf(stderr, "Error [Others]: \"%s\": No such file or directory.\n", filename.c_str());
            continue;
        }

        // Omit blank file
        if (feof(yyin))
        {
            fclose(yyin);
            printf("\n---Omit blank file %s:---\n", filename.c_str());
            continue;
        }
        char ch;
        bool is_blank_file = true;
        while ((ch = fgetc(yyin)) != EOF)
        {
            if (ch != ' ' || ch != '\t' || ch != '\n' || ch != '\r' || ch != '\v' || ch != '\f')
            {
                is_blank_file = false;
                break;
            }
        }
        fclose(yyin);
        if (is_blank_file)
        {
            printf("\n---Omit blank file %s:---\n", filename.c_str());
            continue;
        }
        else
        {
            FILE *yyin = fopen(argv[i], "r");
            input_file_num++;
        }

        printf("\n---Compile file %s:---\n", filename.c_str());

        yyrestart(yyin);
        yyparse();

        if (error_num == 0)
        {
            nodePrint(root, filename, verbose);
            int semantic_error_num = semanticAnalysis(root, verbose);

            error_num += semantic_error_num;

            delete root;
            destroySymbolTable();

            success_file_num++;
        }

        if (error_num > 1)
        {
            fprintf(stderr, "%d errors occured when compiling.\n", error_num);
        }
        else if (error_num == 1)
        {
            fprintf(stderr, "1 error occured when compiling.\n");
        }
        error_num = 0;
        last_error_lineno = 0;
        yylineno = 1;
        yycolumn = 1;
        fclose(yyin);
    }
    printf("\n---%d files has been typed to compile!---\n", cmd_file_num);
    printf("\n---%d files has been successfully entered!---\n", input_file_num);
    printf("\n---%d files has been successfully compiled and run!---\n", success_file_num);
    return 0;
}