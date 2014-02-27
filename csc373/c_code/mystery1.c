/* Problem 1: What does the function mystery do? 
   You should answer at two levels. First, explain in general what it 
   does by giving some sample inputs and outputs. For example, the 
   code as written generates this output

            305419896 ===> 313218680

   How did the function mystery map 305419896 to 313218680?
   If you know how the function works, you might also suggest a better
   name for it.

   Second, document the lines of code in the function, in particular the
   2nd line. (If you know what the 2nd line does, documenting the first
   line will make sense.) I've already documented and 3rd and 4th lines.
*/

#include <stdio.h>

unsigned int mystery(unsigned int  a,       
		     unsigned int  b,      
		     unsigned char c) {    /* a char is 8 bits */
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
  unsigned result = mystery(n, 2, c);
  printf("%u ===> %u\n", n, result);
  return 0;
}

