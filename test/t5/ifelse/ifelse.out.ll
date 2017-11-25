declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = add i32 0, 3
  %t2 = icmp ne i32 %t1, 0
  br i1 %t2, label %l1, label %l2
l1:
  %t3 = add i32 0, 1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t3)
  br label %l2
l2:
  %t4 = add i32 0, 0
  %t5 = icmp ne i32 %t4, 0
  br i1 %t5, label %l3, label %l5
l3:
  %t6 = add i32 0, 2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t6)
  br label %l4
l5:
  %t7 = add i32 0, 3
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t7)
  br label %l4
l4:
  %t8 = add i32 0, 4
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t8)
  ret void
}
