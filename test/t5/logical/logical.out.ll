declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = alloca i32
  %t2 = alloca i32
  %t4 = add i32 0, 3
  %t5 = icmp ne i32 %t4, 0
  br i1 %t5, label %l2, label %l3
l1:
  br label %l4
l2:
  %t6 = add i32 0, 4
  %t7 = icmp ne i32 %t6, 0
  br i1 %t7, label %l1, label %l3
l3:
  br label %l4
l4:
  %t3 = phi i1 [1, %l1], [0, %l3]
  %t8 = zext i1 %t3 to i32
  store i32 %t8, i32* %t1
  %t10 = add i32 0, 0
  %t11 = icmp ne i32 %t10, 0
  br i1 %t11, label %l6, label %l7
l5:
  br label %l8
l6:
  %t12 = add i32 0, 1
  %t13 = icmp ne i32 %t12, 0
  br i1 %t13, label %l5, label %l7
l7:
  br label %l8
l8:
  %t9 = phi i1 [1, %l5], [0, %l7]
  %t14 = zext i1 %t9 to i32
  store i32 %t14, i32* %t2
  %t15 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t15)
  %t16 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t16)
  %t18 = add i32 0, 1
  %t19 = icmp ne i32 %t18, 0
  br i1 %t19, label %l12, label %l13
l11:
  br label %l14
l12:
  %t20 = add i32 0, 1
  %t21 = icmp ne i32 %t20, 0
  br i1 %t21, label %l11, label %l13
l13:
  br label %l14
l14:
  %t17 = phi i1 [1, %l11], [0, %l13]
  br i1 %t17, label %l9, label %l10
l9:
  %t22 = add i32 0, 3
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t22)
  br label %l10
l10:
  %t24 = add i32 0, 0
  %t25 = icmp ne i32 %t24, 0
  br i1 %t25, label %l18, label %l19
l17:
  br label %l20
l18:
  %t26 = add i32 0, 1
  %t27 = icmp ne i32 %t26, 0
  br i1 %t27, label %l17, label %l19
l19:
  br label %l20
l20:
  %t23 = phi i1 [1, %l17], [0, %l19]
  br i1 %t23, label %l15, label %l16
l15:
  %t28 = add i32 0, 4
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t28)
  br label %l16
l16:
  ret void
}
