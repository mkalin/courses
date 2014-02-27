#include <stdio.h>
#include <limits.h>

void show_bytes(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = 0; i < how_many; i++) printf(" %.2x", ptr[i]);
  printf("\n");
}

int main() {
  unsigned n = 0;
  show_bytes("n == 0", (unsigned char*) &n, sizeof(unsigned));

  unsigned k = n - 1;

  show_bytes("k = n - 1", (unsigned char*) &k, sizeof(unsigned));

  k = UINT_MAX;
  show_bytes("UINT_MAX", (unsigned char*) &k, sizeof(unsigned));

  int r = -1;
  show_bytes("-1", (unsigned char*) &r, sizeof(unsigned));
  return 0;
}
/* Output (formatted for readability)

n == 0: 00 00 00 00

k = n - 1: ff ff ff ff (recall that n - 1 == n + -1)

UINT_MAX: ff ff ff ff

-1:       ff ff ff ff
*/
