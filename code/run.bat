del cc
flex cc.l
bison -vdty cc.y
g++ -std=c++11 -o cc main.cpp syntaxTree.cpp Parser.cpp Symbol.cpp hashSet.cpp utils.cpp lex.yy.c y.tab.c
cc true ../test/error_test/test2.c