%option yylineno

%{
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

void comment(void);
void count(void);

int yycolumn = 1;
#define YY_USER_ACTION count();
%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]

%% 
[1-9]{D}* {
    yylval.type_int = atoi(yytext);
    return NUMBER;
}
0[xX]{H}+ {
    char *dc;
    yylval.type_int = strtol(yytext, &dc, 16);
    return NUMBER;
}

"const"			{ return(CONST); }
"int"			{ return(INT); }
"void"			{ return(VOID); }
"if"			{ return(IF); }
"else"			{ return(ELSE); }
"while"			{ return(WHILE); }
"break"			{ return(BREAK); }
"continue"		{ return(CONTINUE); }
"return"		{ return(RETURN); }
{L}({L}|{D})*   { 
    strncpy(yylval.type_str, yytext, 32);
    return(IDENT); 
}

[+\-*/%<>!=;,\[\](){}] {
    return yytext[0];
}
"<="			{ return(LE_OP); }
">="			{ return(GE_OP); }
"=="			{ return(EQ_OP); }
"!="			{ return(NE_OP); }
"&&"			{ return(AND_OP); }
"||"			{ return(OR_OP); }

"/*"			{ comment(); }
"//"[^\n]*      { /* consume //-comment */ }

[ \t\v\n\f]     { /* consume */ }
. { 
    yylval.type_str[0] = yytext[0];
    yylval.type_str[1] = '\0';
    printf("[Lexical] Error at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext); 
    return(ERROR); 
}

%%

int yywrap(void)
{
	return 1;
}

void comment(void)
{
	char c, prev = 0;
  
	while ((c = input()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	perror("unterminated comment");
}

void count(void)
{
    yylloc.first_line = yylloc.last_line = yylineno; 
    yylloc.first_column = yycolumn; 

	for (int i = 0; yytext[i] != '\0'; i++) {
		if (yytext[i] == '\n') {
			yycolumn = 1;
        }
		else if (yytext[i] == '\t') {
			yycolumn += 8 - (yycolumn % 8);
        }
		else {
			yycolumn++;
        }
    }

    yylloc.last_column = yycolumn - 1;
}