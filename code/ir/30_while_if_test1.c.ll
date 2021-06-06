; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @whileIf() {
entry:
  br label %loopend

loop:                                             ; preds = %loopend
  switch i32 %a.0, label %else7 [
    i32 5, label %ifcont9
    i32 10, label %ifcont
  ]

else7:                                            ; preds = %loop
  %arithtmp = shl i32 %a.0, 1
  br label %ifcont

ifcont:                                           ; preds = %loop, %else7
  %b.0 = phi i32 [ %arithtmp, %else7 ], [ 42, %loop ]
  br label %ifcont9

ifcont9:                                          ; preds = %loop, %ifcont
  %b.1 = phi i32 [ %b.0, %ifcont ], [ 25, %loop ]
  %arithtmp11 = add i32 %a.0, 1
  br label %loopend

loopend:                                          ; preds = %ifcont9, %entry
  %b.2 = phi i32 [ 0, %entry ], [ %b.1, %ifcont9 ]
  %a.0 = phi i32 [ 0, %entry ], [ %arithtmp11, %ifcont9 ]
  %cmptmp13 = icmp slt i32 %a.0, 100
  br i1 %cmptmp13, label %loop, label %afterloop

afterloop:                                        ; preds = %loopend
  ret i32 %b.2
}

define i32 @main() {
entry:
  %calltmp = call i32 @whileIf()
  ret i32 %calltmp
}
