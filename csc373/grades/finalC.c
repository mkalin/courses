#include <stdio.h>

unsigned int bar(unsigned int n) {
  /* sizeof(unsigned int) == 4 */
  printf("sizeof(unsigned int) == %u\n",
	 sizeof(unsigned int));
  unsigned char* ptr = (unsigned char*) &n;
  unsigned char t1 = *(ptr + sizeof(unsigned int) - 1);
  unsigned char t2 = *(ptr + 1);
  *(ptr + sizeof(unsigned int) - 1) = t2;
  *(ptr + 1) = t1;
  return n;
}

int main() {

  unsigned int k = 0xff11aa22;
  printf("k in hex == %x\n", k);  /* output: k in hex == ff11aa22 */
  unsigned int r = bar(k);
  printf("r in hex == %x\n", r);

  return 0;
}
