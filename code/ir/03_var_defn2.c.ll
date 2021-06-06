; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@a = global i32 0
@b = global i32 0

define i32 @main() {
entry:
  store i32 10, i32* @a, align 4
  store i32 5, i32* @b, align 4
  ret i32 28
}
