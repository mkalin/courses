#include <stdio.h>

int push_test() {
  int ret_val;
  /* movl %esp, %eax    ;; save stack pointer
     pushl %esp         ;; push stack pointer: original value or decremented?
     popl %edx          ;; pop the top value back into %edx
     subl %edx, %eax    ;; subtract the two values: 0 or 4 results
     movl %eax, ret_val ;; set up the return value
  */
  asm("movl %%esp, %%eax; pushl %%esp; popl %%edx; subl %%edx, %%eax; movl %%eax, %0"
      : "=r" (ret_val)
      : /* not input */
      : "%edx", "%eax");
  return ret_val;
}


int pop_test() {
  int ret_val = 0xffffffff;
  /* pushl ret_val       ;; save ret_val on the stack
     movl %esp, %edx     ;; save the stack pointer
     popl %esp           ;; pop to the stack pointer: original value or incremented?
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
  printf("push test: %d\n", 
	 push_test()); /* output is 0; hence, original value pushed */
  printf("pop test: %d\n",
	 pop_test());  /* output is -1; hence, orignal value popped */
}
