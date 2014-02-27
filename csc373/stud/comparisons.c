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

void show_bytes(char*, unsigned char*, int);

int main() {
  int n1 = INT_MAX;
  int n2 = 0;

  unsigned int u1 = (unsigned int) n1;  
  unsigned int u2 = (unsigned int) n2;

  /* Is result always 1? Explain. */
  
  /* Answer:  No, if either n1 or n2 is INT_MIN.  When you use the 
   *          unary negation operator on n1 you end up with the following 
   *          statement (~n) + 1 which is the two's complement.  In the 
   *  		  case of INT_MIN, -INT_MIN == INT_MIN which causes a failure
   *          of the boolean logic and result = 0
   */
   
  int result = (n1 < n2) == (-n1 > -n2);
  printf("(%d < %d) == (-%d > -%d) evaluates to %d\n", 
	 n1, n2, n1, n2, result);

  /* Is result always 0? Explain. */
  
  /* Answer: Yes, the ~ operator is the one's complement operator which
   *         will give the complement of a given number - 1.  As such the
   *         left hand of the equation will always be off from the right
   *         hand side by 1, because both numbers are affected by the ~
   *         operator as opposed to just the one number on the right
   *         hand side.  Take the case of n1 = 5 and n2 = 6.  The 
   *         one's complement of these two numbers is -4, and -5 respectively
   * 		 when placed into the equation we get the following:
   *             ~5 + ~6 == ~(5 + 6)
   *         order of operations dictates that (5 + 6) must be computed
   *         before the one's complement can be taken.  Which gives the
   *         following:
   *             -6 + -7 == ~11
   *         The next step yeilds:
   *              -13 == -12 
   *         Which yeilds a resulf of 0
   */ 

  result = ~n1 + ~n2 == ~(n1 + n2);
  printf("(~%d + ~%d) == ~(%d + %d) evaluates to %d\n", 
	 n1, n2, n1, n2, result);


  /* Is result always 1? Explain. */
  
  /* Recheck */
 
  /* Answer: Yes, the right shift pushes the least significant bit out
   *         of memory range for the number, essentially removing it.  The 
   *         left shift replaces the least significant bit with a 0, the best case
   *         for the number is that before the shifts the least significant bit
   *         was already a 0, then the number whould be unchanged, anything else 
   *         would cause the number to be smaller, therefore the boolean expression
   *         will always return 1.
   *         
   */
 
  result = ((n1 >> 1) << 1) <= n1;
  printf("((%d >> 1) << 1) <= %d evaluates to %d\n",
	 n1, n1, result);


  /* Is result always 1? Explain. */
  
  /* Answer: Yes, the right hand side of the expression will evaluate to
   *         the two's complement of the left hand side without the unary 
   *         negation operator.  Once the unary negation operator is applied
   *         and the two's compliment of (n2 - n1) is computed, the two
   *         sides of the express equal. 
   */ 
  
  /** On left hand side, the expression (int) (u1 - u2) means that
      the subtraction of u2 from u1 is done and then this result is
      cast to an int, that is, a signed int.
  **/
  
  result = ((int) (u1 - u2)) == -(n2 - n1);
  printf("((int) (%u - %u)) == -(%d - %d) evaluates to %d\n",
	 u1, u2, n2, n1, result);

  return 0;
}

