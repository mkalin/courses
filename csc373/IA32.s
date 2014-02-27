	.file	"IA32.c"
	.text
.globl simple
	.type	simple, @function
simple:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	addl	(%edx), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	movl	%eax, (%edx)
	movl	-4(%ebp), %eax
	leave
	ret
	.size	simple, .-simple
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.4.6 20060404 (Red Hat 3.4.6-9)"
