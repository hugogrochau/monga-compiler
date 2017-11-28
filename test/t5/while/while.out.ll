declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = alloca i32
  %t2 = add i32 0, 0
  store i32 %t2, i32* %t1
  %t3 = load i32, i32* %t1
  %t4 = add i32 0, 10
  %t5 = icmp slt i32 %t3, %t4
  br i1 %t5, label %l1, label %l2
l1:
  %t6 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t6)
  %t7 = load i32, i32* %t1
  %t8 = add i32 0, 1
  %t9 = add i32 %t7, %t8
  store i32 %t9, i32* %t1
  %t10 = load i32, i32* %t1
  %t11 = add i32 0, 10
  %t12 = icmp slt i32 %t10, %t11
  br i1 %t12, label %l1, label %l2
l2:
  %t13 = add i32 0, 0
  %t14 = icmp ne i32 %t13, 0
  br i1 %t14, label %l3, label %l4
l3:
  %t15 = add i32 0, 2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t15)
  %t16 = add i32 0, 0
  %t17 = icmp ne i32 %t16, 0
  br i1 %t17, label %l3, label %l4
l4:
  ret void
}
