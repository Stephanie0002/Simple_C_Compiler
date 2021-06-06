; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @main() {
entry:
  br label %loopend

loop:                                             ; preds = %loopend
  %arithtmp = add i32 %a.0, -1
  %cmptmp = icmp eq i32 %arithtmp, 5
  br i1 %cmptmp, label %afterloop, label %loopend

loopend:                                          ; preds = %loop, %entry
  %a.0 = phi i32 [ 10, %entry ], [ %arithtmp, %loop ]
  %cmptmp4 = icmp sgt i32 %a.0, 0
  br i1 %cmptmp4, label %loop, label %afterloop

afterloop:                                        ; preds = %loop, %loopend
  %a.1 = phi i32 [ %a.0, %loopend ], [ %arithtmp, %loop ]
  ret i32 %a.1
}
