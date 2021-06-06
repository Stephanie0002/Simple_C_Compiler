del cc.exe

set ERROR_FILE=./error_test/00_undef_keyword.c ./error_test/01_mys_~.c ./error_test/02_syntax_error.c ./error_test/03_wrong_data_format.c ./error_test/04_wrong_comments.c ./error_test/05_wrongdef_const.c ./error_test/06_wrongdef_var.c ./error_test/07_wrongdef_const.c ./error_test/08_wrongdef_var.c ./error_test/09_undef_var.c ./error_test/10_wrong_use.c ./error_test/11_undef_func.c ./error_test/12_reapdef_const.c ./error_test/13_reapdef_var.c ./error_test/14_reapdef_func.c ./error_test/15_exp_error.c ./error_test/16_func_call_error.c ./error_test/17_func_ret_error.c ./error_test/18_break_continue_error.c ./error_test/19_blank_test.c 

SCC false %ERROR_FILE%