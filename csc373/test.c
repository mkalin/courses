#include <stdlib.h>
#include <stdio.h>

unsigned ran(unsigned k) {
  unsigned n = rand();
  printf("rand() = %u\nRAND_MAX = %u\nRAND_MAX + 1.0 = %f\n", n, RAND_MAX, (RAND_MAX + 1.0));

  return 1 + n * (k / (RAND_MAX + 1.0));
}

int main() {
  int i = 0;
  while (i++ < 7)
    printf("%u\n", ran(20));

  return 0;
}
