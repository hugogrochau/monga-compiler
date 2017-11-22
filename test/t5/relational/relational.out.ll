declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define i32 @main () {
  %t1 = alloca i32
  %t2 = add i32 0, 4
  %t3 = add i32 0, 4
  %t4 = icmp eq i32 %t2, %t3
  %t5 = zext i1 %t4 to i32
  store i32 %t5, i32* %t1
  %t6 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t6)
  %t7 = add i32 0, 1
  ret i32 %t7
}
