declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = alloca i32
  %t2 = alloca i32
  %t5 = add i32 0, 3
  %t6 = icmp ne i32 %t5, 0
  br i1 %t6, label %l6, label %l7
l5:
  br label %l8
l6:
  %t7 = add i32 0, 4
  %t8 = icmp ne i32 %t7, 0
  br i1 %t8, label %l5, label %l7
l7:
  br label %l8
l8:
  %t4 = phi i1 [1, %l5], [0, %l7]
  br i1 %t4, label %l2, label %l3
l1:
  br label %l4
l2:
  %t9 = add i32 0, 3
  %t10 = add i32 0, 2
  %t11 = mul i32 %t9, %t10
  %t12 = icmp ne i32 %t11, 0
  br i1 %t12, label %l1, label %l3
l3:
  br label %l4
l4:
  %t3 = phi i1 [1, %l1], [0, %l3]
  %t13 = zext i1 %t3 to i32
  store i32 %t13, i32* %t1
  %t17 = add i32 0, 2
  %t18 = icmp ne i32 %t17, 0
  br i1 %t18, label %l18, label %l19
l17:
  br label %l20
l18:
  %t19 = add i32 0, 1
  %t20 = icmp ne i32 %t19, 0
  br i1 %t20, label %l17, label %l19
l19:
  br label %l20
l20:
  %t16 = phi i1 [1, %l17], [0, %l19]
  br i1 %t16, label %l14, label %l15
l13:
  br label %l16
l14:
  %t21 = add i32 0, 0
  %t22 = icmp ne i32 %t21, 0
  br i1 %t22, label %l13, label %l15
l15:
  br label %l16
l16:
  %t15 = phi i1 [1, %l13], [0, %l15]
  br i1 %t15, label %l10, label %l11
l9:
  br label %l12
l10:
  %t23 = add i32 0, 1
  %t24 = icmp ne i32 %t23, 0
  br i1 %t24, label %l9, label %l11
l11:
  br label %l12
l12:
  %t14 = phi i1 [1, %l9], [0, %l11]
  %t25 = zext i1 %t14 to i32
  store i32 %t25, i32* %t2
  %t26 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t26)
  %t27 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t27)
  %t29 = add i32 0, 1
  %t30 = icmp ne i32 %t29, 0
  br i1 %t30, label %l24, label %l25
l23:
  br label %l26
l24:
  %t31 = add i32 0, 1
  %t32 = icmp ne i32 %t31, 0
  br i1 %t32, label %l23, label %l25
l25:
  br label %l26
l26:
  %t28 = phi i1 [1, %l23], [0, %l25]
  br i1 %t28, label %l21, label %l22
l21:
  %t33 = add i32 0, 3
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t33)
  br label %l22
l22:
  %t35 = add i32 0, 0
  %t36 = icmp ne i32 %t35, 0
  br i1 %t36, label %l30, label %l31
l29:
  br label %l32
l30:
  %t37 = add i32 0, 1
  %t38 = icmp ne i32 %t37, 0
  br i1 %t38, label %l29, label %l31
l31:
  br label %l32
l32:
  %t34 = phi i1 [1, %l29], [0, %l31]
  br i1 %t34, label %l27, label %l28
l27:
  %t39 = add i32 0, 4
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t39)
  br label %l28
l28:
  ret void
}
