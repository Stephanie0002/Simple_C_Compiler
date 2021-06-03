%option yylineno

%{
#include <cstdio>
#include <cstdlib>
#include "y.tab.h"
#include "syntaxTree.h"

using namespace std;

void formerComment();
void latterComment();
void count(void);

int yycolumn = 1;

extern int isNewError(int error_lineno);
%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
WrongH		[a-zA-Z0-9]
Dec			0|([1-9]{D}*)
Oct 		0[0-7]+
Hex			0[xX]{H}+
INT			{Dec}|{Oct}|{Hex}
UNDESIGNED	"for"|"switch"|"case"|"char"|"double"|"float"|"bool"|"void"|"struct"
WrongOct	0[0-9]+
WrongHex	0[xX]{WrongH}+
FLOAT		{D}"."{D}+
SCIEN		({FLOAT}|{INT})[eE]*[+-]*[0]*({FLOAT}|{INT})

%%
"/*"			{ count(); formerComment(); }
"*/"			{ count(); latterComment(); }
"//"[^\n]*      {  }

{UNDESIGNED} 	{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Undifined reserved word \'%s\'.\n", yylineno, yycolumn, yytext); return(UNDESIGNED);}
{FLOAT}			{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Wrong number format \'%s\'.\n", yylineno, yycolumn, yytext); return(WrongNumberFormat);}
{SCIEN}			{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Wrong number format \'%s\'.\n", yylineno, yycolumn, yytext); return(WrongNumberFormat);}
{WrongOct}		{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Illegal octal number \'%s\'.\n", yylineno, yycolumn, yytext); return(WrongNumberFormat);}
{WrongHex}		{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Illegal hex number \'%s\'.\n", yylineno, yycolumn, yytext); return(WrongNumberFormat);}

"const"			{ count(); yylval.node = createSyntaxTree("CONST", 0, yylineno); 	return(CONST); }
"int"			{ count(); yylval.node = createSyntaxTree("INT", 0, yylineno); 		return(INT); }
"if"			{ count(); yylval.node = createSyntaxTree("IF", 0, yylineno); 		return(IF); }
"else"			{ count(); yylval.node = createSyntaxTree("ELSE", 0, yylineno); 	return(ELSE); }
"while"			{ count(); yylval.node = createSyntaxTree("WHILE", 0, yylineno); 	return(WHILE); }
"break"			{ count(); yylval.node = createSyntaxTree("BREAK", 0, yylineno); 	return(BREAK); }
"continue"		{ count(); yylval.node = createSyntaxTree("CONTINUE", 0, yylineno);	return(CONTINUE); }
"return"		{ count(); yylval.node = createSyntaxTree("RETURN", 0, yylineno); 	return(RETURN); }

{L}({L}|{D})*   { 
	if (yytext[0] >= '0' && yytext[0] <= '9') { 
		if (isNewError(yylineno)){
			fprintf(stderr, "Error [Lexical] at line %d, Col %d: Illegal identifier begin with number \'%d\'\n", yylineno, yycolumn, yytext[0]);
		}
	}
	count(); yylval.node = createSyntaxTree("IDENT", 0, yylineno);  return(IDENT);  }
{INT}  			{ count(); yylval.node = createSyntaxTree("NUMBER", 0, yylineno); return(NUMBER); }

"&&"	{ count(); yylval.node = createSyntaxTree("AND_OP", 0, yylineno);	return(AND_OP); }
"||"	{ count(); yylval.node = createSyntaxTree("OR_OP", 0, yylineno); 	return(OR_OP); }
"<="	{ count(); yylval.node = createSyntaxTree("LE_OP", 0, yylineno); 	return(LE_OP); }
">="	{ count(); yylval.node = createSyntaxTree("GE_OP", 0, yylineno); 	return(GE_OP); }
"=="	{ count(); yylval.node = createSyntaxTree("EQ_OP", 0, yylineno); 	return(EQ_OP); }
"!="	{ count(); yylval.node = createSyntaxTree("NE_OP", 0, yylineno); 	return(NE_OP); }
";"		{ count(); yylval.node = createSyntaxTree(";", 0, yylineno);		return(';'); }
","		{ count(); yylval.node = createSyntaxTree(",", 0, yylineno);		return(','); }
"="		{ count(); yylval.node = createSyntaxTree("=", 0, yylineno);		return('='); }
"["	 	{ count(); yylval.node = createSyntaxTree("[", 0, yylineno);	    return('['); }
"]"		{ count(); yylval.node = createSyntaxTree("]", 0, yylineno);	    return(']'); }
"!"		{ count(); yylval.node = createSyntaxTree("!", 0, yylineno);	    return('!'); }
"+"		{ count(); yylval.node = createSyntaxTree("+", 0, yylineno);	    return('+'); }
"-"		{ count(); yylval.node = createSyntaxTree("-", 0, yylineno);		return('-'); }
"*"		{ count(); yylval.node = createSyntaxTree("*", 0, yylineno);		return('*'); }
"/"		{ count(); yylval.node = createSyntaxTree("/", 0, yylineno);		return('/'); }
"%"		{ count(); yylval.node = createSyntaxTree("%", 0, yylineno);		return('%'); } 
"<"		{ count(); yylval.node = createSyntaxTree("<", 0, yylineno);		return('<'); }
">"		{ count(); yylval.node = createSyntaxTree(">", 0, yylineno);		return('>'); }
"{"		{ count(); yylval.node = createSyntaxTree("{", 0, yylineno);		return('{'); }
"}"		{ count(); yylval.node = createSyntaxTree("}", 0, yylineno);		return('}'); }
"("		{ count(); yylval.node = createSyntaxTree("(", 0, yylineno);		return('('); }
")"		{ count(); yylval.node = createSyntaxTree(")", 0, yylineno);		return(')'); }

[\v\n\f ]     { count(); }
[ \t\r]			{}
. 				{ if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at line %d, Col %d: Mysterious character \'%s\'.\n", yylineno, yycolumn, yytext); }

%%

int yywrap(void)
{
	return 1;
}

void formerComment()
{
    char c, prev = 0;
  
	while ((c = yyinput()) != 0)
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	if (isNewError(yylineno)){
		fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Unmatched comment for \'/*\'.\n", yylineno, yycolumn);
	}
}

void latterComment(){
	if (isNewError(yylineno)){
		fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Unmatched comment for \'*/\'.\n", yylineno, yycolumn);
	}
}

void count(void)
{
	for (int i = 0; yytext[i] != '\0'; i++) {
		if (yytext[i] == '\n') {
			yycolumn = 1;
        }
		else if (yytext[i] == '\t') {
			yycolumn += 4 - (yycolumn % 4);
        }
		else {
			yycolumn++;
        }
    }
	//ECHO;
}