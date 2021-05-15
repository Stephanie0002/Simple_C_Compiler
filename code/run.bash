rm -rf cc.exe
flex cc.l
bison -vdty --locations cc.y
g++ -std=c++11 -o cc grammarTree.cpp utils.cpp lex.yy.c y.tab.c
./cc false test1.c test2.c 