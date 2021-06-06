; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @main() {
entry:
  %calltmp = call i32 @putint(i32 2)
  ret i32 0
}

declare i32 @putint(i32)
