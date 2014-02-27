#include <stdio.h>

void very_bad(char* buffer) {
  int c;  /* NB: int rather than char because the system I/O function
	     getchar() returns the int value 0xffffffff on end-of-file */
  char* dest = buffer;
  
  /* read until newline or end-of-file (Control-Z for the standard input) */
  while ((c = getchar()) != '\n' && c != EOF)
    *dest++ = c; /* store next character in buffer and move pointer */
  
  printf("%s\n", buffer);
}

int main() {
  char buff[4];  /* big trouble waiting to happen */
  very_bad(buff);
  
  return 0;
}
/* output from sample runs:

    $ ./stack_corrupt
    a b 
    a b

    $ ./stack_corrupt
    a b c d e f g h i j k l m n o p
    a b c d e ...
    Segmentation fault

   The problem:

                +=======================+ <--- main's call frame
                |        ...            |
                |-----------------------| 
                | return address        | <--- saved %eip for main
                +=======================+ <--- very_bad's call frame
                | saved stack pointer   | <--- saved %ebp for main
                |-----------------------|
                | [3] | [2] | [1] | [0] | <--- buffer in very_bad (LE)
                |-----------------------|
                |        ...            |
                +=======================|

   At the assembler level (assembler for main):

     main:
            pushl %ebp          ;; save main's call frame pointer
            movl %esp, %ebp     ;; create call frame for very_bad
            subl $20, %esp      ;; grow the call frame for very_bad
            pushl %ebx          ;; save %ebx on the stack
            addl $-12, %esp     ;; grow the call frame some more
            leal -4(%ebp), %ebx ;; compute buf as %ebp - 4
            pushl %ebx          ;; save new %ebx == buf on the stack
            call very_bad       ;; transfer control to very_bad
*/
