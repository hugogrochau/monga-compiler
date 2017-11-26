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
  %t4 = add i32 0, 3
  store i32 %t4, i32* %t1
  %t5 = load i32, i32* %t1
  store i32 %t5, i32* %t2
  %t6 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t6)
  %t7 = fadd float 0.0, 0x400B333340000000
  store float %t7, float* %t3
  %t8 = load float, float* %t3
  %t9 = fadd float 0.0, 0x4000000000000000
  %t10 = fmul float %t8, %t9
  store float %t10, float* %t3
  %t11 = load float, float* %t3
  %t12 = fpext float %t11 to double
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@floatTemplate, i32 0, i32 0), double %t12)
  ret void
}
