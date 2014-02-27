#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

/* This program illustrates various issues with arbitrary-precision arithmetic
   in C, in particular with the floating-point types float and double. The
   general solution is a library such as the one from GNU available at

      http://gmplib.org/
*/

/* This program uses the fabs function, which is part of the run-time
   math library. To enable its use, this file (math.c) was
   compiled/linked as follows:

             gcc -o snotation snotation.c -lm

   In "-lm", that's a lowercase L rather than a one.
 */

void run_test(float f) {
  printf("\nRunning test on %f\n", f);
  float incr = 0.0f;
  int i = 1;
  while (1) {  /* loop indefinitely */
    incr += FLT_EPSILON; /* incr = incr + FLT_EPSILON */
    float t = f + incr;  /* t is f + the current increment */
    printf("iteration == %d: incr = %f  f == %f  t == %f\n", i++, incr, f, t);

    /* exit the while loop if the absolute difference between t and f
       is equal to or greater than FLT_EPSILON 
    */
    if (fabs(t - f) >= FLT_EPSILON) break; 
  }
}

int main() {  
  /** some basic problems illustrated **/
  double d1 = 2.2, d2 = 1234.5678;
  double d3 = d1 * d2;
  
  /* In my calculator: 2.2 * 1234.5678 = 2716.04916 */
  if (2716.04916 == d3) 
    printf("As expected.\n");
  else 
    printf("Nope, not as expected: %f\n", d3); /* Nope, not as expected: 2716.049160 */
  printf("\n");

  /* Expected output: 10.1 
    1.010000
    2.020000
    3.030000
    4.040000
    5.050000
    6.060000
    7.070001   ;; evident rounding now appears
    8.080001
    9.090001
   10.100001
  */
  float num = 1.01f;
  int i = 0;
  while (i++ < 10) {
    printf("%12f\n", num);
    num += 1.01f;
  }

  /* In exact arithmetic, the left-hand sides of the comparisons are equal to 1; hence,
     we'd expect the answers to be 0 (false). In fact, the answers are both 1 (true).
  */
  printf("((double)(1 / 103.0)) * 103.0 < 1.0 is %i.\n", ((double)(1 / 103.0))  * 103.0 < 1.0);
  printf("((float)(1 / 103.0F)) * 103.0 > 1.0 is %i.\n", ((float) (1 / 103.0f)) * 103.0 > 1.0);
  printf("\n");

  /** Floating-point constants available in float.h **/

  /* max in 32 bits */
  printf("Max:\n");
  float data = FLT_MAX;
  printf("data = %f\n", data); /* data = 340282346638528859811704183484516925440.000000 */
  printf("data = %e\n", data); /* data = 3.402823e+38 */
  printf("data = %e\n", data);
  printf("\n");

  /* min in 32 bits */
  printf("Min:\n");
  data = FLT_MIN;
  printf("data = %f\n", data); /* data = 0.000000 */
  printf("data = %e\n", data); /* data = 1.175494e-38 */
  printf("\n");

  /* formatting */
  printf("\n");
  printf("Formatting:\n");
  data = 0.01234;
  printf ("data = %e\n", data);    /* data = 1.234000e-02 */
  printf( "data = %.2e\n", data ); /* data = 1.23e-02 */

  /** floating-point comparisions: perils and fixes **/

  printf("\n");
  printf("Epsilon:\n");
  data = FLT_EPSILON;             /* least signficant representable digit */
  printf("epsilon = %e\n", data); /* epsilon = 1.192093e-07 */

  printf("\n");
  float f1 = 10000.0; 
  float f2 = 10000.00009; 
  if (f1 == f2) printf("Yes, f1 and f2 are equal...\n"); /* printed */

  /* try again */
  float diff = fabs(f1 - f2); 
  printf("diff (%e - %e) = %e\n", 
	 f1, f2, diff);                   /* diff (1.000000e+04 - 1.000000e+04) = 0.000000e+00 */
  if (diff) printf("f1 and f2 differ...\n"); /* not printed */
  printf("\n");

  /* two adjacent floats */
  float expected = 10000.0f;
  float result =   10000.000977f; /* The closest 4-byte float to 10,000 without being 10,000 */
  diff = fabs(result - expected); 

  /* 10000.000000	10000.000977	0.000977 */
  printf("%f\t%f\t%f\n", expected, result, diff); 

  /* Note that the difference is 97.7 times the epsilon of 0.00001 */
  if (fabs(result - expected) < 0.00001) printf("They differ.\n"); 
  else printf("They don't differ enough.\n"); /* printed */
  
  /* FLT_EPSILON is the minimum positive floating point number of type float such that 
     1.0 + FLT_EPSILON != 1.0 is true. Should be no greater than 1E-5.   
  */
  if (fabs(result - expected) < FLT_EPSILON) printf("They differ.\n"); 
  else printf("They don't differ enough.\n"); /* printed */

  if (fabs(result - expected) - 0.001 < FLT_EPSILON) printf("They differ.\n"); /* printed */
  else printf("They don't differ enough.\n"); 

  /* How long does it take? */
  run_test(10.0f);  /* 10.0f is a float (32-bit) constant */
  run_test(100.0f); /* ditto */
  printf("\n");

  /* output (slightly formatted for readability):

     Running test on 10.000000
     iteration ==  1: incr = 0.000000  f == 10.000000  t == 10.000000
     iteration ==  2: incr = 0.000000  f == 10.000000  t == 10.000000
     iteration ==  3: incr = 0.000000  f == 10.000000  t == 10.000000
     iteration ==  4: incr = 0.000000  f == 10.000000  t == 10.000000
     iteration ==  5: incr = 0.000001  f == 10.000000  t == 10.000001
     
     Running test on 100.000000
     iteration ==  1: incr = 0.000000  f == 100.000000  t == 100.000000
     iteration ==  2: incr = 0.000000  f == 100.000000  t == 100.000000
     iteration ==  3: incr = 0.000000  f == 100.000000  t == 100.000000
     ...
     iteration == 11: incr = 0.000001  f == 100.000000  t == 100.000000
     iteration == 12: incr = 0.000001  f == 100.000000  t == 100.000000
     iteration == 13: incr = 0.000002  f == 100.000000  t == 100.000000
     iteration == 14: incr = 0.000002  f == 100.000000  t == 100.000000
     ...
     iteration == 28: incr = 0.000003  f == 100.000000  t == 100.000000
     iteration == 29: incr = 0.000003  f == 100.000000  t == 100.000000
     iteration == 30: incr = 0.000004  f == 100.000000  t == 100.000000
     iteration == 31: incr = 0.000004  f == 100.000000  t == 100.000000
     iteration == 32: incr = 0.000004  f == 100.000000  t == 100.000000
     iteration == 33: incr = 0.000004  f == 100.000000  t == 100.000008
  */

  /** currency **/

  /* 10.12 in decimal is .... */
  printf("%0.50f\n", 10.12); /* 10.11999999999999921840299066388979554176330566406250 */

  float a = 1.25;
  float b = 0.06;	
  float c = a * b;
  float d = a + c;
  printf("Expected answer is 1.33. Computed answer is %f.\n", d); /* Computed answer = 1.325000 */
  
  /* Expected value: $84.83 */
  float price = 4.99f;
  int quantity = 17;
  float total = price * quantity;
  printf("The total price is $%f.\n", total); /* The total price is $84.829994. */

  /* Expected value: $90 */
  int fullPrice = 100;
  float discount = 0.1f;
  int finalPrice = (int)(fullPrice * (1 - discount));
  printf("The discounted price is $%i.\n", finalPrice); /* $89 */
  
  /* e and pi */
  double ans = pow(M_E, M_PI) - M_PI; /* e and pi, respectively */
  printf("%lf\n", ans); /* 19.999100 prints: expected is 19.99909997 */

  return 0;
}
