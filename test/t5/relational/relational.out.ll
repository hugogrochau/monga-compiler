declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = alloca i32
  %t2 = alloca i32
  %t3 = add i32 0, 3
  %t4 = add i32 0, 4
  %t5 = icmp eq i32 %t3, %t4
  %t6 = zext i1 %t5 to i32
  store i32 %t6, i32* %t1
  %t7 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t7)
  %t8 = add i32 0, 3
  %t9 = add i32 0, 2
  %t10 = icmp sge i32 %t8, %t9
  %t11 = zext i1 %t10 to i32
  store i32 %t11, i32* %t2
  %t12 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t12)
  ret void
}
