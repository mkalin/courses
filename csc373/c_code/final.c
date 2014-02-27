#include <stdio.h>
#include <limits.h>

void show_bytes(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = 0; i < how_many; i++) printf(" %.2x", ptr[i]);
  printf("\n");
}

int mystery(int n1, int n2) {
  unsigned char* ptr1 = (unsigned char*) &n1;
  unsigned char* ptr2 = (unsigned char*) &n2;

  int ret_val;
  unsigned char* ptr3 = (unsigned char*) &ret_val;

  ptr2 += sizeof(int) - 1;
  ptr3 += sizeof(int) - 1;

  int i;
  for (i = 0; i < sizeof(int); i++) {
    *ptr3 = *ptr2;
    ptr3--;
    ptr2--;
  }
  
  ptr3++;
  *ptr3 = *ptr1;

  return ret_val;
}

int main() {
  /*
  int a1 = 162254319;
  int a2 = 1985229328;
  printf("Before: %x\n", a2);

  int ans = mystery(a1, a2);
  printf("After:  %x\n", ans);
  */
  int x = 0x12345678;
  printf("%d\n%f\n%f\n", 
	 x, (float) x, (float) ((x << 4) - x));
  /* output:

     305419896 
     305419896.000000 
     286331144.000000
  */

  return 0;
}
