declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

@foo1 = global i32 0

@foo2 = global i8 0

@foo3 = global float 0.0

@foo4 = global i32* null

@foo5 = global i8* null

@foo6 = global float* null

define void @main (i32 %t1, float %t2) {
  %t3 = add i32 0, 2
  store i32 %t3, i32* @foo1
  %t5 = getelementptr i32, i32* @foo1, i64 0
  %t4 = load i32, i32* %t5
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t4)
  ret void
}
