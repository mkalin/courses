#include <stdio.h>
#include <math.h>

int main() {
  double d1 = 1.0 / 10.0;
  
  double d2 = pow(2.0, -20.0) * d1;
  printf("d2 == %f\n", d2);
  
  double d3 = 9.54 * pow(10.0, -8.0);
  printf("d3 == %f\n", d3);
  
  printf("\n");
  if (d2 == d3) printf("d2 == d3\n");
  else printf("d2 != d3\n");
  
  return 0;
}
