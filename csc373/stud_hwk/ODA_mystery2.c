/*Doug Oda 6/17/06
/*New Name "Change endian"
 *
 *Example 1:
    unsigned int next = 305419896; //0x12345678
    unsigned int result = mystery(next);

	gives the result of 2018915346 or 0x78563412

  *Example 2:
    unsigned int next = 857870592; //0x33221100
    unsigned int result = mystery(next);

	gives the result of 1122867 or 0x00112233

  *the function uses a series of shifts (and assumes that the >> is a logical shift)
  *to reposition the bytes in the proper place, It clears the other stuff from the 
  *middle two bytes by a logical and 0xFF in the correct place and relies on the
  *>> and << to shif in zeros to clear unwanted bits from the two end bytes. The whole
  *thing is ored together to basically reverse the order of the bytes in the int.


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

unsigned int mystery(unsigned int n) 
{
  /* >> is the right-shift operator. The shift is logical, not arithmetic,
     because the data type is unsigned. (P. 50 in the textbook.)
     << is the left-shift operator.
     & is the bitwise logical-and operator.
     | is the bitwise logical-or operator.
  */
  unsigned int temp = 
   
    (n >> 24) |					/*this puts byte 3 into byte 0 position and (if this is a logical shift) clears all other bytes*/
    ((n << 8) & 0x00FF0000) |   /*this moves byte 1 into byte 2 position then uses the and to clear other bytes*/
    ((n >> 8) & 0x0000FF00) |   /*this moves byte 2 into byte 1 position then clears all other bytes*/
    (n << 24);					/*this moves byte 0 into byte 3 position and by shifting clears all other bytes*/
  
  return temp;
}

unsigned int prompt_and_read() 
{
  unsigned int next;
  printf("\nprompt> Please enter an integer (0 to exit): ");
  scanf("%u", &next);
  if (next == 0) exit(0);
  return next;
}

int main() 
{
  while (1) 
  {
    unsigned int next = prompt_and_read();
    unsigned int result = mystery(next);
    printf("%d ===> %d\n", next, result);
  }
  return 0;
}

