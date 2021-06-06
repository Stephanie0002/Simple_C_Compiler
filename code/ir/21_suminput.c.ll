; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@n = global i32 0
@a = global [10 x i32] zeroinitializer

define i32 @main() {
entry:
  %calltmp = call i32 @getint()
  store i32 %calltmp, i32* @n, align 4
  %cmptmp = icmp sgt i32 %calltmp, 10
  br i1 %cmptmp, label %then, label %ifcont

then:                                             ; preds = %entry
  ret i32 1

ifcont:                                           ; preds = %entry
  %s = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  store i32 0, i32* %s, align 4
  br label %loopend

loop:                                             ; preds = %loopend
  %calltmp2 = call i32 @getint()
  %i3 = load i32, i32* %i, align 4
  %0 = sext i32 %i3 to i64
  %arridx = getelementptr [10 x i32], [10 x i32]* @a, i64 0, i64 %0
  store i32 %calltmp2, i32* %arridx, align 4
  %s4 = load i32, i32* %s, align 4
  %1 = sext i32 %i3 to i64
  %arridx6 = getelementptr [10 x i32], [10 x i32]* @a, i64 0, i64 %1
  %a = load i32, i32* %arridx6, align 4
  %arithtmp = add i32 %s4, %a
  store i32 %arithtmp, i32* %s, align 4
  %i7 = load i32, i32* %i, align 4
  %arithtmp8 = add i32 %i7, 1
  store i32 %arithtmp8, i32* %i, align 4
  br label %loopend

loopend:                                          ; preds = %loop, %ifcont
  %i9 = load i32, i32* %i, align 4
  %n10 = load i32, i32* @n, align 4
  %cmptmp11 = icmp slt i32 %i9, %n10
  br i1 %cmptmp11, label %loop, label %afterloop

afterloop:                                        ; preds = %loopend
  %s13 = load i32, i32* %s, align 4
  %calltmp14 = call i32 @putint(i32 %s13)
  %calltmp16 = call i32 @putch(i32 10)
  ret i32 %s13
}

declare i32 @getint()

declare i32 @putint(i32)

declare i32 @putch(i32)
