.globl	main
 main: 
 	pushq  %rbp
 	movq   %rsp, %rbp
 	movl $7, %eax
 	movl %eax, -4(%rbp)
 	movl $34, %eax
 	movl %eax, -8(%rbp)
 	movl $1, %eax
 	movl %eax, -12(%rbp)
 	movl $4, %eax
 	movl %eax, -16(%rbp)
 	movl -4(%rbp), %eax
 	imull -16(%rbp), %eax
 	subl %eax, -12(%rbp)
 	movl -12(%rbp), %eax
 	movl %eax, -20(%rbp)
 	movl -8(%rbp), %eax
 	addl -20(%rbp), %eax
 	movl %eax, -24(%rbp)
 	movl $1, %eax
 	movl %eax, -28(%rbp)
 	movl $1, %eax
 	movl %eax, -32(%rbp)
 	movl $1, %eax
 	movl %eax, -36(%rbp)
 	movl $1, %eax
 	movl %eax, -40(%rbp)
 	movl $1, %eax
 	movl %eax, -44(%rbp)
 	movl $1, %eax
 	movl %eax, -48(%rbp)
 	movl $1, %eax
 	movl %eax, -52(%rbp)
 	movl $1, %eax
 	movl %eax, -56(%rbp)
 	movl $1, %eax
 	movl %eax, -60(%rbp)
 	movl $1, %eax
 	movl %eax, -64(%rbp)
 	movl $1, %eax
 	movl %eax, -68(%rbp)
 	movl $1, %eax
 	movl %eax, -72(%rbp)
 	movl $1, %eax
 	movl %eax, -76(%rbp)
 	movl $1, %eax
 	movl %eax, -80(%rbp)
 	movl $1, %eax
 	movl %eax, -84(%rbp)
 	movl $1, %eax
 	movl %eax, -88(%rbp)
 	movl $1, %eax
 	movl %eax, -92(%rbp)
 	movl $1, %eax
 	movl %eax, -96(%rbp)
 	movl $1, %eax
 	movl %eax, -100(%rbp)
 	movl $1, %eax
 	addl -100(%rbp), %eax
 	addl -96(%rbp), %eax
 	addl -92(%rbp), %eax
 	addl -88(%rbp), %eax
 	addl -84(%rbp), %eax
 	addl -80(%rbp), %eax
 	addl -76(%rbp), %eax
 	addl -72(%rbp), %eax
 	addl -68(%rbp), %eax
 	addl -64(%rbp), %eax
 	addl -60(%rbp), %eax
 	addl -56(%rbp), %eax
 	addl -52(%rbp), %eax
 	addl -48(%rbp), %eax
 	addl -44(%rbp), %eax
 	addl -40(%rbp), %eax
 	addl -36(%rbp), %eax
 	addl -32(%rbp), %eax
 	addl -28(%rbp), %eax
 	movl %eax, -24(%rbp)
 	movl -24(%rbp), %eax
 	popq   %rbp
 	ret
