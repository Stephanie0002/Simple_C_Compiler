; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@a = global i32 0
@b = global i32 0

define i32 @main() {
entry:
  %calltmp = call i32 @getint()
  store i32 %calltmp, i32* @a, align 4
  %calltmp1 = call i32 @getint()
  store i32 %calltmp1, i32* @b, align 4
  %a = load i32, i32* @a, align 4
  %short = icmp ne i32 %a, 0
  %b = load i32, i32* @b, align 4
  %i32toi1_ = icmp ne i32 %b, 0
  %logictmp = select i1 %short, i1 %i32toi1_, i1 %short
  %spec.select = select i1 %logictmp, i32 1, i32 0
  ret i32 %spec.select
}

declare i32 @getint()
