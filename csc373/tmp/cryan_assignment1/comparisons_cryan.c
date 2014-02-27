/* Problem 1: Answer the questions below. For each answer, explain whether
   the expression shown evaluates to true (non-zero) or false (zero). For example,
   you'd say that 

     (n1 < n2) == (-n1 > -n2)

   always evaluates to true or, for some values, might evaluate to false. 

   A perfect score requires the right answer with a solid explanation.
   The right answer without a solid explanation is worth very little. 
   The emphasis, in other words, is on the explanation.

   The code can be compiled and executed, of course.
*/

#include <stdio.h>
#include <limits.h>

int main() {
  int n1 = -1;
  int n2 = 2;

  unsigned int u1 = (unsigned int) n1;  
  unsigned int u2 = (unsigned int) n2;

  /* Is result always 1? Explain. */
  int result = (n1 < n2) == (-n1 > -n2);
  printf("(%d < %d) == (-%d > -%d) evaluates to %d\n", 
	 n1, n2, n1, n2, result);
  /* I tried this with several different combinations:  n1 greater than n2, n1 and n2 equal, n2 greater than n1, and in all combinations the result
  was equal to 1.  I think this has to do with the fact that if one side of the equation is true, then the other side has to be true, which also
  correlates with both sides being false.  If both sides of the equation equal each other (ie, true == true or false == false), then the equation
  is actually true and will result with a 1 each time.
  */
	 

  /* Is result always 0? Explain. */
  result = ~n1 + ~n2 == ~(n1 + n2);
  printf("(~%d + ~%d) == ~(%d + %d) evaluates to %d\n", 
	 n1, n2, n1, n2, result);
  /*I tried this with several combinations (as was done in the previous section) and got the same results:  always obtaining a result equal to 0, or
  false.  The "~" denotes a complement, which essentially transforms all the bits: 1's turn to 0's and 1's to 0's.  The reason that this is always 
  going to be false is because the numbers on the left are going to be different than the numbers on the right.  So if n1=0, then ~n1 is going 
  to equal -1.
	 
	 
	 
  /* Is result always 1? Explain. */
  result = ((n1 >> 1) << 1) <= n1;
  printf("((%d >> 1) << 1) <= %d evaluates to %d\n",
	 n1, n1, result);
  /* The result will always be 1.  This is because, in parenthesis, n1 is moving to the right by one byte, but then, whatever value was found in 
  the parenthesis moves again to the left...essentially back to the original position.  This is based off the order of operations where everything in
  the parenthesis is performed first, then the next function is performed. */

  
  
  /* Is result always 1? Explain. */
  /** On left hand side, the expression (int) (u1 - u2) means that
      the subtraction of u2 from u1 is done and then this result is
      cast to an int, that is, a signed int.
  **/
  result = ((int) (u1 - u2)) == -(n2 - n1);
  printf("((int) (%u - %u)) == -(%d - %d) evaluates to %d\n",
	 u1, u2, n2, n1, result);
	 
  /*  I'm not sure, but I'm thinking it's because a signed int includes both positive and negative and unsigned cannot handle negatives.  It is 
  defined at the beginning that u1 = n1 and u2 = n2, so the operations (u1-u2) and -(n2-n1) mathmatically equal each other anyway. Uhm...not 100%
  sure.  

  return 0;
}
