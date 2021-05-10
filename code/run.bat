flex cc.l
@REM copy lex.yy.c lex.yy.cpp
bison -vdty --locations cc.y
@REM copy y.tab.c y.tab.cpp
g++ -std=c++11 -o cc grammarTree.cpp utils.cpp lex.yy.c y.tab.c
cc.exe true test1.c test2.c 