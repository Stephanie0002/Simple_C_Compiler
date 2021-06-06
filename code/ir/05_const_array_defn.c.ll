; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@a = constant [5 x i32] [i32 0, i32 1, i32 2, i32 3, i32 4]

define i32 @main() {
entry:
  ret i32 4
}
