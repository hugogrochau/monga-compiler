declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define i32 @main () {
  %t1 = alloca i32
  %t2 = alloca i32
  %t3 = add i32 0, 3
  store i32 %t3, i32* %t1
  %t4 = load i32, i32* %t1
  store i32 %t4, i32* %t2
  %t5 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t5)
  %t6 = load i32, i32* %t2
  ret i32 %t6
}
