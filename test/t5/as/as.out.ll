declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = alloca float
  %t2 = alloca i32
  %t3 = fadd float 0.0, 0x4024AE1480000000
  store float %t3, float* %t1
  %t4 = load float, float* %t1

  store float %t4, float* %t1
  %t5 = load float, float* %t1
  %t6 = fpext float %t5 to double
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@floatTemplate, i32 0, i32 0), double %t6)
  %t7 = getelementptr [2 x i8], [2 x i8]* @s1, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@stringTemplate, i32 0, i32 0), i8* %t7)
  %t8 = load float, float* %t1
  %t9 = fptosi float %t8 to i32
  store i32 %t9, i32* %t2
  %t10 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t10)
  %t11 = getelementptr [2 x i8], [2 x i8]* @s2, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@stringTemplate, i32 0, i32 0), i8* %t11)
  %t12 = load i32, i32* %t2
  %t13 = sitofp i32 %t12 to float
  store float %t13, float* %t1
  %t14 = load float, float* %t1
  %t15 = fpext float %t14 to double
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@floatTemplate, i32 0, i32 0), double %t15)
  %t16 = getelementptr [2 x i8], [2 x i8]* @s3, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@stringTemplate, i32 0, i32 0), i8* %t16)
  ret void
}

@s1 = private constant [2 x i8] c"
\00"
@s2 = private constant [2 x i8] c"
\00"
@s3 = private constant [2 x i8] c"
\00"