
//Doug Oda 6/17/06
//Please note that I've changed the integers to characters for easier representation
   

/* Problem 1: Answer the questions below. For each answer, explain whether
   the expression shown evaluates to true (non-zero) or false (zero). For example,
   you'd say that 

     (n1 < n2) == (-n1 > -n2)

   always evaluates to true or, for some values, might evaluate to false. The
   easiest way to show that it might evaluate to false is to provide the values
   and then explain. In general, of course, the expressions are more interesting
   if they somethings evaluate to false.
*/

#include <stdio.h>
#include <limits.h>

int main() {

  signed char n1 = -1;
  signed char n2 = 0;

  unsigned char u1 = (unsigned char) n1;  
  unsigned char u2 = (unsigned char) n2;

  /* Is result always 1? Explain. */
  signed char result = (n1 < n2) == (-n1 > -n2);
 /*the result is 0 if,for example, n1 is the minimum value of the unsigned number
  *in this case -128 or 10000000b
  *a negative of this number is 2's compliment of the -128  = 01111111b + 1b = 10000000b
  *since n1 is the same if it is it it's raw form or negated then any value for n2 results in a 0
  */


  /* Is result always 0? Explain. */
  result = ~n1 + ~n2 == ~(n1 + n2);
  /*the result is always zero, I believe that you mentioned DeMorgans theorem in class. This is the 
   *central theorem that makes reduction of boolean experssions possible. If there was a hole in
   *it, even at the limits, then it would have been found long before this. 
   *~n1 + ~n2 == ~(n1 * n2) does yield a 1 */



  /* Is result always 1? Explain. */
  result = ((n1 >> 1) << 1) <= n1;
  /*result will always be 1 
   *it does not matter if the compiler evaluates the >> as a logical shift or an arithmatic shift
   *since after a 0 or 1 is shifted into the left bit it is then shifted out leaving the
   *original value in the msb. Since the lsb is always replaced by a zero then the resulting calculation
   *will be equal to the original number if the original was an even number(ends in 0) and less than the
   *ofiginal if it was an odd number. 




  /* Is result always 1? Explain. */
  /** On left hand side, the expression (int) (u1 - u2) means that
      the subtraction of u2 from u1 is done and then this result is
      cast to an int, that is, a signed int.
  **/
  result = ((signed char) (u1 - u2)) == -(n2 - n1);
  /*the result can be zero if n1 or n2 is -128.
   *example: when unsigned u1 is assigned from a signed n1 at -128 (0x80) it becomes 128 (0x80)
   *plug in any number for n2 and result will be 0
   */


  return 0;
  }
