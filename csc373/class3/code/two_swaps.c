#include <stdio.h>

int swap_in_c(int* ptr, int swap_value) {
  int temp = *ptr;     /* save original value */
  *ptr = swap_value;   /* reset to swap value */
  return temp;         /* return original value */
}

int swap_in_asm(int* ptr, int swap_value) {
  /* ebp points to the "call frame" or "stack frame," which is
     area of the stack allocated for this particular call.
     eax, edx, and ecx are general-purpose registers. (By the way,
     the "e" in all of this is for "extended," which in turn means
     32 bits.) 

     The 8 and the 12 are byte offsets from where ebp points, which is
     at the original TOP of the call frame. So, basically, the ptr parameter
     is stored 8 bytes from the frame pointer (ebp) and the swap_value
     parameter is stored 12 bytes from the frame pointer.

     Self-test review question: What's the difference between (%eax) and %eax?

     Finally, %eax is a "first among equals" when it comes to general-purpose
     registers in that it holds the return value. So the invoking function, in
     this case main(), gets the value that swap_in_asm stores in eax.
  */
  asm("movl 8(%ebp),%eax");    /* fetch ptr, the pointer parameter */
  asm("movl 12(%ebp),%edx");   /* fetch swap_value, the other parameter */
  asm("movl (%eax),%ecx");     /* get the value that ptr points to */
  asm("movl %edx,(%eax)");     /* store swap_value at ptr */
  asm("movl %ecx,%eax");       /* return the original value of *ptr */
}

int main() {
  int n1 = 7;
  int n2 = swap_in_c(&n1, -999);
  printf("n1 == %d and n2 == %d\n", n1, n2); /* output: n1 == -999 and n2 == 7 */

  n1 = 7;
  n2 = swap_in_asm(&n1, -999);
  printf("n1 == %d and n2 == %d\n", n1, n2); /* output: n1 == -999 and n2 == 7 */
  return 0;
}
