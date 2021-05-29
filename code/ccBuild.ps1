# & 'C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvars64.bat'
$arr = $(llvm-config --cxxflags --ldflags --libs all)
$arr[0] = $arr[0].replace('-I', '/I ')
$arr[1] = $arr[1].replace('-LIBPATH:', '/LIBPATH:')
echo "cl /Fe:cc.exe /TP /Od /Z7 $($arr[0]) IRtest.cpp AST.cpp grammarTree.cpp utils.cpp lex.yy.c y.tab.c /link /DEBUG:NONE $($arr[1]) $($arr[2])"