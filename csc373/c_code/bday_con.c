#include <stdio.h>

#define N (60) /* number of people */

int main() {
  const float temp = 366.0f;
  const float days_in_year = 365.0f; /* ignore leap years */
  float prob = 1.0f; /* initial probability */

  /* probability of a unique birthday given N persons:

         1         2         3         4   ...
      365/365 * 364/365 * 363/365 * 362/365...

     The loop computes the probability of not having a
     unique birthday for values 1 through N. 
   */
  int i;
  for (i = 1; i <= N; i++) {
    prob *= (temp - i) / days_in_year;
    printf("%4i - %5.3f", i, 1.0f - prob);
    if (i % 5 == 0) printf("\n");
  }
  return 0;
}
/* 
 Probabilities of shared birthdays == cache conflict

   1 - 0.000   2 - 0.003   3 - 0.008   4 - 0.016   5 - 0.027
   6 - 0.040   7 - 0.056   8 - 0.074   9 - 0.095  10 - 0.117
  11 - 0.141  12 - 0.167  13 - 0.194  14 - 0.223  15 - 0.253
  16 - 0.284  17 - 0.315  18 - 0.347  19 - 0.379  20 - 0.411
  21 - 0.444  22 - 0.476  23 - 0.507  24 - 0.538  25 - 0.569
  26 - 0.598  27 - 0.627  28 - 0.654  29 - 0.681  30 - 0.706
  31 - 0.730  32 - 0.753  33 - 0.775  34 - 0.795  35 - 0.814
  36 - 0.832  37 - 0.849  38 - 0.864  39 - 0.878  40 - 0.891
  41 - 0.903  42 - 0.914  43 - 0.924  44 - 0.933  45 - 0.941
  46 - 0.948  47 - 0.955  48 - 0.961  49 - 0.966  50 - 0.970
  51 - 0.974  52 - 0.978  53 - 0.981  54 - 0.984  55 - 0.986
  56 - 0.988  57 - 0.990  58 - 0.992  59 - 0.993  60 - 0.994

Semantics:

Among N people (for N from 1 through 60), what is the liklihood that
any will share a birthday? This is the cache collision problem. Note
that, with 23 people, the probability of a shared birthday > 50%.
With 60 people, it's a near certainty.
*/


