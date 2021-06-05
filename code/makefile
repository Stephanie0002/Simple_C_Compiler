ROOT = cc

cc.exe : grammarTree.cpp utils.cpp lex.yy.c y.tab.c
	echo "DEPRECATED"
	# g++ -std=c++11 -o cc.exe grammarTree.cpp utils.cpp lex.yy.c y.tab.c

# lex_test : 

lex.yy.c : y.tab.c cc.l
	flex --nounistd --posix-compat cc.l

y.tab.c : cc.y
	bison -vdty --locations cc.y

clean :
	rm -f lex.yy.c y.tab.c y.tab.h y.output cc.exe