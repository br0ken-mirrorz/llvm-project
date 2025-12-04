; ModuleID = 'test-inputs/ex.c'
source_filename = "test-inputs/ex.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [18 x i8] c"0 <= a && a <= 10\00", align 1
@.str.1 = private unnamed_addr constant [17 x i8] c"test-inputs/ex.c\00", align 1
@__PRETTY_FUNCTION__.foo = private unnamed_addr constant [18 x i8] c"int foo(int, int)\00", align 1
@.str.2 = private unnamed_addr constant [19 x i8] c"30 <= b && b <= 40\00", align 1

; Function Attrs: mustprogress nofree noinline norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local range(i32 -1073741824, 1073741824) i32 @ex(i32 noundef %a, i32 noundef %b) local_unnamed_addr #0 {
entry:
  %add = add nsw i32 %b, %a
  %div = sdiv i32 %add, 2
  ret i32 %div
}

; Function Attrs: nounwind uwtable
define dso_local noundef range(i32 0, 6) i32 @foo(i32 noundef %a, i32 noundef %b) local_unnamed_addr #1 {
entry:
  %or.cond = icmp ult i32 %a, 11
  br i1 %or.cond, label %if.end, label %if.else

if.else:                                          ; preds = %entry
  tail call void @__assert_fail(ptr noundef nonnull @.str, ptr noundef nonnull @.str.1, i32 noundef 9, ptr noundef nonnull @__PRETTY_FUNCTION__.foo) #3
  unreachable

if.end:                                           ; preds = %entry
  %0 = add i32 %b, -30
  %or.cond14 = icmp ult i32 %0, 11
  br i1 %or.cond14, label %if.end7, label %if.else6

if.else6:                                         ; preds = %if.end
  tail call void @__assert_fail(ptr noundef nonnull @.str.2, ptr noundef nonnull @.str.1, i32 noundef 10, ptr noundef nonnull @__PRETTY_FUNCTION__.foo) #3
  unreachable

if.end7:                                          ; preds = %if.end
  ret i32 0
}

; Function Attrs: cold noreturn nounwind
declare void @__assert_fail(ptr noundef, ptr noundef, i32 noundef, ptr noundef) local_unnamed_addr #2

attributes #0 = { mustprogress nofree noinline norecurse nosync nounwind willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { cold noreturn nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { cold noreturn nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"clang version 21.1.5 (https://github.com/br0ken-mirrorz/llvm-project.git de909fc244d543abbe73e5272ccaecc2fd9c1d92)"}
