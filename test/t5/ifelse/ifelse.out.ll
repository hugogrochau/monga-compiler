declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = add i32 0, 1
  %t2 = icmp ne i32 %t1, 0
  br i1 %t2, label %l1, label %l2
l1:
  %t3 = add i32 0, 1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t3)
  %t4 = add i32 0, 1
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
  br label %l2
l2:
  %t8 = add i32 0, 0
  %t9 = icmp ne i32 %t8, 0
  br i1 %t9, label %l6, label %l8
l6:
  %t10 = add i32 0, 4
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t10)
  br label %l7
l8:
  %t11 = add i32 0, 5
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t11)
  br label %l7
l7:
  %t12 = add i32 0, 6
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t12)
  ret void
}
