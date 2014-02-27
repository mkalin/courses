;  hello.asm  a first program for nasm for Linux, Intel, gcc
;  (You'll need the NASM compiler if you want to run, which you
;  can get from the URL below:
;       http://sourceforge.net/project/showfiles.php?group_id=6208 
;
; assemble:	nasm -f elf -l hello.lst  hello.asm
; link:		gcc -o hiASM  hello.o
; run:	        hello 
; output is:	Hello World 

	SECTION .data                      ; data section
msg:	db "Hello, world! (from asm)",10   ; the string to print, 10 is CR
len:	equ $-msg		           ; "$" means "here"
				           ; len is a value, not an address

	SECTION .text	                   ; code section
        global main	                   ; make label available to linker 
main:			                   ; standard  gcc  entry point
	
	mov	edx,len	                   ; arg3, length of string to print
	mov	ecx,msg	                   ; arg2, pointer to string
	mov	ebx,1	                   ; arg1, where to write, screen
	mov	eax,4	                   ; write command to int 80 hex
	int	0x80	                   ; interrupt 80 hex, call kernel
	
	mov	ebx,0	                   ; exit code, 0 = normal
	mov	eax,1	                   ; exit command to kernel
	int	0x80	                   ; interrupt 80 hex, call kernel
