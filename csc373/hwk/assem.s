	.file	"assem.c"
	.text
.globl callee
	.type	callee, @function
callee:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	imull	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	addl	%eax, %edx
	movl	-4(%ebp), %eax
	subl	%edx, %eax
	leave
	ret
	.size	callee, .-callee
.globl caller
	.type	caller, @function
caller:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$4, -4(%ebp)
	movl	$8, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	callee
	movl	%eax, -12(%ebp)
	leave
	ret
	.size	caller, .-caller
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
