#include <stdio.h>
#include <math.h>

void show_bytesBE(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = how_many - 1; i >= 0; i--) printf(" %.2x", ptr[i]);
  printf("\n");
}


int main() {
  double d1 = 1.0 / 10.0;
  show_bytesBE("1/10", (unsigned char*) &d1, sizeof(double));
  printf("d1 == %f\n", d1);

  double d2 = pow(2.0, -20.0) * d1;
  show_bytesBE("1/10", (unsigned char*) &d1, sizeof(double));
  printf("d2 == %f\n", d1);

  double d3 = 9.54 * pow(10.0, -8.0);
  show_bytesBE("1/10", (unsigned char*) &d1, sizeof(double));
  printf("d3 == %f\n", d1);

  if (d1 == d2) printf("d1 == d2\n");
  else printf("d1 != d2\n");

  if (d1 == d3) printf("d1 == d3\n");
  else printf("d1 != d3\n");

  if (d2 == d3) printf("d2 == d3\n");
  else printf("d2 != d3\n");

  return 0;
}
