# Simple_C_Compiler

## 概述

本文件夹存放一些临时文件，如报告内容要点等

## 文件夹结构

/文法词法.doc ---描述了lex词法以及yacc语法，lex程序yacc程序基于该文件

## log

### ref  
- http://www.quut.com/c/ANSI-C-grammar-l-1998.html
- http://www.quut.com/c/ANSI-C-grammar-y-1998.html
- https://github.com/IMMORTAL23/ZJU-Course_info/tree/master/junior/%E7%BC%96%E8%AF%91%E5%8E%9F%E7%90%86 
  - Project_1 in particular

### lex_test  
- methodology
  - `return\((.*)\)` -> `printf("$1 ")`
    - yylval yylloc literals main
  - visual
  - `printf\("(.*) "\)` -> `return($1)` ...
- 19_neg_expr 商议增加八进制的NUMBER 否则无法识别 0
- 04_const_defn 08_comment2 12_array_traverse 38_if_complex_expr 99_register_realloc P
