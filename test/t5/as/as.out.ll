declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = alloca i32
  %t2 = alloca float
  %t3 = add i32 0, 1
  store i32 %t3, i32* %t1
  %t4 = load i32, i32* %t1
  %t5 = sitofp i32 %t4 to float
  store float %t5, float* %t2
  %t6 = load float, float* %t2
  %t7 = fpext float %t6 to double
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@floatTemplate, i32 0, i32 0), double %t7)
  %t8 = getelementptr [2 x i8], [2 x i8]* @s1, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@stringTemplate, i32 0, i32 0), i8* %t8)
  %t9 = load float, float* %t2
  %t10 = fptosi float %t9 to i32
  store i32 %t10, i32* %t1
  %t11 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t11)
  ret void
}

@s1 = private constant [2 x i8] c"
\00"