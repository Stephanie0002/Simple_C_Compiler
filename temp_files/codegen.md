
IRBuilder 示例 https://llvm.org/doxygen/IRBuilder_8h_source.html#l01603

```c++
   Value *CreateNot(Value *V, const Twine &Name = "") {
     if (auto *VC = dyn_cast<Constant>(V))
       return Insert(Folder.CreateNot(VC), Name);
     return Insert(BinaryOperator::CreateNot(V), Name);
   }
```