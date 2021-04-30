ROOT = cc

lab : lex.yy.c y.tab.c
	gcc -o ${ROOT} lex.yy.c y.tab.c

lex.yy.c : y.tab.c ${ROOT}.l
	lex ${ROOT}.l

y.tab.c : ${ROOT}.y
	yacc -d --locations ${ROOT}.y

clean :
	rm *.c *.h ${ROOT}