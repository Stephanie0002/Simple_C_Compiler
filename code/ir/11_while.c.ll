; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@a = global i32 0
@b = global i32 0

define i32 @main() {
entry:
  store i32 0, i32* @b, align 4
  br label %loopend

loop:                                             ; preds = %loopend
  %b = load i32, i32* @b, align 4
  %a = load i32, i32* @a, align 4
  %arithtmp = add i32 %b, %a
  store i32 %arithtmp, i32* @b, align 4
  %arithtmp2 = add i32 %a, -1
  br label %loopend

loopend:                                          ; preds = %loop, %entry
  %storemerge = phi i32 [ 3, %entry ], [ %arithtmp2, %loop ]
  store i32 %storemerge, i32* @a, align 4
  %cmptmp = icmp sgt i32 %storemerge, 0
  br i1 %cmptmp, label %loop, label %afterloop

afterloop:                                        ; preds = %loopend
  %b4 = load i32, i32* @b, align 4
  ret i32 %b4
}
