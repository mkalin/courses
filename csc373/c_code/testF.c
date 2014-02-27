#include <stdio.h>
#include <float.h>

void run_test(double f) {
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
  /* test results are the same if floats or doubles are used */
  run_test(10.0f);  /* 10.0f is a float (32-bit) constant */
  run_test(100.0f); /* ditto */

  return 0;
}
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
