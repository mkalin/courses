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

/* Comment: Mike Haller
 * 
 * mystery = unsigned int reverse_bytes(unsigned int n);
 * This function completely reverses the bytes of the 
 * given unsigned int n.  This function is essentially an
 * endian converter that could be used to convert data stored in
 * memory from Big Endian to Little Endian and vice versa.  This can 
 * most easily be seen by the output of the show_bytes function.
 * 
 *    1234 ====> -771489792
 *    d2 04 00 00 ====> 00 00 04 d2
 * 
 *    -1 ====> -1
 *    ff ff ff ff ====> ff ff ff ff
 * 
 *    15 ====> 251658240
 *    0f 00 00 00 ====> 00 00 00 0f
 * 
 */ 

unsigned int mystery(unsigned int n) {
  /* >> is the right-shift operator. The shift is logical, not arithmetic,
     because the data type is unsigned. (P. 50 in the textbook.)
     << is the left-shift operator.
     & is the bitwise logical-and operator.
     | is the bitwise logical-or operator.
  */

   /* Comment: Mike Haller
   *  (n >> 24) shifts to get byte 1 in the 4th byte position
   *  (n << 8) & 0x00FF0000 shifts the 3rd byte position into the 
   *        second byte position, then performs the & with 0x00FF0000 
   *        which clears the value from the 4th byte position that would
   *        have been moved into the 3rd byte position by the shift.
   *  (n >> 8) & 0x0000FF00 shifts the 2nd byte position into the 3rd
   *        byte position, then performs the & with 0x0000FF00 which
   *        clears the value from the 1st byte position that would have
   *        been moved into the 2nd byte position by the shift.
   *  ( n << 24) shifts n to get byte 4 in the 1st byte position.
   * 
   *  These for steps are done in order with the or between each.
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
    unsigned int result = mystery(next);
    printf("%d ===> %d\n", next, result);
    printf("%x ===> %x\n", next, result);
  }
  return 0;
}

