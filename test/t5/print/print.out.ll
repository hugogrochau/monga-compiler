declare i32 @printf(i8*, ...)
@intTemplate private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate private unnamed_addr constant [3 x i8] c"%p\00"

define null @main (i32 %t1, float %t2) {
  %t3 = add i32 0, 1
  call i32 (i8*, ...) @printf(i8* @intTemplate, i32 %t3)
  %t4 = add float 0.0, 4.500000e+00
  call i32 (i8*, ...) @printf(i8* @floatTemplate, float %t4)
}
