/* declarations */
%{
#include <stdio.h>
%}

%union {
    int type_int;
    char type_str[32];
}

%token <type_int> NUMBER
%token <type_str> IDENT ERROR
%token CONST INT VOID IF ELSE WHILE BREAK CONTINUE RETURN LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP

%%
/* rules */ 
empty : ;

%% 
/* programs */
int main() {
    return yyparse();
}

/* allows for printing of an error message */
int yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
    return 0;
}