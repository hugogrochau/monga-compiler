declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = alloca i32
  %t2 = alloca float
  %t3 = add i32 0, 500
  %t4 = add i32 0, 500
  %t5 = icmp ne i32 %t4, 0
  %t6 = xor i1 %t5, true
  %t7 = zext i1 %t6 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t7)
  %t8 = add i32 0, 0
  %t9 = add i32 0, 0
  %t10 = icmp ne i32 %t9, 0
  %t11 = xor i1 %t10, true
  %t12 = zext i1 %t11 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t12)
  %t13 = add i32 0, 2
  %t14 = add i32 0, 2
  %t15 = icmp ne i32 %t14, 0
  %t16 = xor i1 %t15, true
  %t17 = zext i1 %t16 to i32
  store i32 %t17, i32* %t1
  %t18 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t18)
  %t19 = add i32 0, 3
  %t20 = sub nsw i32 0, %t19
  store i32 %t20, i32* %t1
  %t21 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t21)
  %t22 = add i32 0, 0
  %t23 = icmp ne i32 %t22, 0
  %t24 = xor i1 %t23, true
  %t25 = add i32 0, 0
  %t26 = add i32 0, 0
  %t27 = icmp ne i32 %t26, 0
  %t28 = xor i1 %t27, true
  %t29 = zext i1 %t28 to i32
  %t30 = icmp ne i32 %t29, 0
  br i1 %t30, label %l1, label %l2
l1:
  %t31 = add i32 0, 4
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t31)
  br label %l2
l2:
  %t32 = fadd float 0.0, 0x4008CCCCC0000000
  %t33 = fadd float 0.0, 0x4008CCCCC0000000
  %t34 = fcmp one float %t33, 0.0
  %t35 = xor i1 %t34, true
  %t36 = zext i1 %t35 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t36)
  %t37 = fadd float 0.0, 0x0000000000000000
  %t38 = fadd float 0.0, 0x0000000000000000
  %t39 = fcmp one float %t38, 0.0
  %t40 = xor i1 %t39, true
  %t41 = zext i1 %t40 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t41)
  %t42 = fadd float 0.0, 0x4000000000000000
  %t43 = fadd float 0.0, 0x4000000000000000
  %t44 = fcmp one float %t43, 0.0
  %t45 = xor i1 %t44, true
  %t46 = zext i1 %t45 to i32
  store i32 %t46, i32* %t1
  %t47 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t47)
  %t48 = fadd float 0.0, 0x4008000000000000
  %t49 = fsub float 0.0, %t48
  store float %t49, float* %t2
  %t50 = fadd float 0.0, 0x0000000000000000
  %t51 = fcmp one float %t50, 0.0
  %t52 = xor i1 %t51, true
  %t53 = fadd float 0.0, 0x0000000000000000
  %t54 = fadd float 0.0, 0x0000000000000000
  %t55 = fcmp one float %t54, 0.0
  %t56 = xor i1 %t55, true
  %t57 = zext i1 %t56 to i32
  %t58 = icmp ne i32 %t57, 0
  br i1 %t58, label %l3, label %l4
l3:
  %t59 = fadd float 0.0, 0x4010000000000000
  %t60 = fpext float %t59 to double
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@floatTemplate, i32 0, i32 0), double %t60)
  br label %l4
l4:
  ret void
}
