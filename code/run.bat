del cc.exe

set TEST_FILE_CC=./functional_test/00_main.c ./functional_test/01_var_defn.c ./functional_test/02_var_defn2.c ./functional_test/03_arr_defn.c ./functional_test/03_var_defn2.c ./functional_test/04_const_defn.c ./functional_test/04_func_defn.c ./functional_test/05_add.c ./functional_test/05_const_array_defn.c ./functional_test/06_mod.c ./functional_test/06_var_defn_func.c ./functional_test/07_comment1.c ./functional_test/08_arr_assign.c ./functional_test/08_comment2.c ./functional_test/09_if.c ./functional_test/10_break.c ./functional_test/10_if_else.c ./functional_test/11_continue.c ./functional_test/11_while.c ./functional_test/12_getint.c ./functional_test/13_and.c ./functional_test/14_or.c ./functional_test/15_equal.c ./functional_test/16_greater_eq.c ./functional_test/16_nequal.c ./functional_test/17_less.c ./functional_test/17_less_eq.c ./functional_test/18_cal_prio.c ./functional_test/19_neg_expr.c ./functional_test/20_arr_sum.c ./functional_test/21_suminput.c ./functional_test/22_if_test1.c ./functional_test/23_if_test2.c ./functional_test/24_if_test3.c ./functional_test/25_if_test4.c ./functional_test/26_if_test5.c ./functional_test/27_while_test1.c ./functional_test/28_while_test2.c ./functional_test/29_while_test3.c ./functional_test/30_while_if_test1.c ./functional_test/31_while_if_test2.c ./functional_test/32_while_if_test3.c ./functional_test/33_func_test1.c ./functional_test/34_func_test2.c ./functional_test/35_array_test.c ./functional_test/36_domain_test.c ./functional_test/38_if_complex_expr.c ./functional_test/39_assign_complex_expr.c ./functional_test/40_index_complex_expr.c ./functional_test/41_index_arithmetic_expr.c ./functional_test/42_index_func_ret.c ./functional_test/43_time_prior_plus.c ./functional_test/44_add_prior_equal.c ./functional_test/45_equal_prior_logic.c ./functional_test/46_and_prior_or.c ./functional_test/47_minus_with_sub.c ./functional_test/49_decl_in_defn.c ./functional_test/50_recursion_test1.c
set ERROR_FILE_CC=../test/error_test/00_~.c ../test/error_test/01_a[10][2].c ../test/error_test/02_miss_semi.c ../test/error_test/03_wrong_number.c ../test/error_test/04_resolved_word.c ../test/error_test/05_nested_comments.c ../test/error_test/07_undefined_j.c ../test/error_test/08_array_init_G_def.c

flex cc.l
bison -vdty cc.y
g++ -std=c++11 -o cc main.cpp grammarTree.cpp Parser.cpp Symbol.cpp hashSet.cpp utils.cpp lex.yy.c y.tab.c
cc false %TEST_FILE_CC%
cc false %ERROR_FILE_CC%
@REM cc false ../test/error_test/18_illegal_idx.c