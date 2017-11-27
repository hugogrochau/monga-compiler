declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

@foo1 = global i32 0

@foo2 = global float 0.0

define void @main (i32 %t1, float %t2) {
  %t3 = alloca i32
  %t4 = alloca float
  store i32 %t1, i32* %t3
  store float %t2, float* %t4
  %t5 = add i32 0, 2
  store i32 %t5, i32* @foo1
  %t7 = getelementptr i32, i32* @foo1, i64 0
  %t6 = load i32, i32* %t7
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t6)
  %t8 = fadd float 0.0, 0x3FF3BE76C0000000
  store float %t8, float* @foo2
  %t10 = getelementptr float, float* @foo2, i64 0
  %t9 = load float, float* %t10
  %t11 = fpext float %t9 to double
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@floatTemplate, i32 0, i32 0), double %t11)
  ret void
}
