/* Problem 3: What does the function mystery do?
   You should answer at two levels. First, explain in general what it 
   does by giving some sample inputs and outputs. For example, on a 
   sample run I got

            1234 ===> -771489792

   as my output. How did the function mystery map 1234 to -771489792?
   If you know how the function works, you might also suggest a better
   name for it.

   Second, document the lines of code in the function. There are four
   such lines, involving shifts and logical-ands. What do they do?
*/

#include <stdio.h>

/* A better name for this function would be "endian_reverse." In effect,
   it changes a big-endian integer to a little-endian integer and vice-versa. 
*/

unsigned int mystery(unsigned int n) {
  /* >> is the right-shift operator. The shift is logical, not arithmetic,
     because the data type is unsigned. (P. 50 in the textbook.)
     << is the left-shift operator.
     & is the bitwise logical-and operator.
     | is the bitwise logical-or operator.
  */

  /* By assumption, an int is 32 bits. Note that the bitwise operations
     do not involve assignment statements so that n remains unchanged.
     Only temp is impacted by the operations.
  */
  unsigned int temp = 
    (n >> 24)               |   /* leftmost becomes rightmost byte */
    ((n << 8) & 0x00FF0000) |   /* switch the two middle bytes */
    ((n >> 8) & 0x0000FF00) |
    (n << 24);                  /* rightmost becomes leftmost byte */

  return temp; /* reversed endian integer */
}

unsigned int prompt_and_read() {
  unsigned int next;
  printf("\nprompt> Please enter an integer (0 to exit): ");
  scanf("%u", &next);
  if (next == 0) exit(0);
  return next;
}

int main() {
  /* To illustrate the answer, I'm just hardwiring the arguments. */
  unsigned int next = 0xABCDEF12;
  unsigned int result = mystery(next);
  printf("%x ==> %x\n", next, result);
  next = mystery(result);
  printf("%x ==> %x\n", result, next);
  /* output:

        abcdef12 ==> 12efcdab
        12efcdab ==> abcdef12
  */

  /*
  while (1) {
    unsigned int next = prompt_and_read();
    unsigned int result = mystery(next);
    printf("%d ===> %d\n", next, result);
  }
  */
  return 0;
}

