%option yylineno
%option yywrap

%{
#include <cstdio>
#include <cstdlib>
#include "y.tab.h"
#include "grammarTree.h"

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
Dec			0|([1-9]{D}*)
Oct 		0[0-7]+
Hex			0[xX]{H}+
INT			{Dec}|{Oct}|{Hex}
UNDESIGNED	"char"|"double"|"float"|"bool"
WrongOct	0[0-9]+
WrongH		[a-zA-Z0-9]
WrongHex	0[xX]{WrongH}+
WrongInt	[0][0]+{INT}
FLOAT		{D}"."{D}+
SCIEN		({FLOAT}|{WrongInt}|{INT})[eE][+-]*[0]*({FLOAT}|{WrongInt}|{INT})
BOOL		"true"|"false"

%%
"/*"			{ formerComment(); }
"*/"			{ latterComment(); }
"//"[^\n]*      { char c = yyinput(); while (c!='\n') c=yyinput(); }

{UNDESIGNED} 	{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Undefined data type \'%s\'.\n", yylineno, yycolumn, yytext); return(UNDESIGNED);}
{FLOAT}			{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Unsupported float/double format \'%s\'.\n", yylineno, yycolumn, yytext); return(WrongNumberFormat);}
{SCIEN}			{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Unsupported scientific format \'%s\'.\n", yylineno, yycolumn, yytext); return(WrongNumberFormat);}
{BOOL}			{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Unsupported bool format \'%s\'.\n", yylineno, yycolumn, yytext); return(WrongNumberFormat);}
{WrongInt}		{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Confusing decimal format \'%s\'?\n", yylineno, yycolumn, yytext); return(WrongNumberFormat);}
{WrongOct}		{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Illegal octal number \'%s\'.\n", yylineno, yycolumn, yytext); return(WrongNumberFormat);}
{WrongHex}		{ count(); if (isNewError(yylineno)) fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Illegal hex number \'%s\'.\n", yylineno, yycolumn, yytext); return(WrongNumberFormat);}

"const"			{ count(); yylval.node = createGrammarTree("CONST", 0, yylineno); 	return(CONST); }
"int"			{ count(); yylval.node = createGrammarTree("INT", 0, yylineno); 		return(INT); }
"if"			{ count(); yylval.node = createGrammarTree("IF", 0, yylineno); 		return(IF); }
"else"			{ count(); yylval.node = createGrammarTree("ELSE", 0, yylineno); 	return(ELSE); }
"while"			{ count(); yylval.node = createGrammarTree("WHILE", 0, yylineno); 	return(WHILE); }
"break"			{ count(); yylval.node = createGrammarTree("BREAK", 0, yylineno); 	return(BREAK); }
"continue"		{ count(); yylval.node = createGrammarTree("CONTINUE", 0, yylineno);	return(CONTINUE); }
"return"		{ count(); yylval.node = createGrammarTree("RETURN", 0, yylineno); 	return(RETURN); }

{L}({L}|{D})*   { count(); yylval.node = createGrammarTree("IDENT", 0, yylineno);  return(IDENT);  }
{INT}  			{ count(); yylval.node = createGrammarTree("NUMBER", 0, yylineno); return(NUMBER); }

"&&"	{ count(); yylval.node = createGrammarTree("AND_OP", 0, yylineno);	return(AND_OP); }
"||"	{ count(); yylval.node = createGrammarTree("OR_OP", 0, yylineno); 	return(OR_OP); }
"<="	{ count(); yylval.node = createGrammarTree("LE_OP", 0, yylineno); 	return(LE_OP); }
">="	{ count(); yylval.node = createGrammarTree("GE_OP", 0, yylineno); 	return(GE_OP); }
"=="	{ count(); yylval.node = createGrammarTree("EQ_OP", 0, yylineno); 	return(EQ_OP); }
"!="	{ count(); yylval.node = createGrammarTree("NE_OP", 0, yylineno); 	return(NE_OP); }
";"		{ count(); yylval.node = createGrammarTree(";", 0, yylineno);		return(';'); }
","		{ count(); yylval.node = createGrammarTree(",", 0, yylineno);		return(','); }
"="		{ count(); yylval.node = createGrammarTree("=", 0, yylineno);		return('='); }
"["	 	{ count(); yylval.node = createGrammarTree("[", 0, yylineno);	    return('['); }
"]"		{ count(); yylval.node = createGrammarTree("]", 0, yylineno);	    return(']'); }
"!"		{ count(); yylval.node = createGrammarTree("!", 0, yylineno);	    return('!'); }
"+"		{ count(); yylval.node = createGrammarTree("+", 0, yylineno);	    return('+'); }
"-"		{ count(); yylval.node = createGrammarTree("-", 0, yylineno);		return('-'); }
"*"		{ count(); yylval.node = createGrammarTree("*", 0, yylineno);		return('*'); }
"/"		{ count(); yylval.node = createGrammarTree("/", 0, yylineno);		return('/'); }
"%"		{ count(); yylval.node = createGrammarTree("%", 0, yylineno);		return('%'); } 
"<"		{ count(); yylval.node = createGrammarTree("<", 0, yylineno);		return('<'); }
">"		{ count(); yylval.node = createGrammarTree(">", 0, yylineno);		return('>'); }
"{"		{ count(); yylval.node = createGrammarTree("{", 0, yylineno);		return('{'); }
"}"		{ count(); yylval.node = createGrammarTree("}", 0, yylineno);		return('}'); }
"("		{ count(); yylval.node = createGrammarTree("(", 0, yylineno);		return('('); }
")"		{ count(); yylval.node = createGrammarTree(")", 0, yylineno);		return(')'); }

[\v\n\f ]     { count(); }
[ \t\r]			{}
. 				{ 
	if (isNewError(yylineno)) {
		if (yytext[0] == '\'' || yytext[0] == '"'){
			fprintf(stderr, "Error [Lexical] at line %d, Col %d: Unsupported char/string.\n", yylineno, yycolumn);
		}
		else {
			fprintf(stderr, "Error [Lexical] at line %d, Col %d: Mysterious character \'%s\'.\n", yylineno, yycolumn, yytext); 
		}
	}
}
	

%%

int yywrap(void)
{
	yy_flush_buffer(YY_CURRENT_BUFFER);
	{BEGIN INITIAL;}
	return 1;
}

void formerComment()
{
    char c = yyinput();
  
	while (1)
	{
		if (c == '*' ){
			c = yyinput();
			if (c == '/'){
				break;
			}
			else{
				unput(c);
			}
		}
		else if(c == EOF){
			if (isNewError(yylineno)){
				fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Unmatched comment for \"/*\".\n", yylineno, yycolumn);
			}
			break;
		}
		c = yyinput();
	}
}

void latterComment(){
	if (isNewError(yylineno)){
		fprintf(stderr, "Error [Lexical] at Line %d, Col %d: Unmatched comment for \"*/\".\n", yylineno, yycolumn);
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
}