target: LLVM IR

# Test log

- Glbl VarDecl + FuncDef
  - ？全局变量初始化为0
- Func call
- arithmetic BinExpr
- return
- IF: 09 10
- WHILE: 10 11

# 资源

## 教程

- https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html
- 二手中文 https://llvm-tutorial-cn.readthedocs.io/en/latest/index.html
- 系列 逐步讲解 https://www.bilibili.com/video/av626821579/

测试人员注意

- LLVM IR 指令速学 https://zhuanlan.zhihu.com/p/64427829

## 参考

- 稍微友好一些 https://llvm.org/docs/ProgrammersManual.html
- https://llvm.org/docs/LangRef.html
- https://llvm.org/doxygen/classllvm_1_1IRBuilderBase.html

## 前人工作借鉴

- w/ English report: https://github.com/huangyangyi/Our-Pascal-Compiler
- 介绍了完整流水线 http://www.cppblog.com/woaidongmao/archive/2009/11/11/100693.aspx https://github.com/lsegal/my_toy_compiler
- GitHub 搜 zju llvm 还可扒到若干仓库，参考价值略逊

# install

Do NOT use prebuilt binaries. Follow https://llvm.org/docs/GettingStartedVS.html#getting-started w/ adjustments:

Step 5: I'm using

```
D:\Downloads\cmake-3.20.2-windows-x86_64\cmake-3.20.2-windows-x86_64\bin\cmake.exe -G 'Visual Studio 15 2017 Win64' -Thost=x64 -DLLVM_TARGETS_TO_BUILD="X86" -DLLVM_ENABLE_PROJECTS="libcxx;libcxxabi" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=d:\LLVM ../llvm
```

Step 7: Be sure to use Release Build in llvm.sln

The Build takes ~ 1 hr

- Note: The implementation of some debugging function (though found in `include/`) is not included in Release build. 主程链接不起来可以 Google 一下

# portability 

Lexical Analysis & Syntax Analysis: `cc.l` and `cc.y` are translated into C src code. Both Windows (w/ batch script) and Linux (w/ make) are viable for the process, using `flex` and `bison`. Translated src can be built using `MSVC` or `g++` on Windows or `g++` on Linux (ad-hoc patch applied to `.l`).

Parse Tree operations are written in portable C++.

IR generation relies on LLVM, so the build depends heavily on its installation. The ABI of libraries is to blame for this. For example, if you installed LLVM using Visual Studio on Windows, then you'd better build your project with VS, too.

# 目前存在问题

- 词法和语法的代码 C 和 C++ 杂糅，存在隐患。但反正能跑。有时间审阅代码，或者全部生成成 .cpp
- AST 生成严重依赖于 tailor 后 Parse Tree 的结构
- 需要再想怎么测试到 IR

std::move std::unique_ptr 

If one does not use a platform, then he must also figure out outputting ELF object file.
An alternative approach will be `AST -> 拍脑袋 IR -> Target Arch Assembly Text -> Simulator/Assembler`.