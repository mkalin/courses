#include <stdio.h>
#include <limits.h>

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

void f(unsigned int x) {
  unsigned int i = 0;
  while (i <= x) {
    printf("hi\n");
    i = i - 1;
  }
  printf("bye\n");
}

int main() {
  /*
  unsigned k = 0xff11aa22;
  printf("%x\n", bar(k));
  k = 0xaabbeeff;
  printf("%x\n", bar(k));

  printf("%i\n", 9 + 0x1238);
  */
  f(4); f(8); f(UINT_MAX);

  return 0;
}
