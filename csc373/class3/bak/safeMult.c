#include <limits.h>

int safe_mult(int n1, int n2, int* dest) {
  int ret_val;
  
  *dest = n1 * n2;   /* potential overflow */
  
  /* setae %%bl sets the result of the overflow test in 
     a single-byte register, bl. 

     movzbl %%bl,%0 moves the test result to 32-bit register
     of the compiler's choosing, indicated by %0.

     In the entry after the first colon, 

                 "=r" (ret_val)

     is assembler for

                 ret_val = %0

     where %0 is the register (the "r" in "=r") that the compiler chose.

     There are no additional inputs to the assembler code; hence, the 
     second colon has nothing following it.

     The third and last colon indicates the register to use for
     scratchpad in the multiplication. Note that this register is not
     eax, which is "special purpose" in that it holds the return value
     of a function.
  */
  asm("setae %%bl; movzbl %%bl,%0"
      : "=r" (ret_val)               /* lvalue to set */
      :                              /* no inputs */
      : "%ebx");                     /* scratchpad */

  return ret_val;
}

void print(const char* msg, int n) {
  printf("%s: returned product == %d\n", msg, n);
}


int main() {
  int n;
  char* msg;

  int flag = safe_mult(16, 48, &n);
  msg =  (!flag) ? "Overflow on 16 * 48" 
                 : "No overflow on 16 * 48";
  print(msg, n);

  flag = safe_mult(INT_MAX, INT_MAX, &n);
  msg = (!flag) ? "Overflow on INT_MAX * INT_MAX" 
                : "No overflow on INT_MAX * INT_MAX";
  print(msg, n);
  
  return 0;
}
/* output:

    No overflow on 16 * 48: returned product == 768
    Overflow on INT_MAX * INT_MAX: returned product == 1
*/
