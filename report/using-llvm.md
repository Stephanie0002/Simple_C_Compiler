target: LLVM IR

# ref

## 官方文档

- https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html
- https://llvm.org/docs/LangRef.html
- https://llvm.org/docs/ProgrammersManual.html

## 二手中文文档

- https://llvm-tutorial-cn.readthedocs.io/en/latest/index.html

# install

Do NOT use prebuilt binaries. Follow https://llvm.org/docs/GettingStartedVS.html#getting-started w/ adjustments:

Step 5: I'm using

```
D:\Downloads\cmake-3.20.2-windows-x86_64\cmake-3.20.2-windows-x86_64\bin\cmake.exe -G 'Visual Studio 15 2017 Win64' -Thost=x64 -DLLVM_TARGETS_TO_BUILD="X86" -DLLVM_ENABLE_PROJECTS="libcxx;libcxxabi" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=d:\LLVM ../llvm
```

Step 7: Be sure to use Release Build in llvm.sln

The Build takes ~ 1 hr