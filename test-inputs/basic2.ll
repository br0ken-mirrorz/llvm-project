; ModuleID = 'test-inputs/basic.cpp'
source_filename = "test-inputs/basic.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

module asm ".globl _ZSt21ios_base_library_initv"

%"class.std::basic_ostream" = type { ptr, %"class.std::basic_ios" }
%"class.std::basic_ios" = type { %"class.std::ios_base", ptr, i8, i8, ptr, ptr, ptr, ptr }
%"class.std::ios_base" = type { ptr, i64, i64, i32, i32, i32, ptr, %"struct.std::ios_base::_Words", [8 x %"struct.std::ios_base::_Words"], i32, ptr, %"class.std::locale" }
%"struct.std::ios_base::_Words" = type { ptr, i64 }
%"class.std::locale" = type { ptr }

@.str = private unnamed_addr constant [18 x i8] c"0 <= a && a <= 10\00", align 1
@.str.1 = private unnamed_addr constant [22 x i8] c"test-inputs/basic.cpp\00", align 1
@__PRETTY_FUNCTION__._Z3barii = private unnamed_addr constant [19 x i8] c"void bar(int, int)\00", align 1
@.str.2 = private unnamed_addr constant [19 x i8] c"30 <= b && b <= 40\00", align 1
@_ZSt4cout = external global %"class.std::basic_ostream", align 8
@.str.3 = private unnamed_addr constant [14 x i8] c"less than a!\0A\00", align 1
@.str.4 = private unnamed_addr constant [14 x i8] c"more than b!\0A\00", align 1
@.str.5 = private unnamed_addr constant [10 x i8] c"neither!\0A\00", align 1

; Function Attrs: mustprogress uwtable
define dso_local void @_Z3barii(i32 noundef %a, i32 noundef %b) local_unnamed_addr #0 {
entry:
  %0 = icmp ult i32 %a, 11
  br i1 %0, label %cond.end, label %cond.false

cond.false:                                       ; preds = %entry
  tail call void @__assert_fail(ptr noundef nonnull @.str, ptr noundef nonnull @.str.1, i32 noundef 6, ptr noundef nonnull @__PRETTY_FUNCTION__._Z3barii) #4
  unreachable

cond.end:                                         ; preds = %entry
  %1 = add i32 %b, -30
  %2 = icmp ult i32 %1, 11
  br i1 %2, label %cond.end8, label %cond.false7

cond.false7:                                      ; preds = %cond.end
  tail call void @__assert_fail(ptr noundef nonnull @.str.2, ptr noundef nonnull @.str.1, i32 noundef 7, ptr noundef nonnull @__PRETTY_FUNCTION__._Z3barii) #4
  unreachable

cond.end8:                                        ; preds = %cond.end
  %call = tail call noundef i32 @_Z7averageii(i32 noundef %a, i32 noundef %b)
  %cmp9 = icmp slt i32 %call, %a
  br i1 %cmp9, label %if.then, label %if.end

if.then:                                          ; preds = %cond.end8
  %call1.i = tail call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cout, ptr noundef nonnull @.str.3, i64 noundef 13)
  br label %if.end

if.end:                                           ; preds = %if.then, %cond.end8
  %cmp11 = icmp sgt i32 %call, %b
  br i1 %cmp11, label %if.then12, label %if.end14

if.then12:                                        ; preds = %if.end
  %call1.i24 = tail call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cout, ptr noundef nonnull @.str.4, i64 noundef 13)
  br label %if.end14

if.end14:                                         ; preds = %if.then12, %if.end
  %call1.i26 = tail call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cout, ptr noundef nonnull @.str.5, i64 noundef 9)
  ret void
}

; Function Attrs: cold noreturn nounwind
declare void @__assert_fail(ptr noundef, ptr noundef, i32 noundef, ptr noundef) local_unnamed_addr #1

; Function Attrs: mustprogress nofree noinline norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef range(i32 -1073741824, 1073741824) i32 @_Z7averageii(i32 noundef %a, i32 noundef %b) local_unnamed_addr #2 {
entry:
  %add = add nsw i32 %b, %a
  %div = sdiv i32 %add, 2
  ret i32 %div
}

declare noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8), ptr noundef, i64 noundef) local_unnamed_addr #3

attributes #0 = { mustprogress uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { cold noreturn nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nofree noinline norecurse nosync nounwind willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { cold noreturn nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"clang version 21.1.5 (https://github.com/br0ken-mirrorz/llvm-project.git 04102d998d0e4019c26654cf0b545a0af19819c7)"}
