del cc.exe
RUN_FILE_CC="./functional_test/00_main.c ./functional_test/01_var_defn.c"

rm -rf cc
flex cc.l
bison -vdty cc.y
g++ -std=c++11 -o cc grammarTree.cpp utils.cpp lex.yy.c y.tab.c
./cc false $RUN_FILE_CC
