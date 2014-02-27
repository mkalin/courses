#include <stdio.h>
#include <math.h>

int main() {
  double ans = pow(M_E, M_PI) - M_PI; /* e and pi, respectively */
  printf("%lf\n", ans); /* 19.999100 prints: expected is 19.99909997 */

  return 0;
}
