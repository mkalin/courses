#include <stdio.h>
#include <limits.h>

/* show_bytes is now defined above main so that the definition
   also counts as a declaration 
*/
void show_bytes(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = 0; i < how_many; i++) printf(" %.2x", ptr[i]);
  printf("\n");
}

int left_right1(unsigned n) {
  return (int) ((n << 24) >> 24);
}

int left_right2(unsigned n) {
  return ((int) n << 24) >> 25;
}

int sum_ints(int array[ ], unsigned length) {
  int i; /* trouble starts here */
  int result = 0;
  
  if (length == 0) printf("0 - 1 in unsigned is %x\n", length - 1);
  if ((unsigned) 0 - (unsigned) 1 == UINT_MAX) printf("Yes!\n");
  /* 0 - 1 is 111...1111 */
  for (i = 0; i <= length - 1; i++)  /* length - 1 brings it home */
    result += array[i];
  return result;
}

int main() {
  /* dangers of mixed integer types */
  unsigned int n1 = 0;
  signed int n2 = -1;
  int n3 = (n1 > n2) ? n1 : n2;
  printf("%d\n", n3); /* -1 is printed */

  /* illustration of constants in limits.h and shifting */
  n1 = 1;          /* n1 is unsigned: 000...001 in binary  */
  int count = 0;  
  while (n1 < INT_MAX) {
    n1 = n1 << 1;  /* left shift one position */
    count++;
  }
  n1 = n1 >> 1;    /* why? */
  /* output is: After 30 1-bit left shifts, n1's value is 1073741824 */
  printf("After %d 1-bit left shifts, n1's value is %d\n", 
	 count - 1, n1);

  /* binary expansions of signed and unsigned types */
  int signed_num = -12345;
  unsigned int unsigned_num = 53191;
  show_bytes("signed int", (unsigned char*) &signed_num, /* c7 cf ff ff */
	     sizeof(int));
  show_bytes("unsigned", (unsigned char*) &unsigned_num, /* c7 cf 00 00 */
	     sizeof(unsigned));

  /* p. 63 in the book: key assumption is that sizeof(int) is 4 == 32 bits */
  printf("left_rigth1(127) => %d  left_right2(127) => %d\n", 
	 left_right1(127), left_right2(127));
  printf("left_right1(128) => %d  left_right2(128) => %d\n", 
	 left_right1(128), left_right2(128));
  printf("left_right1(255) => %d  left_right2(255) => %d\n", 
	 left_right1(255), left_right2(255));
  printf("left_right1(256) => %d  left_right2(256) => %d\n", 
	 left_right1(256), left_right2(256));

  /* more mixed type dangers */
  printf("\n");
  int a[ ] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int sum_a = sum_ints(a, (unsigned) 10);
  printf("Sum of the ints in the array is: %d\n", sum_a);

  int b[0]; /* empty */
  int sum_b = sum_ints(b, (unsigned) 0); /* trouble ends here */

  return 0;
}

