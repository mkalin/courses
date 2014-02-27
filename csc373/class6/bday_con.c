#include <stdio.h>

#define N (50)
int main() {
  const float temp = 366.0f;
  const float days_in_year = 365.0f; /* ignore leap years */
  float prob = 1.0f;

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

Semantics:

Among N people (for N from 1 through 50), what is the liklihood that
any will share a birthday? This is the cache collision problem. Note
that, with 23 people, the probability of a shared birthday > 50%.
With 50 people, it's almost a certainty.
*/


