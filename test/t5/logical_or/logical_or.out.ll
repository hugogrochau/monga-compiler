declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = alloca i32
  %t2 = alloca i32
  %t6 = add i32 0, 0
  %t7 = icmp ne i32 %t6, 0
  br i1 %t7, label %l9, label %l10
l9:
  br label %l12
l10:
  %t8 = add i32 0, 5
  %t9 = icmp ne i32 %t8, 0
  br i1 %t9, label %l9, label %l11
l11:
  br label %l12
l12:
  %t5 = phi i1 [1, %l9], [0, %l11]
  br i1 %t5, label %l5, label %l6
l5:
  br label %l8
l6:
  %t10 = add i32 0, 0
  %t11 = icmp ne i32 %t10, 0
  br i1 %t11, label %l5, label %l7
l7:
  br label %l8
l8:
  %t4 = phi i1 [1, %l5], [0, %l7]
  br i1 %t4, label %l1, label %l2
l1:
  br label %l4
l2:
  %t12 = add i32 0, 0
  %t13 = icmp ne i32 %t12, 0
  br i1 %t13, label %l1, label %l3
l3:
  br label %l4
l4:
  %t3 = phi i1 [1, %l1], [0, %l3]
  %t14 = zext i1 %t3 to i32
  store i32 %t14, i32* %t1
  %t16 = add i32 0, 0
  %t17 = icmp ne i32 %t16, 0
  br i1 %t17, label %l13, label %l14
l13:
  br label %l16
l14:
  %t18 = add i32 0, 0
  %t19 = icmp ne i32 %t18, 0
  br i1 %t19, label %l13, label %l15
l15:
  br label %l16
l16:
  %t15 = phi i1 [1, %l13], [0, %l15]
  %t20 = zext i1 %t15 to i32
  store i32 %t20, i32* %t2
  %t21 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t21)
  %t22 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t22)
  %t24 = add i32 0, 1
  %t25 = icmp ne i32 %t24, 0
  br i1 %t25, label %l19, label %l20
l19:
  br label %l22
l20:
  %t26 = add i32 0, 0
  %t27 = icmp ne i32 %t26, 0
  br i1 %t27, label %l19, label %l21
l21:
  br label %l22
l22:
  %t23 = phi i1 [1, %l19], [0, %l21]
  br i1 %t23, label %l17, label %l18
l17:
  %t28 = add i32 0, 3
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t28)
  br label %l18
l18:
  %t30 = add i32 0, 0
  %t31 = icmp ne i32 %t30, 0
  br i1 %t31, label %l25, label %l26
l25:
  br label %l28
l26:
  %t32 = add i32 0, 1
  %t33 = add i32 0, 1
  %t34 = sub i32 %t32, %t33
  %t35 = icmp ne i32 %t34, 0
  br i1 %t35, label %l25, label %l27
l27:
  br label %l28
l28:
  %t29 = phi i1 [1, %l25], [0, %l27]
  br i1 %t29, label %l23, label %l24
l23:
  %t36 = add i32 0, 4
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t36)
  br label %l24
l24:
  ret void
}
