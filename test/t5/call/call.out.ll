declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @foo (i32 %t1, i32 %t2) {
  %t3 = alloca i32
  %t4 = alloca i32
  store i32 %t1, i32* %t3
  store i32 %t2, i32* %t4
  %t5 = load i32, i32* %t3
  %t6 = load i32, i32* %t4
  %t7 = add i32 %t5, %t6
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t7)
  ret void
}

define i32 @bar (float %t8, float %t9) {
  %t10 = alloca float
  %t11 = alloca float
  store float %t8, float* %t10
  store float %t9, float* %t11
  %t12 = load float, float* %t10
  %t13 = load float, float* %t11
  %t14 = fcmp oeq float %t12, %t13
  %t15 = zext i1 %t14 to i32
  ret i32 %t15
}

define void @main () {
  %t16 = alloca i32
  %t18 = add i32 0, 1
  %t19 = add i32 0, 2
  call void @foo(i32 %t18, i32 %t19)
  %t21 = fadd float 0.0, 0x3FF19999A0000000
  %t22 = fadd float 0.0, 0x3FF3333340000000
  %t20 = call i32 @bar(float %t21, float %t22)
  store i32 %t20, i32* %t16
  %t23 = load i32, i32* %t16
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t23)
  ret void
}
