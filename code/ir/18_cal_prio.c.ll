; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@a = global i32 0
@b = global i32 0
@c = global i32 0

define i32 @main() {
entry:
  %calltmp = call i32 @getint()
  store i32 %calltmp, i32* @a, align 4
  %calltmp1 = call i32 @getint()
  store i32 %calltmp1, i32* @b, align 4
  %calltmp2 = call i32 @getint()
  store i32 %calltmp2, i32* @c, align 4
  %a = load i32, i32* @a, align 4
  %b = load i32, i32* @b, align 4
  %arithtmp = mul i32 %b, %calltmp2
  %arithtmp3 = add i32 %a, %arithtmp
  ret i32 %arithtmp3
}

declare i32 @getint()
