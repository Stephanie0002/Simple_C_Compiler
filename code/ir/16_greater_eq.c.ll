; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@a = global i32 5
@s = global [10 x i32] [i32 9, i32 8, i32 7, i32 6, i32 5, i32 4, i32 3, i32 2, i32 1, i32 0]

define i32 @main() {
entry:
  br label %loopend

loop:                                             ; preds = %loopend
  %arithtmp = add i32 %i.0, 1
  br label %loopend

loopend:                                          ; preds = %loop, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %arithtmp, %loop ]
  %0 = sext i32 %i.0 to i64
  %arridx = getelementptr [10 x i32], [10 x i32]* @s, i64 0, i64 %0
  %s = load i32, i32* %arridx, align 4
  %a = load i32, i32* @a, align 4
  %cmptmp.not = icmp slt i32 %s, %a
  br i1 %cmptmp.not, label %afterloop, label %loop

afterloop:                                        ; preds = %loopend
  ret i32 %i.0
}
