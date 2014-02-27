int simple(int *xp, int y) {
  int t = *xp + y;
  *xp = t;
  return t;
}
/* The code above resides in the file IA32.c
   The command issued is: gcc -S IA32.c, which produces IA32.s, shown below
   Comments added after the ;;
   This example is in the book: p. 134

simple:
        pushl   %ebp               ;; save the frame pointer
        movl    %esp, %ebp         ;; create a new frame pointer
        movl    8(%ebp), %eax      ;; copy xp into eax
        movl    (%eax), %edx       ;; copy *xp into edx
        addl    12(%ebp), %edx     ;; add y
        movl    %edx, (%eax)       ;; store t at *xp
        movl    %edx, %eax         ;; copy t into eax, the return value
        movl    %ebp, %esp         ;; reset the stack pointer
        popl    %ebp               ;; reset the frame pointer
        ret                        ;; return
*/
