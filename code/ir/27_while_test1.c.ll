; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @doubleWhile() {
entry:
  br label %loopend8

loop:                                             ; preds = %loopend8
  %arithtmp = add i32 %i.0, 30
  br label %loopend

loop2:                                            ; preds = %loopend
  %arithtmp4 = add i32 %j.0, 6
  br label %loopend

loopend:                                          ; preds = %loop2, %loop
  %j.0 = phi i32 [ %j.1, %loop ], [ %arithtmp4, %loop2 ]
  %cmptmp = icmp slt i32 %j.0, 100
  br i1 %cmptmp, label %loop2, label %afterloop

afterloop:                                        ; preds = %loopend
  %arithtmp7 = add i32 %j.0, -100
  br label %loopend8

loopend8:                                         ; preds = %afterloop, %entry
  %j.1 = phi i32 [ 7, %entry ], [ %arithtmp7, %afterloop ]
  %i.0 = phi i32 [ 5, %entry ], [ %arithtmp, %afterloop ]
  %cmptmp10 = icmp slt i32 %i.0, 100
  br i1 %cmptmp10, label %loop, label %afterloop13

afterloop13:                                      ; preds = %loopend8
  ret i32 %j.1
}

define i32 @main() {
entry:
  %calltmp = call i32 @doubleWhile()
  ret i32 %calltmp
}
