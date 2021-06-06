set TEST_FILE_CC=./functional_test/00_main.c ./functional_test/01_var_defn.c ./functional_test/02_var_defn2.c ./functional_test/03_arr_defn.c ./functional_test/03_var_defn2.c ./functional_test/04_const_defn.c ./functional_test/04_func_defn.c ./functional_test/05_add.c ./functional_test/05_const_array_defn.c ./functional_test/06_mod.c ./functional_test/06_var_defn_func.c ./functional_test/07_comment1.c ./functional_test/08_arr_assign.c ./functional_test/08_comment2.c ./functional_test/09_if.c ./functional_test/10_break.c ./functional_test/10_if_else.c ./functional_test/11_continue.c ./functional_test/11_while.c ./functional_test/13_and.c ./functional_test/14_or.c ./functional_test/15_equal.c ./functional_test/16_greater_eq.c ./functional_test/16_nequal.c ./functional_test/17_less.c ./functional_test/17_less_eq.c ./functional_test/18_cal_prio.c ./functional_test/19_neg_expr.c ./functional_test/20_arr_sum.c ./functional_test/21_suminput.c ./functional_test/22_if_test1.c ./functional_test/23_if_test2.c ./functional_test/24_if_test3.c ./functional_test/25_if_test4.c ./functional_test/26_if_test5.c ./functional_test/27_while_test1.c ./functional_test/28_while_test2.c ./functional_test/29_while_test3.c ./functional_test/30_while_if_test1.c ./functional_test/31_while_if_test2.c ./functional_test/32_while_if_test3.c ./functional_test/33_func_test1.c ./functional_test/34_func_test2.c ./functional_test/38_if_complex_expr.c ./functional_test/39_assign_complex_expr.c ./functional_test/40_index_complex_expr.c ./functional_test/41_index_arithmetic_expr.c ./functional_test/43_time_prior_plus.c ./functional_test/44_add_prior_equal.c ./functional_test/45_equal_prior_logic.c ./functional_test/46_and_prior_or.c ./functional_test/47_minus_with_sub.c ./functional_test/49_decl_in_defn.c ./functional_test/50_recursion_test1.c 

SCC false %TEST_FILE_CC%

