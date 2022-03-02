.globl	main
 main: 
 	pushq  %rbp
 	movq   %rsp, %rbp
 	movl $15, %eax
 	movl %eax, -4(%rbp)
 	movl -4(%rbp), %eax
 	movl %eax, -8(%rbp)
 	movl %eax, -12(%rbp)
 	movl -12(%rbp), %eax
 	movl $12, %eax
 	movl %eax, -4(%rbp)
 	movl -4(%rbp), %eax
 	movl %eax, -12(%rbp)
 	movl $14, %eax
 	movl %eax, -8(%rbp)
 	movl %eax, -4(%rbp)
 	movl -12(%rbp), %eax
 	popq   %rbp
 	ret
