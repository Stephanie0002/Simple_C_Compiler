; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @fact(i32 %n) {
entry:
  %cmptmp = icmp eq i32 %n, 0
  br i1 %cmptmp, label %then, label %ifcont

then:                                             ; preds = %entry
  ret i32 1

ifcont:                                           ; preds = %entry
  %arithtmp = add i32 %n, -1
  %calltmp = call i32 @fact(i32 %arithtmp)
  %arithtmp6 = mul i32 %calltmp, %n
  ret i32 %arithtmp6
}

define i32 @main() {
entry:
  %calltmp = call i32 @fact(i32 4)
  ret i32 %calltmp
}
