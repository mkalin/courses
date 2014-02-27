#include <stdio.h>
#include <limits.h>

int main() {
  unsigned m = UINT_MAX;
  unsigned n = m;
  
  printf("m = %u\n", m);
  printf("n = %u\n", n);
  printf("m + n = %u\n", m + n);

  return 0;
}

/* Output (formatted for readability):

m     = 4,294,967,295
n     =             1
m + n =             0

*/
