%option yylineno

%{
#include "y.tab.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "grammarTree.h"

using namespace std;

void comment(void);
void count(void);

int yycolumn = 0;
// typedef struct YYLTYPE YYLTYPE;
// struct YYLTYPE
// {
//   int first_line;
//   int first_column;
//   int last_line;
//   int last_column;
// };
// YYLTYPE yylloc;

#define YY_USER_ACTION count();
%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]

%% 
[1-9]{D}* {
    yylval.tree = createTree("NUMBER", 0, yylineno);
    return(NUMBER);
}
0[0-7]* {
    yylval.tree = createTree("NUMBER", 0, yylineno);
    return(NUMBER);
}
0[xX]{H}+ {
    yylval.tree = createTree("NUMBER", 0, yylineno);
    return(NUMBER);
}

"const"			{ yylval.tree =createTree("CONST", 0, yylineno); return(CONST); }
"int"			{ yylval.tree =createTree("INT", 0, yylineno); return(INT); }
"void"			{ yylval.tree =createTree("VOID", 0, yylineno); return(VOID); }
"if"			{ yylval.tree =createTree("IF", 0, yylineno); return(IF); }
"else"			{ yylval.tree =createTree("ELSE", 0, yylineno); return(ELSE); }
"while"			{ yylval.tree =createTree("WHILE", 0, yylineno); return(WHILE); }
"break"			{ yylval.tree =createTree("BREAK", 0, yylineno); return(BREAK); }
"continue"		{ yylval.tree =createTree("CONTINUE", 0, yylineno); return(CONTINUE); }
"return"		{ yylval.tree =createTree("RETURN", 0, yylineno); return(RETURN); }
{L}({L}|{D})*   { 
    yylval.tree = createTree("IDENT", 0, yylineno);
    return(IDENT); 
}

[+\-*/%<>!=;,\[\](){}] {
    return(yytext[0]);
}
"<="			{ yylval.tree =createTree("LE_OP", 0, yylineno); return(LE_OP); }
">="			{ yylval.tree =createTree("GE_OP", 0, yylineno); return(GE_OP); }
"=="			{ yylval.tree =createTree("EQ_OP", 0, yylineno); return(EQ_OP); }
"!="			{ yylval.tree =createTree("NE_OP", 0, yylineno); return(NE_OP); }
"&&"			{ yylval.tree =createTree("AND_OP", 0, yylineno); return(AND_OP); }
"||"			{ yylval.tree =createTree("OR_OP", 0, yylineno); return(OR_OP); }

"/*"			{ comment(); }
"//"[^\n]*      { /* consume //-comment */ }

[\t\v\n\f]     { /* consume */ }
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
	yycolumn = 0;
    char c, prev = 0;
  
	while (cin >> c)      /* (EOF maps to 0) */
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
			yycolumn = 0;
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