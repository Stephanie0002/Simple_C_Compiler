# Simple_C_Compiler
**1.概述**

code文件夹存放代码、测试文件、及批处理文件等

**2.code文件夹结构内容**

/viewTree ---存放一个python项目，用于可视化语法分析树，需要电脑上安装有Graphvix方可显示出图片（用于可视化语法树的文件也在语义分析后生成在该目录下）

/functional_test---存放功能性测试代码，内部的input.txt存放了批处理中需要的输入数据

/error_test---存放错误检测测试代码

/bat_info_generate ---存放一个python项目，用于批量输出一些批处理需要的数据

/ir ---存放一个python项目，生成的中间代码、汇编代码会在该文件夹内

/libsysy---存放一个VS项目，生成用于输入输出的动态dll库，输入类似下面的指令执行中间代码可以完成中间代码中相关输入输出（ 如getint(),  putint(), putch() ）

`lli --dlopen="x64/Debug/libsysy.dll" .\main.ll`

**3. 编译**

文件中是已经编译好的SCC.exe，各种生成的中间代码、图片也已经生成好了。

若想重新编译.l .y，需要双击compile.bat，编译后如果报错lex内\#include <io.h>或\#include <unistd.h>有错，就互相替换一下，总之这俩会有一个符合你的平台。

然后打开SCC.sln，编译生成exe文件（是不能直接运行的，要给命令行参数），然后将exe文件拷贝进入code文件夹下，接着就可以进行4.使用

**4.使用**
windows下：

- *测试IR，也即完整跑通*：

```bash
./test_ir.bat              
```

执行后解析functional_test内文件并生成中间代码汇编代码于ir文件夹内，运行中需要copy input.txt内容输入

- *OR 进行语法树测试*：

```bash
./test_syntax.bat          
```

除了解析functional_test内文件并生成中间代码汇编代码于ir文件夹内，还启动pyhton程序可视化语法树，生成的图片在viewTree文件夹内。运行中需要copy input.txt内容输入

可根据需要修改其内  `TEST_FILE_CC`  为需要编译的文件名

`TEST_FILE_PY`    为cc生成的文件名类似 ： -path *.c_node_tree.txt

(该python文件`usage: main.py [-h] [-path PATH] [-path PATH] ... [-path PATH]`)

- *OR 进行错误检测测试*：

```bash
./test_semantic.bat          
```

解析error_test内文件，并报错。

`注1`：必须安装提供graphviz

linux下：sudo apt install graphviz graphviz-doc;pip install graphviz

Windows下：参考链接https://www.jianshu.com/p/8ede808e6f92

`注2`：必须安装提供llvm

linux下：sudo apt install cmake llvm

windows下：需要在官网下载源码并在本地用CMake创建VS工程，然后借助VS 来 Build，最后还需要配置环境变量等，网上教程很多。

llvm执行命令：

```bash
clang -c -emit-llvm test.c -o test.bc # 把c语言代码翻译为llvm字节码  
# 我们应该用llvm-as test1.ll test1.bc把我们的中间代码翻译为字节码
clang -S -fobjc-arc test.bc -o test.s # 把字节码翻译为汇编代码
clang test.s -o test.exe # 把汇编代码翻译为可执行文件
```

