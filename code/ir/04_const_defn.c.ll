; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@x = common constant i32 4

define i32 @main() {
entry:
  %x = load i32, i32* @x, align 4
  ret i32 %x
}
