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

/* The function inserts byte c (3rd argument) into integer a (1st argument)
   at position b (2nd argument). On a little-endian machine, the position
   is computed from the LSB (by our convention, the right side); on a 
   big-endian machine, the position is computed from the MSB (by our 
   convention, the left side).

   It's easiest to see by changing the printf formatter in main from 
   %d to %x.
*/
unsigned int mystery(unsigned int  a,       
		     unsigned int  b,      
		     unsigned char c) {    /* a char is 8 bits */
  unsigned char* ptr = (unsigned char*) &a; /* make ptr point to a */
  unsigned int ret_val;

  if (b >= sizeof(unsigned int)) b = 0;  /* Is the position inbounds? If not, make 
					    make it zero. */

  /* Store byte c at position (ptr + b), where ptr is &a and b is an integer
     between 0 and sizeof(int).
  */
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
  /* added for clarification */
  printf("Arguments are: int ==> %x, position ==> %d, byte ==> %x\n",
	 n, 2, c);
  /* output is 

       12345678 ===> 12ab5678 

     on a little-endian machine.
  */
  printf("%x ===> %x\n", n, result);  /* changed to %x from %u */
  return 0;
}

