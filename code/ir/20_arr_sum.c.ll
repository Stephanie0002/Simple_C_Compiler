; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@a = global [5 x i32] zeroinitializer

define i32 @main() {
entry:
  %calltmp = call i32 @getint()
  store i32 %calltmp, i32* getelementptr inbounds ([5 x i32], [5 x i32]* @a, i64 0, i64 0), align 16
  %calltmp1 = call i32 @getint()
  store i32 %calltmp1, i32* getelementptr inbounds ([5 x i32], [5 x i32]* @a, i64 0, i64 1), align 4
  %calltmp2 = call i32 @getint()
  store i32 %calltmp2, i32* getelementptr inbounds ([5 x i32], [5 x i32]* @a, i64 0, i64 2), align 8
  %calltmp3 = call i32 @getint()
  store i32 %calltmp3, i32* getelementptr inbounds ([5 x i32], [5 x i32]* @a, i64 0, i64 3), align 4
  %calltmp4 = call i32 @getint()
  store i32 %calltmp4, i32* getelementptr inbounds ([5 x i32], [5 x i32]* @a, i64 0, i64 4), align 16
  br label %loopend

loop:                                             ; preds = %loopend
  %0 = sext i32 %cnt.0 to i64
  %arridx = getelementptr [5 x i32], [5 x i32]* @a, i64 0, i64 %0
  %a = load i32, i32* %arridx, align 4
  %arithtmp = add i32 %sum.0, %a
  %arithtmp8 = add i32 %cnt.0, -1
  br label %loopend

loopend:                                          ; preds = %loop, %entry
  %sum.0 = phi i32 [ 0, %entry ], [ %arithtmp, %loop ]
  %cnt.0 = phi i32 [ 4, %entry ], [ %arithtmp8, %loop ]
  %cmptmp = icmp sgt i32 %cnt.0, 1
  br i1 %cmptmp, label %loop, label %afterloop

afterloop:                                        ; preds = %loopend
  ret i32 %sum.0
}

declare i32 @getint()
