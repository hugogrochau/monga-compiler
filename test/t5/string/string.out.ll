declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = getelementptr [6 x i8], [6 x i8]* @s1, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@stringTemplate, i32 0, i32 0), i8* %t1)
  %t2 = getelementptr [5 x i8], [5 x i8]* @s2, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@stringTemplate, i32 0, i32 0), i8* %t2)
  ret void
}

@s1 = private constant [6 x i8] c"Test
\00"
@s2 = private constant [5 x i8] c"bar
\00"