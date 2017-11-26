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
  br i1 %t5, label %l2, label %l1
l1:
  %t6 = add i32 0, 4
  %t7 = icmp ne i32 %t6, 0
  br i1 %t7, label %l2, label %l3
l2:
  br label %l4
l3:
  br label %l4
l4:
  %t3 = phi i32 [1, %l2], [0, %l3]

  store i32 %t3, i32* %t1
  %t9 = add i32 0, 0
  %t10 = icmp ne i32 %t9, 0
  br i1 %t10, label %l6, label %l5
l5:
  %t11 = add i32 0, 1
  %t12 = icmp ne i32 %t11, 0
  br i1 %t12, label %l6, label %l7
l6:
  br label %l8
l7:
  br label %l8
l8:
  %t8 = phi i32 [1, %l6], [0, %l7]

  store i32 %t8, i32* %t2
  %t13 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t13)
  %t14 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t14)
  %t16 = add i32 0, 1
  %t17 = icmp ne i32 %t16, 0
  br i1 %t17, label %l12, label %l11
l11:
  %t18 = add i32 0, 1
  %t19 = icmp ne i32 %t18, 0
  br i1 %t19, label %l12, label %l13
l12:
  br label %l14
l13:
  br label %l14
l14:
  %t15 = phi i32 [1, %l12], [0, %l13]

  %t20 = icmp ne i32 %t15, 0
  br i1 %t20, label %l9, label %l10
l9:
  %t21 = add i32 0, 3
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t21)
  br label %l10
l10:
  %t23 = add i32 0, 0
  %t24 = icmp ne i32 %t23, 0
  br i1 %t24, label %l18, label %l17
l17:
  %t25 = add i32 0, 1
  %t26 = icmp ne i32 %t25, 0
  br i1 %t26, label %l18, label %l19
l18:
  br label %l20
l19:
  br label %l20
l20:
  %t22 = phi i32 [1, %l18], [0, %l19]

  %t27 = icmp ne i32 %t22, 0
  br i1 %t27, label %l15, label %l16
l15:
  %t28 = add i32 0, 4
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t28)
  br label %l16
l16:
  ret void
}
