#include <stdio.h>
#include <float.h>
#include <math.h>

/* A site worth visiting for this material: http://babbage.cs.qc.edu/IEEE-754/Decimal.html */
int main() {

  /* 10.12 in decimal is .... */
  printf("%0.50f\n", 10.12); /* 10.11999999999999921840299066388979554176330566406250 */

  float a = 1.25;
  float b = 0.06;	
  float c = a * b;
  float d = a + c;
  printf("Expected answer is 1.33. Computed answer is %f.\n", d); /* Computed answer = 1.325000 */

  
  double d1 = 2.2, d2 = 1234.5678;
  double d3 = d1 * d2;
  
  /* In my calculator: 2.2 * 1234.5678 = 2716.04916 */
  if (2716.04916 == d3) 
    printf("As expected.\n");
  else 
    printf("Nope, not as expected: %f\n", d3); /* Nope, not as expected: 2716.049160 */

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
  printf("((double)(1 / 103.0)) * 103.0 < 1.0 is %i.\n", ((double)(1 / 103.0)) * 103.0 < 1.0);
  printf("((float)(1 / 103.0F)) * 103.0 > 1.0 is %i.\n", ((float) (1 / 103.0f)) * 103.0 > 1.0);

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

  /* two adjacent floats */
  float expected = 10000.0f;
  float result = +10000.000977f; /* The closest 4-byte float to 10,000 without being 10,000 */
  float diff = fabs(result - expected); 

  /* 10000.000000	10000.000977	0.000977 */
  printf("%f\t%f\t%f\n", expected, result, diff); 

  /* Note that the difference is 97.7 times the epsilon of 00001 */
  if (fabs(result - expected) < 0.00001) printf("They differ.\n"); 
  else printf("They don't differ enough.\n"); /* printed */
  
  /* This is the minimum positive floating point number of type float such that 
     1.0 + FLT_EPSILON != 1.0 is true. Should be no greater than 1E-5.   
  */
  if (fabs(result - expected) < FLT_EPSILON) printf("They differ.\n"); 
  else printf("They don't differ enough.\n"); /* printed */

  if (fabs(result - expected) - 0.001 < FLT_EPSILON) printf("They differ.\n"); /* printed */
  else printf("They don't differ enough.\n"); 
  
  return 0;
}
