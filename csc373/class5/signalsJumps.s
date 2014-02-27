	.file	"signalsJumps.c"
	.local	env
	.comm	env,156,32
	.text
.globl trace_and_die
	.type	trace_and_die, @function
trace_and_die:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	stderr, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	fputs
	movl	$1, (%esp)
	call	exit
	.size	trace_and_die, .-trace_and_die
	.section	.rodata
.LC0:
	.string	"SIGFPE is defined as %i\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$.LC0, %eax
	movl	$8, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$jumper, 4(%esp)
	movl	$8, (%esp)
	call	signal
.L4:
	call	guard
	testl	%eax, %eax
	je	.L4
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.section	.rodata
	.align 4
.LC1:
	.string	"\t Control to jumper: signal status == %d.\n"
	.text
.globl jumper
	.type	jumper, @function
jumper:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$.LC1, %eax
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$1, 4(%esp)
	movl	$env, (%esp)
	call	longjmp
	.size	jumper, .-jumper
	.section	.rodata
.LC2:
	.string	"Right after divisionInt()...."
	.text
.globl guard
	.type	guard, @function
guard:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$env, (%esp)
	call	_setjmp
	call	divisionInt
	movl	$.LC2, (%esp)
	call	puts
	movl	$0, %eax
	leave
	ret
	.size	guard, .-guard
	.section	.rodata
.LC3:
	.string	"Two integers: "
.LC4:
	.string	"%i %i"
.LC5:
	.string	"%i / %i == %i\n"
	.text
.globl divisionInt
	.type	divisionInt, @function
divisionInt:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$.LC3, %eax
	movl	%eax, (%esp)
	call	printf
	movl	$.LC4, %eax
	leal	-16(%ebp), %edx
	movl	%edx, 8(%esp)
	leal	-12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__isoc99_scanf
	movl	-12(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, %ecx
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	%ecx
	movl	%eax, %ebx
	movl	-16(%ebp), %ecx
	movl	-12(%ebp), %edx
	movl	$.LC5, %eax
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	divisionInt, .-divisionInt
	.ident	"GCC: (Ubuntu 4.4.1-4ubuntu9) 4.4.1"
	.section	.note.GNU-stack,"",@progbits
