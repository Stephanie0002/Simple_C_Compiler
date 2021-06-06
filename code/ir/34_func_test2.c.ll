; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @func1() {
entry:
  ret i32 1
}

define i32 @func2() {
entry:
  ret i32 2
}

define i32 @func3() {
entry:
  ret i32 4
}

define i32 @func4() {
entry:
  ret i32 24
}

define i32 @main() {
entry:
  %calltmp = call i32 @func1()
  %calltmp1 = call i32 @func2()
  %arithtmp = add i32 %calltmp, %calltmp1
  %calltmp2 = call i32 @func3()
  %arithtmp3 = add i32 %arithtmp, %calltmp2
  %calltmp4 = call i32 @func4()
  %arithtmp5 = add i32 %arithtmp3, %calltmp4
  %arithtmp11 = add i32 %arithtmp5, 96
  ret i32 %arithtmp11
}
