; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@a = global i32 0

define i32 @myFunc(i32 %a, i32 %b, i32 %c) {
entry:
  br label %loopend

loop:                                             ; preds = %loopend
  %arithtmp = add i32 %b2.0, -1
  br label %loopend

loopend:                                          ; preds = %loop, %entry
  %b2.0 = phi i32 [ %b, %entry ], [ %arithtmp, %loop ]
  %cmptmp8 = icmp sgt i32 %b2.0, 0
  br i1 %cmptmp8, label %loop, label %afterloop

afterloop:                                        ; preds = %loopend
  %arithtmp12 = add i32 %b2.0, 2
  ret i32 %arithtmp12
}

define i32 @main() {
entry:
  store i32 3, i32* @a, align 4
  %calltmp = call i32 @myFunc(i32 1, i32 2, i32 1)
  %a = load i32, i32* @a, align 4
  %arithtmp = add i32 %a, %calltmp
  ret i32 %arithtmp
}
