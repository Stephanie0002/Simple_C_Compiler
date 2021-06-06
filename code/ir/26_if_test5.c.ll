; ModuleID = 'SysY--'
source_filename = "SysY--"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

define i32 @if_if_Else() {
entry:
  ret i32 25
}

define i32 @main() {
entry:
  %calltmp = call i32 @if_if_Else()
  ret i32 %calltmp
}
