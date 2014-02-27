 /* This program uses the pow function, which is part of the run-time
    math library. To enable its use, this file (math.c) was
    compiled/linked as follows:

             gcc -o math -lm math.c

        In "-lm", that's a lowercase L rather than a one.
 */

#include <stdio.h>
#include <math.h>

int main() {
  printf("2**9 is %f\n", pow(2.0, 9.0));
  
  return 0;
}
