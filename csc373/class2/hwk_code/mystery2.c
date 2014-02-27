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
#include <stdlib.h>

unsigned int mystery2(unsigned int n) {
  /* >> is the right-shift operator. The shift is logical, not arithmetic,
     because the data type is unsigned. (P. 50 in the textbook.)
     << is the left-shift operator.
     & is the bitwise logical-and operator.
     | is the bitwise logical-or operator.
  */
  unsigned int temp = 
    (n >> 24) | 
    ((n << 8) & 0x00FF0000) |
    ((n >> 8) & 0x0000FF00) |
    (n << 24);
  
  return temp;
}

unsigned int prompt_and_read() {
  unsigned int next;
  printf("\nprompt> Please enter an integer (0 to exit): ");
  scanf("%u", &next);
  if (next == 0) exit(0);
  return next;
}

int main() {
  while (1) {
    unsigned int next = prompt_and_read();
    unsigned int result = mystery2(next);
    printf("%d ===> %d\n", next, result);
  }
  return 0;
}

