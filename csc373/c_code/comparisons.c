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
  int n1 = -1;
  int n2 = 2;

  unsigned int u1 = (unsigned int) n1;  
  unsigned int u2 = (unsigned int) n2;

  /* Is result always 1? Explain. */
  int result = (n1 < n2) == (-n1 > -n2);
  printf("(%d < %d) == (-%d > -%d) evaluates to %d\n", 
	 n1, n2, n1, n2, result);

  /* Is result always 0? Explain. */
  result = ~n1 + ~n2 == ~(n1 + n2);
  printf("(~%d + ~%d) == ~(%d + %d) evaluates to %d\n", 
	 n1, n2, n1, n2, result);

  /* Is result always 1? Explain. */
  result = ((n1 >> 1) << 1) <= n1;
  printf("((%d >> 1) << 1) <= %d evaluates to %d\n",
	 n1, n1, result);

  /* Is result always 1? Explain. */
  /** On left hand side, the expression (int) (u1 - u2) means that
      the subtraction of u2 from u1 is done and then this result is
      cast to an int, that is, a signed int.
  **/
  result = ((int) (u1 - u2)) == -(n2 - n1);
  printf("((int) (%u - %u)) == -(%d - %d) evaluates to %d\n",
	 u1, u2, n2, n1, result);

  return 0;
}
