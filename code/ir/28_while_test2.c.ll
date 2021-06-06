; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @FourWhile() {
entry:
  br label %loopend30

loop:                                             ; preds = %loopend30
  %arithtmp = add i32 %a.0, 3
  br label %loopend22

loop2:                                            ; preds = %loopend22
  %arithtmp4 = add i32 %b.0, 1
  br label %loopend14

loop5:                                            ; preds = %loopend14
  %arithtmp7 = add i32 %c.0, -1
  br label %loopend

loop8:                                            ; preds = %loopend
  %arithtmp10 = add i32 %d.0, 3
  br label %loopend

loopend:                                          ; preds = %loop8, %loop5
  %d.0 = phi i32 [ %d.1, %loop5 ], [ %arithtmp10, %loop8 ]
  %cmptmp = icmp slt i32 %d.0, 20
  br i1 %cmptmp, label %loop8, label %afterloop

afterloop:                                        ; preds = %loopend
  %arithtmp13 = add i32 %d.0, -1
  br label %loopend14

loopend14:                                        ; preds = %afterloop, %loop2
  %d.1 = phi i32 [ %d.2, %loop2 ], [ %arithtmp13, %afterloop ]
  %c.0 = phi i32 [ %c.1, %loop2 ], [ %arithtmp7, %afterloop ]
  %cmptmp16 = icmp eq i32 %c.0, 7
  br i1 %cmptmp16, label %loop5, label %afterloop19

afterloop19:                                      ; preds = %loopend14
  %arithtmp21 = add i32 %c.0, 1
  br label %loopend22

loopend22:                                        ; preds = %afterloop19, %loop
  %d.2 = phi i32 [ %d.3, %loop ], [ %d.1, %afterloop19 ]
  %c.1 = phi i32 [ %c.2, %loop ], [ %arithtmp21, %afterloop19 ]
  %b.0 = phi i32 [ %b.1, %loop ], [ %arithtmp4, %afterloop19 ]
  %cmptmp24 = icmp slt i32 %b.0, 10
  br i1 %cmptmp24, label %loop2, label %afterloop27

afterloop27:                                      ; preds = %loopend22
  %arithtmp29 = add i32 %b.0, -2
  br label %loopend30

loopend30:                                        ; preds = %afterloop27, %entry
  %d.3 = phi i32 [ 10, %entry ], [ %d.2, %afterloop27 ]
  %c.2 = phi i32 [ 7, %entry ], [ %c.1, %afterloop27 ]
  %b.1 = phi i32 [ 6, %entry ], [ %arithtmp29, %afterloop27 ]
  %a.0 = phi i32 [ 5, %entry ], [ %arithtmp, %afterloop27 ]
  %cmptmp32 = icmp slt i32 %a.0, 20
  br i1 %cmptmp32, label %loop, label %afterloop35

afterloop35:                                      ; preds = %loopend30
  %arithtmp39 = add i32 %b.1, %d.3
  %arithtmp40 = add i32 %a.0, %arithtmp39
  %arithtmp42 = add i32 %arithtmp40, %c.2
  ret i32 %arithtmp42
}

define i32 @main() {
entry:
  %calltmp = call i32 @FourWhile()
  ret i32 %calltmp
}
