%option yylineno

%{
#include "y.tab.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "grammarTree.h"

using namespace std;

void comment();
void count(void);

int yycolumn = 0;
%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]

%%
"/*"			{ comment(); }
"//"[^\n]*      {  }

"for" 			{printf("Undifined reserved word \'for\'!"); exit(0);}
"switch"		{printf("Undifined reserved word \'switch\'!"); exit(0);}
"case"			{printf("Undifined reserved word \'case\'!"); exit(0);}
"char"			{printf("Undifined reserved word \'char\'!"); exit(0);}
"double"		{printf("Undifined reserved word \'double\'!"); exit(0);}
"float"			{printf("Undifined reserved word \'float\'!"); exit(0);}

"const"			{ count(); yylval.tree =createTree("CONST", 0, yylineno); 	return(CONST); }
"int"			{ count(); yylval.tree =createTree("INT", 0, yylineno); 	return(INT); }
"void"			{ count(); yylval.tree =createTree("VOID", 0, yylineno); 	return(VOID); }
"if"			{ count(); yylval.tree =createTree("IF", 0, yylineno); 		return(IF); }
"else"			{ count(); yylval.tree =createTree("ELSE", 0, yylineno); 	return(ELSE); }
"while"			{ count(); yylval.tree =createTree("WHILE", 0, yylineno); 	return(WHILE); }
"break"			{ count(); yylval.tree =createTree("BREAK", 0, yylineno); 	return(BREAK); }
"continue"		{ count(); yylval.tree =createTree("CONTINUE", 0, yylineno);return(CONTINUE); }
"return"		{ count(); yylval.tree =createTree("RETURN", 0, yylineno); 	return(RETURN); }

{L}({L}|{D})*   { count(); yylval.tree = createTree("IDENT", 0, yylineno); 	return(IDENT); }

[1-9]{D}*   { count(); yylval.tree = createTree("NUMBER", 0, yylineno); return(NUMBER); }
0[0-7]*     { count(); yylval.tree = createTree("NUMBER", 0, yylineno); return(NUMBER); }
0[xX]{H}+   { count(); yylval.tree = createTree("NUMBER", 0, yylineno); return(NUMBER); }

"&&"	{ count(); yylval.tree =createTree("AND_OP", 0, yylineno);	return(AND_OP); }
"||"	{ count(); yylval.tree =createTree("OR_OP", 0, yylineno); 	return(OR_OP); }
"<="	{ count(); yylval.tree =createTree("LE_OP", 0, yylineno); 	return(LE_OP); }
">="	{ count(); yylval.tree =createTree("GE_OP", 0, yylineno); 	return(GE_OP); }
"=="	{ count(); yylval.tree =createTree("EQ_OP", 0, yylineno); 	return(EQ_OP); }
"!="	{ count(); yylval.tree =createTree("NE_OP", 0, yylineno); 	return(NE_OP); }
";"		{ count(); yylval.tree =createTree(";", 0, yylineno);		return(';'); }
","		{ count(); yylval.tree =createTree(",", 0, yylineno);		return(','); }
"="		{ count(); yylval.tree =createTree("=", 0, yylineno);		return('='); }
"["	 	{ count(); yylval.tree =createTree("[", 0, yylineno);	    return('['); }
"]"		{ count(); yylval.tree =createTree("]", 0, yylineno);	    return(']'); }
"!"		{ count(); yylval.tree =createTree("!", 0, yylineno);	    return('!'); }
"+"		{ count(); yylval.tree =createTree("+", 0, yylineno);	    return('+'); }
"-"		{ count(); yylval.tree =createTree("-", 0, yylineno);		return('-'); }
"*"		{ count(); yylval.tree =createTree("*", 0, yylineno);		return('*'); }
"/"		{ count(); yylval.tree =createTree("/", 0, yylineno);		return('/'); }
"%"		{ count(); yylval.tree =createTree("%", 0, yylineno);		return('%'); } 
"<"		{ count(); yylval.tree =createTree("<", 0, yylineno);		return('<'); }
">"		{ count(); yylval.tree =createTree(">", 0, yylineno);		return('>'); }
"{"		{ count(); yylval.tree =createTree("{", 0, yylineno);		return('{'); }
"}"		{ count(); yylval.tree =createTree("}", 0, yylineno);		return('}'); }
"("		{ count(); yylval.tree =createTree("(", 0, yylineno);		return('('); }
")"		{ count(); yylval.tree =createTree(")", 0, yylineno);		return(')'); }

[\t\v\n\f ]     { count(); }
[\r]			{}
. 				{ printf("<src>:%d:%d: error: [Lexical] unmatched character \'%s\'\n", yylineno, yycolumn, yytext); exit(0);}

%%

int yywrap(void)
{
	return 1;
}

void comment()
{
	yycolumn = 0;
    char c, prev = 0;
  
	while (cin >> c)
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	printf("unterminated comment");
}

void count(void)
{
	for (int i = 0; yytext[i] != '\0'; i++) {
		if (yytext[i] == '\n') {
			yycolumn = 0;
        }
		else if (yytext[i] == '\t') {
			yycolumn += 4 - (yycolumn % 4);
        }
		else {
			yycolumn++;
        }
    }
    ECHO;
}