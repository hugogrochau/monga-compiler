declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = alloca i32
  %t2 = alloca i32
  %t3 = add i32 0, 3
  %t4 = add i32 0, 4
  %t5 = icmp eq i32 %t3, %t4
  %t6 = zext i1 %t5 to i32
  store i32 %t6, i32* %t1
  %t7 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t7)
  %t8 = add i32 0, 3
  %t9 = add i32 0, 3
  %t10 = icmp eq i32 %t8, %t9
  %t11 = zext i1 %t10 to i32
  store i32 %t11, i32* %t1
  %t12 = load i32, i32* %t1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t12)
  %t13 = add i32 0, 1
  %t14 = add i32 0, 1
  %t15 = icmp eq i32 %t13, %t14
  %t16 = zext i1 %t15 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t16)
  %t17 = add i32 0, 1
  %t18 = add i32 0, 0
  %t19 = icmp eq i32 %t17, %t18
  %t20 = zext i1 %t19 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t20)
  %t21 = add i32 0, 1
  %t22 = add i32 0, 0
  %t23 = icmp ne i32 %t21, %t22
  %t24 = zext i1 %t23 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t24)
  %t25 = add i32 0, 1
  %t26 = add i32 0, 1
  %t27 = icmp ne i32 %t25, %t26
  %t28 = zext i1 %t27 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t28)
  %t29 = add i32 0, 3
  %t30 = add i32 0, 3
  %t31 = icmp sle i32 %t29, %t30
  %t32 = zext i1 %t31 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t32)
  %t33 = add i32 0, 3
  %t34 = add i32 0, 2
  %t35 = icmp sle i32 %t33, %t34
  %t36 = zext i1 %t35 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t36)
  %t37 = add i32 0, 3
  %t38 = add i32 0, 3
  %t39 = icmp sge i32 %t37, %t38
  %t40 = zext i1 %t39 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t40)
  %t41 = add i32 0, 2
  %t42 = add i32 0, 3
  %t43 = icmp sge i32 %t41, %t42
  %t44 = zext i1 %t43 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t44)
  %t45 = add i32 0, 2
  %t46 = add i32 0, 3
  %t47 = icmp slt i32 %t45, %t46
  %t48 = zext i1 %t47 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t48)
  %t49 = add i32 0, 4
  %t50 = add i32 0, 3
  %t51 = icmp slt i32 %t49, %t50
  %t52 = zext i1 %t51 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t52)
  %t53 = add i32 0, 2
  %t54 = add i32 0, 1
  %t55 = icmp sgt i32 %t53, %t54
  %t56 = zext i1 %t55 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t56)
  %t57 = add i32 0, 2
  %t58 = add i32 0, 3
  %t59 = icmp sgt i32 %t57, %t58
  %t60 = zext i1 %t59 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t60)
  %t61 = fadd float 0.0, 0x4008CCCCC0000000
  %t62 = fadd float 0.0, 0x4011333340000000
  %t63 = fcmp oeq float %t61, %t62
  %t64 = zext i1 %t63 to i32
  store i32 %t64, i32* %t2
  %t65 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t65)
  %t66 = fadd float 0.0, 0x4008CCCCC0000000
  %t67 = fadd float 0.0, 0x4008CCCCC0000000
  %t68 = fcmp oeq float %t66, %t67
  %t69 = zext i1 %t68 to i32
  store i32 %t69, i32* %t2
  %t70 = load i32, i32* %t2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t70)
  %t71 = add i32 0, 1
  %t72 = add i32 0, 1
  %t73 = icmp eq i32 %t71, %t72
  %t74 = zext i1 %t73 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t74)
  %t75 = add i32 0, 1
  %t76 = add i32 0, 0
  %t77 = icmp eq i32 %t75, %t76
  %t78 = zext i1 %t77 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t78)
  %t79 = add i32 0, 1
  %t80 = add i32 0, 0
  %t81 = icmp ne i32 %t79, %t80
  %t82 = zext i1 %t81 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t82)
  %t83 = add i32 0, 1
  %t84 = add i32 0, 1
  %t85 = icmp ne i32 %t83, %t84
  %t86 = zext i1 %t85 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t86)
  %t87 = add i32 0, 3
  %t88 = add i32 0, 3
  %t89 = icmp sle i32 %t87, %t88
  %t90 = zext i1 %t89 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t90)
  %t91 = add i32 0, 3
  %t92 = add i32 0, 2
  %t93 = icmp sle i32 %t91, %t92
  %t94 = zext i1 %t93 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t94)
  %t95 = add i32 0, 3
  %t96 = add i32 0, 3
  %t97 = icmp sge i32 %t95, %t96
  %t98 = zext i1 %t97 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t98)
  %t99 = add i32 0, 2
  %t100 = add i32 0, 3
  %t101 = icmp sge i32 %t99, %t100
  %t102 = zext i1 %t101 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t102)
  %t103 = add i32 0, 2
  %t104 = add i32 0, 3
  %t105 = icmp slt i32 %t103, %t104
  %t106 = zext i1 %t105 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t106)
  %t107 = add i32 0, 4
  %t108 = add i32 0, 3
  %t109 = icmp slt i32 %t107, %t108
  %t110 = zext i1 %t109 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t110)
  %t111 = add i32 0, 2
  %t112 = add i32 0, 1
  %t113 = icmp sgt i32 %t111, %t112
  %t114 = zext i1 %t113 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t114)
  %t115 = add i32 0, 2
  %t116 = add i32 0, 3
  %t117 = icmp sgt i32 %t115, %t116
  %t118 = zext i1 %t117 to i32
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t118)
  ret void
}
