#include <stdio.h>

unsigned char convert(unsigned char x) {
  unsigned char y;
  y = (x / 10) << 4;
  y = y | (x % 10);  /* % is modulus */
  return y;
}

/* Hex  Binary Decimal

   0 	0000    0	  
   1 	0001    1	  
   2 	0010    2	  
   3 	0011    3	 
   4 	0100    4	 
   5 	0101    5	 
   6 	0110    6	 
   7 	0111    7	 
   8 	1000    8	 
   9 	1001    9	 
   a 	1010   10 	
   b 	1011   11
   c 	1100   12	
   d 	1101   13	
   e 	1110   14	
   f 	1111   15	 
*/

int main() {
  unsigned char c = 241;         /* 11110001 in binary, f1 in hex */
  unsigned char r = convert(c);
  printf("%x\n", c);             /* f1 */
  printf("%x\n", r);             /* ? */

  c = 243;                       /* 11110011 in binary, f3 in hex */
  r = convert(c);
  printf("%x\n", c);             /* f3 */
  printf("%x\n", r);             /* ?  */

  c = 255;                       /* 11111111 in binary, ff in hex */
  r = convert(c);
  printf("%x\n", c);             /* ff */
  printf("%x\n", r);             /* ?  */

  return 0;
}
