del cc.exe

set TEST_FILE_CC=./functional_test/00_main.c ./functional_test/01_var_defn.c ./functional_test/02_var_defn2.c ./functional_test/03_arr_defn.c ./functional_test/03_var_defn2.c ./functional_test/04_const_defn.c ./functional_test/04_func_defn.c ./functional_test/05_add.c ./functional_test/05_const_array_defn.c ./functional_test/06_mod.c ./functional_test/06_var_defn_func.c ./functional_test/07_comment1.c ./functional_test/08_arr_assign.c ./functional_test/08_comment2.c ./functional_test/09_if.c ./functional_test/10_break.c ./functional_test/10_if_else.c ./functional_test/11_continue.c ./functional_test/11_while.c ./functional_test/13_and.c ./functional_test/14_or.c ./functional_test/15_equal.c ./functional_test/16_greater_eq.c ./functional_test/16_nequal.c ./functional_test/17_less.c ./functional_test/17_less_eq.c ./functional_test/18_cal_prio.c ./functional_test/19_neg_expr.c ./functional_test/20_arr_sum.c ./functional_test/21_suminput.c ./functional_test/22_if_test1.c ./functional_test/23_if_test2.c ./functional_test/24_if_test3.c ./functional_test/25_if_test4.c ./functional_test/26_if_test5.c ./functional_test/27_while_test1.c ./functional_test/28_while_test2.c ./functional_test/29_while_test3.c ./functional_test/30_while_if_test1.c ./functional_test/31_while_if_test2.c ./functional_test/32_while_if_test3.c ./functional_test/33_func_test1.c ./functional_test/34_func_test2.c ./functional_test/35_array_test.c ./functional_test/36_domain_test.c ./functional_test/38_if_complex_expr.c ./functional_test/39_assign_complex_expr.c ./functional_test/40_index_complex_expr.c ./functional_test/41_index_arithmetic_expr.c ./functional_test/42_index_func_ret.c ./functional_test/43_time_prior_plus.c ./functional_test/44_add_prior_equal.c ./functional_test/45_equal_prior_logic.c ./functional_test/46_and_prior_or.c ./functional_test/47_minus_with_sub.c ./functional_test/49_decl_in_defn.c ./functional_test/50_recursion_test1.c


set TEST_FILE_PY=-path ./viewTree/00_main.c_node_tree.txt -path ./viewTree/01_var_defn.c_node_tree.txt -path ./viewTree/02_var_defn2.c_node_tree.txt -path ./viewTree/03_arr_defn.c_node_tree.txt -path ./viewTree/03_var_defn2.c_node_tree.txt -path ./viewTree/04_const_defn.c_node_tree.txt -path ./viewTree/04_func_defn.c_node_tree.txt -path ./viewTree/05_add.c_node_tree.txt -path ./viewTree/05_const_array_defn.c_node_tree.txt -path ./viewTree/06_mod.c_node_tree.txt -path ./viewTree/06_var_defn_func.c_node_tree.txt -path ./viewTree/07_comment1.c_node_tree.txt -path ./viewTree/08_arr_assign.c_node_tree.txt -path ./viewTree/08_comment2.c_node_tree.txt -path ./viewTree/09_if.c_node_tree.txt -path ./viewTree/10_break.c_node_tree.txt -path ./viewTree/10_if_else.c_node_tree.txt -path ./viewTree/11_continue.c_node_tree.txt -path ./viewTree/11_while.c_node_tree.txt -path ./viewTree/13_and.c_node_tree.txt -path ./viewTree/14_or.c_node_tree.txt -path ./viewTree/15_equal.c_node_tree.txt -path ./viewTree/16_greater_eq.c_node_tree.txt -path ./viewTree/16_nequal.c_node_tree.txt -path ./viewTree/17_less.c_node_tree.txt -path ./viewTree/17_less_eq.c_node_tree.txt -path ./viewTree/18_cal_prio.c_node_tree.txt -path ./viewTree/19_neg_expr.c_node_tree.txt -path ./viewTree/20_arr_sum.c_node_tree.txt -path ./viewTree/21_suminput.c_node_tree.txt -path ./viewTree/22_if_test1.c_node_tree.txt -path ./viewTree/23_if_test2.c_node_tree.txt -path ./viewTree/24_if_test3.c_node_tree.txt -path ./viewTree/25_if_test4.c_node_tree.txt -path ./viewTree/26_if_test5.c_node_tree.txt -path ./viewTree/27_while_test1.c_node_tree.txt -path ./viewTree/28_while_test2.c_node_tree.txt -path ./viewTree/29_while_test3.c_node_tree.txt -path ./viewTree/30_while_if_test1.c_node_tree.txt -path ./viewTree/31_while_if_test2.c_node_tree.txt -path ./viewTree/32_while_if_test3.c_node_tree.txt -path ./viewTree/33_func_test1.c_node_tree.txt -path ./viewTree/34_func_test2.c_node_tree.txt -path ./viewTree/35_array_test.c_node_tree.txt -path ./viewTree/36_domain_test.c_node_tree.txt -path ./viewTree/38_if_complex_expr.c_node_tree.txt -path ./viewTree/39_assign_complex_expr.c_node_tree.txt -path ./viewTree/40_index_complex_expr.c_node_tree.txt -path ./viewTree/41_index_arithmetic_expr.c_node_tree.txt -path ./viewTree/42_index_func_ret.c_node_tree.txt -path ./viewTree/43_time_prior_plus.c_node_tree.txt -path ./viewTree/44_add_prior_equal.c_node_tree.txt -path ./viewTree/45_equal_prior_logic.c_node_tree.txt -path ./viewTree/46_and_prior_or.c_node_tree.txt -path ./viewTree/47_minus_with_sub.c_node_tree.txt -path ./viewTree/49_decl_in_defn.c_node_tree.txt -path ./viewTree/50_recursion_test1.c_node_tree.txt

SCC false %TEST_FILE_CC%
python ./viewTree/main.py %TEST_FILE_PY%