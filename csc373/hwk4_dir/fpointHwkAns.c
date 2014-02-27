/* This program uses the pow function, which is part of the run-time
        math library. To enable its use, this file (fpointHwk.c) was
        compiled/linked as follows:
	
	gcc -o fpointHwk -lm fpointHwk.c
	
        In "-lm", that's a lowercase L rather than a one.
*/

#include <stdio.h>
#include <math.h>

void show_bytesBE(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = how_many - 1; i >= 0; i--) printf(" %.2x", ptr[i]);
  printf("\n");
}


int main() {
  /* first printf statements */
  double d1 = 1.0 / 10.0;
  printf("d1 == %f\n", d1);
  
  double d2 = pow(2.0, -20.0) * d1;
  printf("d2 == %f\n", d2);
  
  double d3 = 9.54 * pow(10.0, -8.0);
  printf("d3 == %f\n", d3);
  
  printf("\n");
  
  /* second printf statements */
  if (d1 == d2) printf("d1 == d2\n");
  else printf("d1 != d2\n");
  
  if (d1 == d3) printf("d1 == d3\n");
  else printf("d1 != d3\n");
  
  if (d2 == d3) printf("d2 == d3\n");
  else printf("d2 != d3\n");

  show_bytesBE("d2", (unsigned char*) &d2, sizeof(double));
  show_bytesBE("d3", (unsigned char*) &d3, sizeof(double));
  
  return 0;
}
