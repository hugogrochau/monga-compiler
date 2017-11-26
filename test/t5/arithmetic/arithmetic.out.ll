declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = alloca i32
  %t2 = alloca i32
  %t3 = alloca float
  %t4 = add i32 0, 1
  %t5 = add i32 0, 4
  %t6 = add i32 %t4, %t5
  store i32 %t6, i32* %t1
  %t7 = load i32, i32* %t1
  %t8 = add i32 0, 3
  %t9 = sub i32 %t7, %t8
  store i32 %t9, i32* %t2
  %t10 = load i32, i32* %t2
  %t11 = add i32 0, 3
  %t12 = mul i32 %t10, %t11
  store i32 %t12, i32* %t2
  %t13 = load i32, i32* %t2
  %t14 = add i32 0, 2
  %t15 = sdiv i32 %t13, %t14
  store i32 %t15, i32* %t2
  %t16 = load i32, i32* %t2
  %t17 = sub nsw i32 0, %t16
  store i32 %t17, i32* %t2
  %t18 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t18)
  %t19 = fadd float 0.0, 0x3FB99999A0000000
  %t20 = fadd float 0.0, 0x4059000000000000
  %t21 = fmul float %t19, %t20
  %t22 = fadd float 0.0, 0x4014000000000000
  %t23 = fdiv float %t21, %t22
  %t24 = fadd float 0.0, 0x3FE0000000000000
  %t25 = fmul float %t23, %t24
  %t26 = fpext float %t25 to double
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@floatTemplate, i32 0, i32 0), double %t26)
  ret void
}
