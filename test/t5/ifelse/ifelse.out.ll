declare i32 @printf(i8*, ...)
@intTemplate = private unnamed_addr constant [3 x i8] c"%d\00"
@floatTemplate = private unnamed_addr constant [3 x i8] c"%f\00"
@charTemplate = private unnamed_addr constant [3 x i8] c"%c\00"
@stringTemplate = private unnamed_addr constant [3 x i8] c"%s\00"
@addressTemplate = private unnamed_addr constant [3 x i8] c"%p\00"

define void @main () {
  %t1 = add i32 0, 2
  %t2 = add i32 0, 1
  %t3 = icmp sgt i32 %t1, %t2
  br i1 %t3, label %l1, label %l2
l1:
  %t4 = add i32 0, 1
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t4)
  %t5 = add i32 0, 1
  %t6 = add i32 0, 1
  %t7 = icmp eq i32 %t5, %t6
  br i1 %t7, label %l3, label %l5
l3:
  %t8 = add i32 0, 2
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t8)
  br label %l4
l5:
  %t9 = add i32 0, 3
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t9)
  br label %l4
l4:
  br label %l2
l2:
  %t10 = add i32 0, 1
  %t11 = add i32 0, 2
  %t12 = icmp sge i32 %t10, %t11
  br i1 %t12, label %l6, label %l8
l6:
  %t13 = add i32 0, 4
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t13)
  br label %l7
l8:
  %t14 = add i32 0, 5
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t14)
  br label %l7
l7:
  %t15 = add i32 0, 6
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 %t15)
  ret void
}
