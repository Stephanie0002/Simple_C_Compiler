; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @ifWhile() {
entry:
  br label %loopend13

loop8:                                            ; preds = %loopend13
  %arithtmp10 = shl i32 %b.1, 1
  %arithtmp12 = add i32 %a.0, 1
  br label %loopend13

loopend13:                                        ; preds = %loop8, %entry
  %b.1 = phi i32 [ 3, %entry ], [ %arithtmp10, %loop8 ]
  %a.0 = phi i32 [ 0, %entry ], [ %arithtmp12, %loop8 ]
  %cmptmp15 = icmp slt i32 %a.0, 5
  br i1 %cmptmp15, label %loop8, label %ifcont

ifcont:                                           ; preds = %loopend13
  ret i32 %b.1
}

define i32 @main() {
entry:
  %calltmp = call i32 @ifWhile()
  ret i32 %calltmp
}
