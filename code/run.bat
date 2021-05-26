del cc
flex cc.l
bison -vdty cc.y
g++ -std=c++11 -o cc main.cpp syntaxTree.cpp Parser.cpp symbol.cpp hashSet.cpputils.cpp lex.yy.c y.tab.c
cc ture test2.c