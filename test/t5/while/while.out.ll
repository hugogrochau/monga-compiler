declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = add i32 0, 0
  %t2 = icmp ne i32 %t1, 0
  br i1 %t2, label %l1, label %l2
l1:
  %t3 = add i32 0, 1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t3)
  %t4 = add i32 0, 0
  %t5 = icmp ne i32 %t4, 0
  br i1 %t5, label %l1, label %l2
l2:
  %t6 = add i32 0, 1
  %t7 = icmp ne i32 %t6, 0
  br i1 %t7, label %l3, label %l4
l3:
  %t8 = add i32 0, 2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t8)
  %t9 = add i32 0, 1
  %t10 = icmp ne i32 %t9, 0
  br i1 %t10, label %l3, label %l4
l4:
  ret void
}