llvm-as ./ir/00_main.c.ll -o ./ir/00_main.c.bc
llc ./ir/00_main.c.bc -o ./ir/00_main.c.s
llvm-as ./ir/01_var_defn.c.ll -o ./ir/01_var_defn.c.bc
llc ./ir/01_var_defn.c.bc -o ./ir/01_var_defn.c.s
llvm-as ./ir/02_var_defn2.c.ll -o ./ir/02_var_defn2.c.bc
llc ./ir/02_var_defn2.c.bc -o ./ir/02_var_defn2.c.s
llvm-as ./ir/03_arr_defn.c.ll -o ./ir/03_arr_defn.c.bc
llc ./ir/03_arr_defn.c.bc -o ./ir/03_arr_defn.c.s
llvm-as ./ir/03_var_defn2.c.ll -o ./ir/03_var_defn2.c.bc
llc ./ir/03_var_defn2.c.bc -o ./ir/03_var_defn2.c.s
llvm-as ./ir/04_const_defn.c.ll -o ./ir/04_const_defn.c.bc
llc ./ir/04_const_defn.c.bc -o ./ir/04_const_defn.c.s
llvm-as ./ir/04_func_defn.c.ll -o ./ir/04_func_defn.c.bc
llc ./ir/04_func_defn.c.bc -o ./ir/04_func_defn.c.s
llvm-as ./ir/05_add.c.ll -o ./ir/05_add.c.bc
llc ./ir/05_add.c.bc -o ./ir/05_add.c.s
llvm-as ./ir/05_const_array_defn.c.ll -o ./ir/05_const_array_defn.c.bc
llc ./ir/05_const_array_defn.c.bc -o ./ir/05_const_array_defn.c.s
llvm-as ./ir/06_mod.c.ll -o ./ir/06_mod.c.bc
llc ./ir/06_mod.c.bc -o ./ir/06_mod.c.s
llvm-as ./ir/06_var_defn_func.c.ll -o ./ir/06_var_defn_func.c.bc
llc ./ir/06_var_defn_func.c.bc -o ./ir/06_var_defn_func.c.s
llvm-as ./ir/07_comment1.c.ll -o ./ir/07_comment1.c.bc
llc ./ir/07_comment1.c.bc -o ./ir/07_comment1.c.s
llvm-as ./ir/08_arr_assign.c.ll -o ./ir/08_arr_assign.c.bc
llc ./ir/08_arr_assign.c.bc -o ./ir/08_arr_assign.c.s
llvm-as ./ir/08_comment2.c.ll -o ./ir/08_comment2.c.bc
llc ./ir/08_comment2.c.bc -o ./ir/08_comment2.c.s
llvm-as ./ir/09_if.c.ll -o ./ir/09_if.c.bc
llc ./ir/09_if.c.bc -o ./ir/09_if.c.s
llvm-as ./ir/10_break.c.ll -o ./ir/10_break.c.bc
llc ./ir/10_break.c.bc -o ./ir/10_break.c.s
llvm-as ./ir/10_if_else.c.ll -o ./ir/10_if_else.c.bc
llc ./ir/10_if_else.c.bc -o ./ir/10_if_else.c.s
llvm-as ./ir/11_continue.c.ll -o ./ir/11_continue.c.bc
llc ./ir/11_continue.c.bc -o ./ir/11_continue.c.s
llvm-as ./ir/11_while.c.ll -o ./ir/11_while.c.bc
llc ./ir/11_while.c.bc -o ./ir/11_while.c.s
llvm-as ./ir/13_and.c.ll -o ./ir/13_and.c.bc
llc ./ir/13_and.c.bc -o ./ir/13_and.c.s
llvm-as ./ir/14_or.c.ll -o ./ir/14_or.c.bc
llc ./ir/14_or.c.bc -o ./ir/14_or.c.s
llvm-as ./ir/15_equal.c.ll -o ./ir/15_equal.c.bc
llc ./ir/15_equal.c.bc -o ./ir/15_equal.c.s
llvm-as ./ir/16_greater_eq.c.ll -o ./ir/16_greater_eq.c.bc
llc ./ir/16_greater_eq.c.bc -o ./ir/16_greater_eq.c.s
llvm-as ./ir/16_nequal.c.ll -o ./ir/16_nequal.c.bc
llc ./ir/16_nequal.c.bc -o ./ir/16_nequal.c.s
llvm-as ./ir/17_less.c.ll -o ./ir/17_less.c.bc
llc ./ir/17_less.c.bc -o ./ir/17_less.c.s
llvm-as ./ir/17_less_eq.c.ll -o ./ir/17_less_eq.c.bc
llc ./ir/17_less_eq.c.bc -o ./ir/17_less_eq.c.s
llvm-as ./ir/18_cal_prio.c.ll -o ./ir/18_cal_prio.c.bc
llc ./ir/18_cal_prio.c.bc -o ./ir/18_cal_prio.c.s
llvm-as ./ir/19_neg_expr.c.ll -o ./ir/19_neg_expr.c.bc
llc ./ir/19_neg_expr.c.bc -o ./ir/19_neg_expr.c.s
llvm-as ./ir/20_arr_sum.c.ll -o ./ir/20_arr_sum.c.bc
llc ./ir/20_arr_sum.c.bc -o ./ir/20_arr_sum.c.s
llvm-as ./ir/21_suminput.c.ll -o ./ir/21_suminput.c.bc
llc ./ir/21_suminput.c.bc -o ./ir/21_suminput.c.s
llvm-as ./ir/22_if_test1.c.ll -o ./ir/22_if_test1.c.bc
llc ./ir/22_if_test1.c.bc -o ./ir/22_if_test1.c.s
llvm-as ./ir/23_if_test2.c.ll -o ./ir/23_if_test2.c.bc
llc ./ir/23_if_test2.c.bc -o ./ir/23_if_test2.c.s
llvm-as ./ir/24_if_test3.c.ll -o ./ir/24_if_test3.c.bc
llc ./ir/24_if_test3.c.bc -o ./ir/24_if_test3.c.s
llvm-as ./ir/25_if_test4.c.ll -o ./ir/25_if_test4.c.bc
llc ./ir/25_if_test4.c.bc -o ./ir/25_if_test4.c.s
llvm-as ./ir/26_if_test5.c.ll -o ./ir/26_if_test5.c.bc
llc ./ir/26_if_test5.c.bc -o ./ir/26_if_test5.c.s
llvm-as ./ir/27_while_test1.c.ll -o ./ir/27_while_test1.c.bc
llc ./ir/27_while_test1.c.bc -o ./ir/27_while_test1.c.s
llvm-as ./ir/28_while_test2.c.ll -o ./ir/28_while_test2.c.bc
llc ./ir/28_while_test2.c.bc -o ./ir/28_while_test2.c.s
llvm-as ./ir/29_while_test3.c.ll -o ./ir/29_while_test3.c.bc
llc ./ir/29_while_test3.c.bc -o ./ir/29_while_test3.c.s
llvm-as ./ir/30_while_if_test1.c.ll -o ./ir/30_while_if_test1.c.bc
llc ./ir/30_while_if_test1.c.bc -o ./ir/30_while_if_test1.c.s
llvm-as ./ir/31_while_if_test2.c.ll -o ./ir/31_while_if_test2.c.bc
llc ./ir/31_while_if_test2.c.bc -o ./ir/31_while_if_test2.c.s
llvm-as ./ir/32_while_if_test3.c.ll -o ./ir/32_while_if_test3.c.bc
llc ./ir/32_while_if_test3.c.bc -o ./ir/32_while_if_test3.c.s
llvm-as ./ir/33_func_test1.c.ll -o ./ir/33_func_test1.c.bc
llc ./ir/33_func_test1.c.bc -o ./ir/33_func_test1.c.s
llvm-as ./ir/34_func_test2.c.ll -o ./ir/34_func_test2.c.bc
llc ./ir/34_func_test2.c.bc -o ./ir/34_func_test2.c.s
llvm-as ./ir/38_if_complex_expr.c.ll -o ./ir/38_if_complex_expr.c.bc
llc ./ir/38_if_complex_expr.c.bc -o ./ir/38_if_complex_expr.c.s
llvm-as ./ir/39_assign_complex_expr.c.ll -o ./ir/39_assign_complex_expr.c.bc
llc ./ir/39_assign_complex_expr.c.bc -o ./ir/39_assign_complex_expr.c.s
llvm-as ./ir/40_index_complex_expr.c.ll -o ./ir/40_index_complex_expr.c.bc
llc ./ir/40_index_complex_expr.c.bc -o ./ir/40_index_complex_expr.c.s
llvm-as ./ir/41_index_arithmetic_expr.c.ll -o ./ir/41_index_arithmetic_expr.c.bc
llc ./ir/41_index_arithmetic_expr.c.bc -o ./ir/41_index_arithmetic_expr.c.s
llvm-as ./ir/43_time_prior_plus.c.ll -o ./ir/43_time_prior_plus.c.bc
llc ./ir/43_time_prior_plus.c.bc -o ./ir/43_time_prior_plus.c.s
llvm-as ./ir/44_add_prior_equal.c.ll -o ./ir/44_add_prior_equal.c.bc
llc ./ir/44_add_prior_equal.c.bc -o ./ir/44_add_prior_equal.c.s
llvm-as ./ir/45_equal_prior_logic.c.ll -o ./ir/45_equal_prior_logic.c.bc
llc ./ir/45_equal_prior_logic.c.bc -o ./ir/45_equal_prior_logic.c.s
llvm-as ./ir/46_and_prior_or.c.ll -o ./ir/46_and_prior_or.c.bc
llc ./ir/46_and_prior_or.c.bc -o ./ir/46_and_prior_or.c.s
llvm-as ./ir/47_minus_with_sub.c.ll -o ./ir/47_minus_with_sub.c.bc
llc ./ir/47_minus_with_sub.c.bc -o ./ir/47_minus_with_sub.c.s
llvm-as ./ir/49_decl_in_defn.c.ll -o ./ir/49_decl_in_defn.c.bc
llc ./ir/49_decl_in_defn.c.bc -o ./ir/49_decl_in_defn.c.s
llvm-as ./ir/50_recursion_test1.c.ll -o ./ir/50_recursion_test1.c.bc
llc ./ir/50_recursion_test1.c.bc -o ./ir/50_recursion_test1.c.s
