#include <stdio.h>

int main() {
  int n = 0xabcdef12;               /* 0x means "hex" */
  printf("n in decimal: %d\n", n);  /* -1,412,567,278 */

  printf("%p\n", &n); /* print n's address: 0xbffa1f74 */

  printf("n contains %d bytes.\n", sizeof(n)); /* n's size in bytes: 4 */

  /* store n's address in ptr but cast the address to that of
     a char (1 byte) rather than of an int (4 bytes) */
  unsigned char* ptr = (unsigned char*) &n;
  int i;

  /* Run onn an Intel machine, which is little endian */
  for (i = 0; i < sizeof(int); i++)
    printf("%.2x ", ptr[i]);        /* 12 ef cd ab */
  printf("\n");

  /* in "reverse" order */
  unsigned char* last = ptr + sizeof(int) - 1; 
  while (last >= ptr)               /* ab cd ef 12 */
    printf("%.2x ", *last--); 
  printf("\n");
  
  return 0;
}
