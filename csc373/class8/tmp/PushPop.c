#include <stdio.h>

int push_test() {
  int ret_val;
  /* movl %esp, %eax    ;; save stack pointer
     pushl %esp         ;; push stack pointer onto stack
     popl %edx          ;; pop the stack into %edx
     subl %edx, %eax    ;; subtract the two values
     movl %eax, ret_val ;; set up the return value
  */
  asm("movl %%esp, %%eax; pushl %%esp; popl %%edx; subl %%edx, %%eax; movl %%eax, %0"
      : "=r" (ret_val)
      : /* no input */
      : "%edx", "%eax");
  return ret_val;
}


int pop_test() {
  int ret_val = 0xffffffff;  /* -1 in decimal */
  /* pushl ret_val       ;; save ret_val on the stack
     movl %esp, %edx     ;; save the stack pointer
     popl %esp           ;; pop stack into the stack pointer
     movl %esp, ret_val  ;; set the popped value as the return value
     movl %edx, %esp     ;; restore original stack pointer
  */
  asm("pushl %1; movl %%esp, %%edx; popl %%esp; movl %%esp, %0; movl %%edx, %%esp"
      : "=r" (ret_val)
      : "r" (ret_val)
      : "%edx");
  return ret_val;
}

int main() {
  printf("push test: %d\n", push_test()); 
  printf("pop test: %d\n", pop_test()); 
}
/* Output:

  push test: 0
  pop test: -1

*/
