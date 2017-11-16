declare i32 @printf(i8*, ...)
@intTemplate private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate private unnamed_addr constant [3 x i8] c"%p\00"

@foo1 = common global i32 0

@foo2 = common global i8 0

@foo3 = common global float 0.0

@foo4 = common global i32* null

@foo5 = common global i8* null

@foo6 = common global float* null

define null @main (i32 %t1, float %t2) {
}

define i8 @main2 (i8 %t3, i8* %t4) {
}
