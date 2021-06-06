

filename=['00_main.c','01_var_defn.c','02_var_defn2.c',\
          '03_arr_defn.c','03_var_defn2.c','04_const_defn.c',\
          '04_func_defn.c','05_add.c','05_const_array_defn.c',\
          '06_mod.c','06_var_defn_func.c','07_comment1.c',\
          '08_arr_assign.c','08_comment2.c','09_if.c',\
          '10_break.c','10_if_else.c','11_continue.c',\
          '11_while.c','13_and.c',\
          '14_or.c','15_equal.c','16_greater_eq.c',\
          '16_nequal.c','17_less.c','17_less_eq.c',\
          '18_cal_prio.c','19_neg_expr.c','20_arr_sum.c',\
          '21_suminput.c','22_if_test1.c','23_if_test2.c',\
          '24_if_test3.c','25_if_test4.c','26_if_test5.c',\
          '27_while_test1.c','28_while_test2.c','29_while_test3.c',\
          '30_while_if_test1.c','31_while_if_test2.c',\
          '32_while_if_test3.c','33_func_test1.c','34_func_test2.c',\
          '38_if_complex_expr.c',\
          '39_assign_complex_expr.c','40_index_complex_expr.c',\
          '41_index_arithmetic_expr.c',\
          '43_time_prior_plus.c','44_add_prior_equal.c',\
          '45_equal_prior_logic.c','46_and_prior_or.c',\
          '47_minus_with_sub.c','49_decl_in_defn.c',\
          '50_recursion_test1.c']
error_file=[]
py='./viewTree/'
ir='./ir/'
fun='./functional_test/'

with open('LLtoBCtoS.txt','w') as file:
    for name in filename:
        name=ir+name
        print('llvm-as '+name+'.ll -o '+name+'.bc')
        file.write('llvm-as '+name+'.ll -o '+name+'.bc\n')
        print('llc '+name+'.bc -o '+name+'.s')
        file.write('llc '+name+'.bc -o '+name+'.s\n')
        # print('clang '+name+'.s -l ./x64/Debug/libsysy -o '+name+'.exe')
        # file.write('clang '+name+'.s -l ./x64/Debug/libsysy -o '+name+'.exe\n')
        
with open('EXEC.txt','w') as file:
    print('set TEST_FILE_CC=')
    file.write('set TEST_FILE_CC=')
    for name in filename:
        name=fun+name
        print(name+' ')
        file.write(name+' ')

with open('PY_Graph.txt','w') as file:
    print('set TEST_FILE_PY=')
    file.write('set TEST_FILE_PY=')
    for name in filename:
        name=py+name
        print('-path '+name+'_node_tree.txt ')
        file.write('-path '+name+'_node_tree.txt ')