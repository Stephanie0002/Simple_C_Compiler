# Simple_C_Compiler
**1.概述**

本文件夹存放lex，yacc代码等

**2.文件夹结构**

/viewTree ---存放一个python项目，用于可视化语法分析树，需要电脑上安装有Graphvix方可显示出图片

**3.使用**
linux：

*Run*：

```bash
bash run.bash              
```

进行语法分析，输出语法树文件，需要修改其内  `RUN_FILE_CC` 的值为需要编译的文件名

*OR 进行语法树测试*：

```bash
bash test.bash
```

进行语法分析，输出语法树文件并可视化，需要修改其内  `TEST_FILE_CC`  为需要编译的文件名

`TEST_FILE_PY`    为cc生成的文件名类似 ： -path *.c_node_tree.txt

(该python文件`usage: main.py [-h] [-path PATH] [-path PATH] ... [-path PATH]`)

windows: ???

`注1`：必须安装提供graphviz

linux下：sudo apt install graphviz graphviz-doc;pip install graphviz

Windows下：参考链接https://www.jianshu.com/p/8ede808e6f92

`注2`：必须安装提供llvm

linux下：sudo apt install cmake llvm

windows下：进入https://github.com/llvm/llvm-project/releases/tag/llvmorg-12.0.0 下载LLVM-12.0.0-win64.exe和Source code(zip)

   exe是win下傻瓜式安装软件，点开一直下一步就好，Source code(zip)解压后.\llvm-project-llvmorg-12.0.0\llvm\include\内有我们代码要引用的头文件

llvm执行命令：

```bash
clang -c -emit-llvm test.c -o test.bc # 把c语言代码翻译为llvm字节码  我们应该用llvm-as test1.ll test1.bc把我们的中间代码翻译为字节码
clang -S -fobjc-arc test.bc -o test.s # 把字节码翻译为汇编代码
clang test.s -o test.exe # 把汇编代码翻译为可执行文件
```

