declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define i32 @main () {
  %t1 = alloca i32
  %t2 = alloca i32
  %t3 = add i32 0, 1
  %t4 = add i32 0, 4
  %t5 = add i32 %t3, %t4
  store i32 %t5, i32* %t1
  %t6 = load i32, i32* %t1
  %t7 = add i32 0, 3
  %t8 = sub i32 %t6, %t7
  store i32 %t8, i32* %t2
  %t9 = load i32, i32* %t2
  %t10 = add i32 0, 3
  %t11 = mul i32 %t9, %t10
  store i32 %t11, i32* %t2
  %t12 = load i32, i32* %t2
  %t13 = add i32 0, 2
  %t14 = sdiv i32 %t12, %t13
  store i32 %t14, i32* %t2
  %t15 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t15)
  %t16 = add i32 0, 0
  ret i32 %t16
}
