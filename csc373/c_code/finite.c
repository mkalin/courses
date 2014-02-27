#include <stdio.h>
#include <limits.h>

int main() {
  /* basic overflow example */
  printf("Largest signed int is %d (%x)\n", 
	 INT_MAX, INT_MAX);
  printf("Largest + 1 is       %d (%x)\n", 
	 INT_MAX + 1, INT_MAX + 1); /* generates compiler warning on overflow */
  printf("Smallest signed is   %d (%x)\n", 
	 INT_MIN, INT_MIN);         /* same as above */
  /* output:
  Largest signed int is 2147483647 (7fffffff)
  Largest + 1 is       -2147483648 (80000000)
  Smallest signed is   -2147483648 (80000000)
  */

  printf("Largest unsigned int is %u (%x)\n", 
	 UINT_MAX, UINT_MAX);
  printf("Largest unsigned + 1 is %u (%x)\n", 
	 UINT_MAX + 1, UINT_MAX + 1); /* generates compiler warning on overflow */
  printf("Largest signed int is   %d (%x)\n",
	 INT_MAX, INT_MAX);
  /* output:
  Largest unsigned int is 4294967295 (ffffffff)
  Largest unsigned + 1 is 0 (0)
  Largest signed int is   2147483647 (7fffffff)
  */

  printf("Largest unsigned is %u times as big as the largest signed.\n",
	 UINT_MAX / (unsigned) INT_MAX);
  /* Largest unsigned is 2 times as big as the largest signed. */

  /* multiplication via shifting and one addition */
  unsigned int n = 54321;
  unsigned int n_doubled = n << 1;
  printf("\nn      ==  %u\nn << 1 == %u\n", 
	 n, n_doubled);
  printf("n * 2  == %u\n", n * 2);
  /*
    n      ==  54321
    n << 1 == 108642
    n * 2  == 108642
  */


  printf("\n");
  unsigned int n_quadrupled = n << 2;
  printf("n * 4        == %u\n", n * 4);
  printf("n << 2       == %u\n", n_quadrupled);
  printf("n << 1 + n   == %u\n", n_doubled + n);
  printf("n * 3        == %u\n", n * 3);
  /*
    n * 4        == 217284
    n << 2       == 217284
    n << 1 + n   == 162963
    n * 3        == 162963
  */

  /* integer wrap up with "C puzzles" */
  printf("\n");
  int x = INT_MIN;  /* for a 32-bit int, -2,147,483,648. In binary,
		       10000000000000000000000000000000 */
  if (x >= 0 || ((2 * x) < 0)) printf("x >= OR 2 * x < 0\n");
  else printf("Ooops! 2 * x is %d\n", 2 * x);


  /* First, a brief review of sign changes in 2's complement */
  printf("\n");
  int t = -7;
  t = ~t;    /* 1's complement */
  t += 1;    /* 2's complement */
  printf("%t = ~t followed by t += 1 is %d\n", t); /* 7 */
  t = ~t;
  t += 1;
  printf("%t = ~t followed by t += 1 is %d\n", t); /* -7 */

  printf("\n");
  if (x > 0 || -x >= 0) printf("Just what I expected.\n");
  else printf("Ooops! Must not either x be > 0 or -x >= 0?\n");
  if (x == -x) printf("yes, for some x, x == -x, in this case %d == %d\n",
		      x, -x);
  /* Recall that x is 1000...000. So the 1's complement is
     0111...111. Now add 1. */

  /* Work for any value of x? Why, assuming 32-bit int? */
  printf("\n");
  x = 31;
  if ((x & 7) != 7 || (x << 30) < 0)       /* 7 in binary is 0...111 */
    printf("x & 7 != 7 OR x << 30 < 0\n"); /* 31 is 0..11111 */
  else
    printf("Ooops!\n");

  return 0;
}
