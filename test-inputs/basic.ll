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

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local noundef i32 @_Z7averageii(i32 noundef %a, i32 noundef %b) #0 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  store i32 %b, ptr %b.addr, align 4
  %0 = load i32, ptr %a.addr, align 4
  %1 = load i32, ptr %b.addr, align 4
  %add = add nsw i32 %0, %1
  %div = sdiv i32 %add, 2
  ret i32 %div
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @_Z3barii(i32 noundef %a, i32 noundef %b) #1 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  store i32 %b, ptr %b.addr, align 4
  %0 = load i32, ptr %a.addr, align 4
  %cmp = icmp sle i32 0, %0
  br i1 %cmp, label %land.rhs, label %land.end

land.rhs:                                         ; preds = %entry
  %1 = load i32, ptr %a.addr, align 4
  %cmp1 = icmp sle i32 %1, 10
  br label %land.end

land.end:                                         ; preds = %land.rhs, %entry
  %2 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ]
  br i1 %2, label %cond.true, label %cond.false

cond.true:                                        ; preds = %land.end
  br label %cond.end

cond.false:                                       ; preds = %land.end
  call void @__assert_fail(ptr noundef @.str, ptr noundef @.str.1, i32 noundef 7, ptr noundef @__PRETTY_FUNCTION__._Z3barii) #4
  unreachable

3:                                                ; No predecessors!
  br label %cond.end

cond.end:                                         ; preds = %3, %cond.true
  %4 = load i32, ptr %b.addr, align 4
  %cmp2 = icmp sle i32 30, %4
  br i1 %cmp2, label %land.rhs3, label %land.end5

land.rhs3:                                        ; preds = %cond.end
  %5 = load i32, ptr %b.addr, align 4
  %cmp4 = icmp sle i32 %5, 40
  br label %land.end5

land.end5:                                        ; preds = %land.rhs3, %cond.end
  %6 = phi i1 [ false, %cond.end ], [ %cmp4, %land.rhs3 ]
  br i1 %6, label %cond.true6, label %cond.false7

cond.true6:                                       ; preds = %land.end5
  br label %cond.end8

cond.false7:                                      ; preds = %land.end5
  call void @__assert_fail(ptr noundef @.str.2, ptr noundef @.str.1, i32 noundef 8, ptr noundef @__PRETTY_FUNCTION__._Z3barii) #4
  unreachable

7:                                                ; No predecessors!
  br label %cond.end8

cond.end8:                                        ; preds = %7, %cond.true6
  %8 = load i32, ptr %a.addr, align 4
  %9 = load i32, ptr %b.addr, align 4
  %call = call noundef i32 @_Z7averageii(i32 noundef %8, i32 noundef %9)
  store i32 %call, ptr %x, align 4
  %10 = load i32, ptr %x, align 4
  %11 = load i32, ptr %a.addr, align 4
  %cmp9 = icmp slt i32 %10, %11
  br i1 %cmp9, label %if.then, label %if.end

if.then:                                          ; preds = %cond.end8
  %call10 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cout, ptr noundef @.str.3)
  br label %if.end

if.end:                                           ; preds = %if.then, %cond.end8
  %12 = load i32, ptr %x, align 4
  %13 = load i32, ptr %b.addr, align 4
  %cmp11 = icmp sgt i32 %12, %13
  br i1 %cmp11, label %if.then12, label %if.end14

if.then12:                                        ; preds = %if.end
  %call13 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cout, ptr noundef @.str.4)
  br label %if.end14

if.end14:                                         ; preds = %if.then12, %if.end
  %call15 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cout, ptr noundef @.str.5)
  ret void
}

; Function Attrs: cold noreturn nounwind
declare void @__assert_fail(ptr noundef, ptr noundef, i32 noundef, ptr noundef) #2

declare noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8), ptr noundef) #3

attributes #0 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { cold noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { cold noreturn nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 21.1.1 (https://github.com/llvm/llvm-project.git 5a86dc996c26299de63effc927075dcbfb924167)"}
