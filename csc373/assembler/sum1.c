/* file: sum.c */
int accumulator = 0;

int sum(int n1, int n2) {
  int t = n1 + n2;
  accumulator += t;
  return t;
}
/*
  At the command prompt:  gcc -02 -S sum.c
     -02 ==> level 2 optimization
     -S  ==> generate assembly code file sum.s, shown below

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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  Again at the command prompt, on my Linux box:

          gcc -02 -c sum.c    ;; produces sum.o

          objdump -d sum.o    ;; produces what's shown below
                              ;; (stuff that starts with _ is an annotation)

















sum.o:     file format elf32-i386

Disassembly of section .text:

_offset _bytes                 _equivalent in assembly

00000000 <sum>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   8b 45 0c                mov    0xc(%ebp),%eax
   6:   03 45 08                add    0x8(%ebp),%eax
   9:   01 05 00 00 00 00       add    %eax,0x0
   f:   c9                      leave
  10:   c3                      ret

   Explanation: 

   The _offsets are from the start of the file.

   The _bytes are the byte sequence, broken into seven groupings, each grouping 
   is an instruction. An IA32 instruction can be from 1 to 15 byes in size.
   
   The _equivalent column is the equivalent assembly instruction to the byte code.

*/
