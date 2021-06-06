; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @main() {
entry:
  br label %loop

loop:                                             ; preds = %entry, %then
  %a.0 = phi i32 [ 10, %entry ], [ %arithtmp, %then ]
  %cmptmp = icmp sgt i32 %a.0, 5
  br i1 %cmptmp, label %then, label %ifcont

then:                                             ; preds = %loop
  %arithtmp = add i32 %a.0, -1
  br label %loop

ifcont:                                           ; preds = %loop
  ret i32 %a.0
}
