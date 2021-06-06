; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @deepWhileBr(i32 %a, i32 %b) {
entry:
  %arithtmp = add i32 %a, %b
  br label %loopend

loop:                                             ; preds = %loopend
  %d = alloca i32, align 4
  store i32 42, i32* %d, align 4
  %d7 = load i32, i32* %d, align 4
  %arithtmp8 = add i32 %c.3, %d7
  %cmptmp10 = icmp sgt i32 %arithtmp8, 99
  br i1 %cmptmp10, label %then13, label %ifcont22

then13:                                           ; preds = %loop
  %e = alloca i32, align 4
  %d14 = load i32, i32* %d, align 4
  %arithtmp15 = shl i32 %d14, 1
  store i32 %arithtmp15, i32* %e, align 4
  %e17 = load i32, i32* %e, align 4
  %arithtmp18 = shl i32 %e17, 1
  br label %ifcont22

ifcont22:                                         ; preds = %then13, %loop
  %c.1 = phi i32 [ %arithtmp18, %then13 ], [ %arithtmp8, %loop ]
  br label %loopend

loopend:                                          ; preds = %ifcont22, %entry
  %c.3 = phi i32 [ %arithtmp, %entry ], [ %c.1, %ifcont22 ]
  %cmptmp24 = icmp slt i32 %c.3, 75
  br i1 %cmptmp24, label %loop, label %afterloop

afterloop:                                        ; preds = %loopend
  ret i32 %c.3
}

define i32 @main() {
entry:
  %calltmp = call i32 @deepWhileBr(i32 2, i32 2)
  ret i32 %calltmp
}
