.globl	calc
 calc: 
 	pushq  %rbp
 	movq   %rsp, %rbp
subq $32, %rsp
calc.block0:
movl -4(%rbp), %eax
movl %eax, -8(%rbp)
movl $3, %eax
imull -8(%rbp), %eax
 	leave
 	ret
.globl	main
 main: 
 	pushq  %rbp
 	movq   %rsp, %rbp
subq $128, %rsp
main.block0:
movl $18, %eax
movl %eax, -4(%rbp)
movl $1, %eax
movl %eax, -8(%rbp)
movl $1, %eax
movl %eax, -12(%rbp)
movl $1, %eax
movl %eax, -16(%rbp)
movl $1, %eax
movl %eax, -20(%rbp)
movl $1, %eax
movl %eax, -24(%rbp)
movl $27, %eax
movl %eax, -28(%rbp)
movl -28(%rbp), %eax
movq %rax, %rdi
call calc
movl %eax, -32(%rbp)
call test
imull -32(%rbp), %eax
movl %eax, -36(%rbp)
movl -4(%rbp), %eax
addl -36(%rbp), %eax
movl %eax, -40(%rbp)
movl -8(%rbp), %eax
addl -40(%rbp), %eax
movl %eax, -44(%rbp)
movl -12(%rbp), %eax
addl -44(%rbp), %eax
movl %eax, -48(%rbp)
movl -16(%rbp), %eax
addl -48(%rbp), %eax
movl %eax, -52(%rbp)
movl -20(%rbp), %eax
addl -52(%rbp), %eax
movl %eax, -56(%rbp)
movl -24(%rbp), %eax
addl -56(%rbp), %eax
movl %eax, -60(%rbp)
call test
addl -60(%rbp), %eax
 	leave
 	ret
.globl	test
 test: 
 	pushq  %rbp
 	movq   %rsp, %rbp
subq $32, %rsp
test.block0:
movl $67, %eax
movl %eax, -8(%rbp)
movl -8(%rbp), %eax
movq %rax, %rdi
call getchar@PLT
movl $26, %eax
movl %eax, -4(%rbp)
movl -4(%rbp), %eax
movl %eax, -12(%rbp)
movl $3, %eax
imull -12(%rbp), %eax
 	leave
 	ret
