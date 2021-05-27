%option yylineno

%{
#include <cstdio>
#include <cstdlib>
#include "y.tab.h"
#include "syntaxTree.h"

using namespace std;

void comment();
void count(void);

int yycolumn = 1;
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
"void"			{printf("Undifined reserved word \'void\'!"); exit(0);}

"const"			{ count(); yylval.node = createSyntaxTree("CONST", 0, yylineno); 	return(CONST); }
"int"			{ count(); yylval.node = createSyntaxTree("INT", 0, yylineno); 	return(INT); }
"if"			{ count(); yylval.node = createSyntaxTree("IF", 0, yylineno); 		return(IF); }
"else"			{ count(); yylval.node = createSyntaxTree("ELSE", 0, yylineno); 	return(ELSE); }
"while"			{ count(); yylval.node = createSyntaxTree("WHILE", 0, yylineno); 	return(WHILE); }
"break"			{ count(); yylval.node = createSyntaxTree("BREAK", 0, yylineno); 	return(BREAK); }
"continue"		{ count(); yylval.node = createSyntaxTree("CONTINUE", 0, yylineno);return(CONTINUE); }
"return"		{ count(); yylval.node = createSyntaxTree("RETURN", 0, yylineno); 	return(RETURN); }

{L}({L}|{D})*   { count(); yylval.node = createSyntaxTree("IDENT", 0, yylineno); 	return(IDENT); }

[1-9]{D}*   { count(); yylval.node = createSyntaxTree("NUMBER", 0, yylineno); return(NUMBER); }
0[0-7]*     { count(); yylval.node = createSyntaxTree("NUMBER", 0, yylineno); return(NUMBER); }
0[xX]{H}+   { count(); yylval.node = createSyntaxTree("NUMBER", 0, yylineno); return(NUMBER); }

"&&"	{ count(); yylval.node =createSyntaxTree("AND_OP", 0, yylineno);	return(AND_OP); }
"||"	{ count(); yylval.node =createSyntaxTree("OR_OP", 0, yylineno); 	return(OR_OP); }
"<="	{ count(); yylval.node =createSyntaxTree("LE_OP", 0, yylineno); 	return(LE_OP); }
">="	{ count(); yylval.node =createSyntaxTree("GE_OP", 0, yylineno); 	return(GE_OP); }
"=="	{ count(); yylval.node =createSyntaxTree("EQ_OP", 0, yylineno); 	return(EQ_OP); }
"!="	{ count(); yylval.node =createSyntaxTree("NE_OP", 0, yylineno); 	return(NE_OP); }
";"		{ count(); yylval.node =createSyntaxTree(";", 0, yylineno);		return(';'); }
","		{ count(); yylval.node =createSyntaxTree(",", 0, yylineno);		return(','); }
"="		{ count(); yylval.node =createSyntaxTree("=", 0, yylineno);		return('='); }
"["	 	{ count(); yylval.node =createSyntaxTree("[", 0, yylineno);	    return('['); }
"]"		{ count(); yylval.node =createSyntaxTree("]", 0, yylineno);	    return(']'); }
"!"		{ count(); yylval.node =createSyntaxTree("!", 0, yylineno);	    return('!'); }
"+"		{ count(); yylval.node =createSyntaxTree("+", 0, yylineno);	    return('+'); }
"-"		{ count(); yylval.node =createSyntaxTree("-", 0, yylineno);		return('-'); }
"*"		{ count(); yylval.node =createSyntaxTree("*", 0, yylineno);		return('*'); }
"/"		{ count(); yylval.node =createSyntaxTree("/", 0, yylineno);		return('/'); }
"%"		{ count(); yylval.node =createSyntaxTree("%", 0, yylineno);		return('%'); } 
"<"		{ count(); yylval.node =createSyntaxTree("<", 0, yylineno);		return('<'); }
">"		{ count(); yylval.node =createSyntaxTree(">", 0, yylineno);		return('>'); }
"{"		{ count(); yylval.node =createSyntaxTree("{", 0, yylineno);		return('{'); }
"}"		{ count(); yylval.node =createSyntaxTree("}", 0, yylineno);		return('}'); }
"("		{ count(); yylval.node =createSyntaxTree("(", 0, yylineno);		return('('); }
")"		{ count(); yylval.node =createSyntaxTree(")", 0, yylineno);		return(')'); }

[\t\v\n\f ]     { count(); }
[\r]			{}
. 				{ fprintf(stderr, "Error [Lexical] at line %d, col %d, Mysterious character \'%s\'\n", yylineno, yycolumn, yytext); exit(0);}

%%

int yywrap(void)
{
	return 1;
}

void comment()
{
	yycolumn = 0;
    char c, prev = 0;
  
	while ((c = yyinput()) != 0)
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
    // ECHO;
}