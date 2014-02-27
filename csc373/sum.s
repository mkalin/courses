	.file	"sum.c"
.globl accumulator
	.bss
	.align 4
	.type	accumulator, @object
	.size	accumulator, 4
accumulator:
	.zero	4
	.text
	.p2align 2,,3
.globl sum
	.type	sum, @function
sum:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	addl	%eax, accumulator
	leave
	ret
	.size	sum, .-sum
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.4.5 20051201 (Red Hat 3.4.5-2)"
