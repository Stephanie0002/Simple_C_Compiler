; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@g = global i32 0
@h = global i32 0
@f = global i32 0
@e = global i32 0

define i32 @EightWhile() {
entry:
  br label %loopend70

loop:                                             ; preds = %loopend70
  %arithtmp = add i32 %a.0, 3
  br label %loopend62

loop2:                                            ; preds = %loopend62
  %arithtmp4 = add i32 %b.0, 1
  br label %loopend54

loop5:                                            ; preds = %loopend54
  %arithtmp7 = add i32 %c.0, -1
  br label %loopend46

loop8:                                            ; preds = %loopend46
  %arithtmp10 = add i32 %d.0, 3
  br label %loopend38

loop11:                                           ; preds = %loopend38
  %e = load i32, i32* @e, align 4
  %arithtmp12 = add i32 %e, -1
  store i32 %arithtmp12, i32* @e, align 4
  br label %loopend30

loop13:                                           ; preds = %loopend30
  %f = load i32, i32* @f, align 4
  %arithtmp14 = add i32 %f, -2
  store i32 %arithtmp14, i32* @f, align 4
  br label %loopend22

loop15:                                           ; preds = %loopend22
  %g = load i32, i32* @g, align 4
  %arithtmp16 = add i32 %g, 10
  store i32 %arithtmp16, i32* @g, align 4
  br label %loopend

loop17:                                           ; preds = %loopend
  %h = load i32, i32* @h, align 4
  %arithtmp18 = add i32 %h, 8
  store i32 %arithtmp18, i32* @h, align 4
  br label %loopend

loopend:                                          ; preds = %loop17, %loop15
  %h19 = load i32, i32* @h, align 4
  %cmptmp = icmp slt i32 %h19, 10
  br i1 %cmptmp, label %loop17, label %afterloop

afterloop:                                        ; preds = %loopend
  %h20 = load i32, i32* @h, align 4
  %arithtmp21 = add i32 %h20, -1
  store i32 %arithtmp21, i32* @h, align 4
  br label %loopend22

loopend22:                                        ; preds = %afterloop, %loop13
  %g23 = load i32, i32* @g, align 4
  %cmptmp24 = icmp slt i32 %g23, 3
  br i1 %cmptmp24, label %loop15, label %afterloop27

afterloop27:                                      ; preds = %loopend22
  %g28 = load i32, i32* @g, align 4
  %arithtmp29 = add i32 %g28, -8
  store i32 %arithtmp29, i32* @g, align 4
  br label %loopend30

loopend30:                                        ; preds = %afterloop27, %loop11
  %f31 = load i32, i32* @f, align 4
  %cmptmp32 = icmp sgt i32 %f31, 2
  br i1 %cmptmp32, label %loop13, label %afterloop35

afterloop35:                                      ; preds = %loopend30
  %f36 = load i32, i32* @f, align 4
  %arithtmp37 = add i32 %f36, 1
  store i32 %arithtmp37, i32* @f, align 4
  br label %loopend38

loopend38:                                        ; preds = %afterloop35, %loop8
  %e39 = load i32, i32* @e, align 4
  %cmptmp40 = icmp sgt i32 %e39, 1
  br i1 %cmptmp40, label %loop11, label %afterloop43

afterloop43:                                      ; preds = %loopend38
  %e44 = load i32, i32* @e, align 4
  %arithtmp45 = add i32 %e44, 1
  store i32 %arithtmp45, i32* @e, align 4
  br label %loopend46

loopend46:                                        ; preds = %afterloop43, %loop5
  %d.0 = phi i32 [ %d.1, %loop5 ], [ %arithtmp10, %afterloop43 ]
  %cmptmp48 = icmp slt i32 %d.0, 20
  br i1 %cmptmp48, label %loop8, label %afterloop51

afterloop51:                                      ; preds = %loopend46
  %arithtmp53 = add i32 %d.0, -1
  br label %loopend54

loopend54:                                        ; preds = %afterloop51, %loop2
  %d.1 = phi i32 [ %d.2, %loop2 ], [ %arithtmp53, %afterloop51 ]
  %c.0 = phi i32 [ %c.1, %loop2 ], [ %arithtmp7, %afterloop51 ]
  %cmptmp56 = icmp eq i32 %c.0, 7
  br i1 %cmptmp56, label %loop5, label %afterloop59

afterloop59:                                      ; preds = %loopend54
  %arithtmp61 = add i32 %c.0, 1
  br label %loopend62

loopend62:                                        ; preds = %afterloop59, %loop
  %d.2 = phi i32 [ %d.3, %loop ], [ %d.1, %afterloop59 ]
  %c.1 = phi i32 [ %c.2, %loop ], [ %arithtmp61, %afterloop59 ]
  %b.0 = phi i32 [ %b.1, %loop ], [ %arithtmp4, %afterloop59 ]
  %cmptmp64 = icmp slt i32 %b.0, 10
  br i1 %cmptmp64, label %loop2, label %afterloop67

afterloop67:                                      ; preds = %loopend62
  %arithtmp69 = add i32 %b.0, -2
  br label %loopend70

loopend70:                                        ; preds = %afterloop67, %entry
  %d.3 = phi i32 [ 10, %entry ], [ %d.2, %afterloop67 ]
  %c.2 = phi i32 [ 7, %entry ], [ %c.1, %afterloop67 ]
  %b.1 = phi i32 [ 6, %entry ], [ %arithtmp69, %afterloop67 ]
  %a.0 = phi i32 [ 5, %entry ], [ %arithtmp, %afterloop67 ]
  %cmptmp72 = icmp slt i32 %a.0, 20
  br i1 %cmptmp72, label %loop, label %afterloop75

afterloop75:                                      ; preds = %loopend70
  %arithtmp79 = add i32 %b.1, %d.3
  %arithtmp80 = add i32 %a.0, %arithtmp79
  %arithtmp82 = add i32 %arithtmp80, %c.2
  %e83 = load i32, i32* @e, align 4
  %arithtmp85 = add i32 %e83, %d.3
  %g86 = load i32, i32* @g, align 4
  %arithtmp87 = sub i32 %arithtmp85, %g86
  %h88 = load i32, i32* @h, align 4
  %arithtmp89 = add i32 %arithtmp87, %h88
  %arithtmp90 = sub i32 %arithtmp82, %arithtmp89
  ret i32 %arithtmp90
}

define i32 @main() {
entry:
  store i32 1, i32* @g, align 4
  store i32 2, i32* @h, align 4
  store i32 4, i32* @e, align 4
  store i32 6, i32* @f, align 4
  %calltmp = call i32 @EightWhile()
  ret i32 %calltmp
}
