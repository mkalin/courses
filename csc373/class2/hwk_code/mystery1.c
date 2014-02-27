/* Problem 1: What does the function mystery do? 

   To get the idea of what constitutes a good explanation, consider
   the simpler function

       int mys(int n) { 
          int ans = n * 2; 
          ans += 1;
       }

   The function is needlessly long for emphasis. A perfectly good
   explanation of what the function does is:

       The function mys doubles its argument, adds 1, and 
       returns the result.

       The argument and return value are signed integers.

       For example, given 4 as the argument, mys returns 9;
       given -3 as the argument, mys returns -5; and so on.

   For more complicated examples, as the one below, you can 
   explain in more detail. The goal is to explain (a) what the
   function does in general and (b) how the function does what
   it does.

*/

#include <stdio.h>

unsigned int mystery1(unsigned int  a,       
		      unsigned int  b,      
		      unsigned char c) {     /* a char is 8 bits */
  unsigned char* ptr = (unsigned char*) &a; /* make ptr point to a */
  unsigned int ret_val;

  if (b >= sizeof(unsigned int)) b = 0;

  *(ptr + b) = c;  /* In general, if ptr is a pointer, then *ptr is the
                      value pointed at. So, for example, if 

                        int n = 27;
                        int* ptr = &n;

                                    0x1234
                                    +----+
                          ptr ----->| 27 |
                                    +----+
                                      n
                      
                      with 0x1234 as the address of n, then *ptr is 27.
		   */

  /* ptr is of type unsigned char*, that is, pointer to unsigned char; but
     the function is supposed to return an int. So, first, we cast ptr's
     value to unsigned int* (pointer to unsigned int):

              (unsigned int*) ptr

     However, we need to return an unsigned int, not a pointer to an 
     unsigned int. So we dereference the pointer:

             *((unsigned int*) ptr)

     If we just did

             *ptr

     we'd get an unsigned char rather than the unsigned int that we want.
  */
  ret_val = *((unsigned int*) ptr);
  return ret_val; /* return an unsigned int */
}
  
int main() {
  /* sample run */
  unsigned int n = 305419896;
  unsigned char c = 171;
  unsigned result = mystery1(n, 2, c);
  printf("%u ===> %u\n", n, result);
  return 0;
}

