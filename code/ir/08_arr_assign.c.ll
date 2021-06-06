; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@a = global [10 x i32] zeroinitializer

define i32 @main() {
entry:
  store i32 1, i32* getelementptr inbounds ([10 x i32], [10 x i32]* @a, i64 0, i64 0), align 16
  ret i32 0
}
