     1		.file	"stack.c"
     2	.globl greeting_pieces
     3		.section	.rodata
     4	.LC0:
     5		.string	"Hello"
     6	.LC1:
     7		.string	","
     8	.LC2:
     9		.string	" world"
    10	.LC3:
    11		.string	"!"
    12		.data
    13		.align 4
    14		.type	greeting_pieces, @object
    15		.size	greeting_pieces, 16
    16	greeting_pieces:
    17		.long	.LC0
    18		.long	.LC1
    19		.long	.LC2
    20		.long	.LC3
    21	.globl state
    22		.align 4
    23		.type	state, @object
    24		.size	state, 4
    25	state:
    26		.long	4
    27		.section	.rodata
    28	.LC4:
    29		.string	"%s"
    30		.text
    31	.globl main
    32		.type	main, @function
    33	main:
    34		pushl	%ebp
    35		movl	%esp, %ebp
    36		andl	$-16, %esp
    37		subl	$32, %esp
    38		movl	state, %eax
    39		subl	$1, %eax
    40		movl	%eax, state
    41		movl	state, %eax
    42		testl	%eax, %eax
    43		jns	.L2
    44		movl	$0, %eax
    45		jmp	.L3
    46	.L2:
    47		movl	state, %eax
    48		movl	%eax, 28(%esp)
    49		call	main
    50		movl	28(%esp), %eax
    51		movl	greeting_pieces(,%eax,4), %edx
    52		movl	$.LC4, %eax
    53		movl	%edx, 4(%esp)
    54		movl	%eax, (%esp)
    55		call	printf
    56		movl	$0, %eax
    57	.L3:
    58		leave
    59		ret
    60		.size	main, .-main
    61		.ident	"GCC: (Ubuntu 4.4.1-4ubuntu9) 4.4.1"
    62		.section	.note.GNU-stack,"",@progbits
