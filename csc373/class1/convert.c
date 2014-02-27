#include <stdio.h>

/* Convert command-line arguments from decimal to hexidecimal */
/* Sample invocation: convert 26 -9 44 3 11 -15 */
int main(int argc, char* argv[]) {
  /* usage check */
  if (argc < 2) {
    printf("Invoke as: convert [one or more decimal integers]\n");
    return -1;  /* negative integer signals abnormal termination */
  }

  int i = 1;         /* 1 because argv[0] is the program's name */
  while (i < argc) { /* argc is the number of command-line arguments */
    int next;
    sscanf(argv[i++], "%d", &next);
    if (i == 2) printf("%d resides at address %u\n", next, &next);
    printf("Decimal: %d   Hex: %x\n", next, next);
  }

  /* Now print out 10 through 20 in decimal/hex and their negatives */
  for (i = 0; i <= 20; i++) {
    printf("Decimal: %d   Hex: %x\n", i, i);
    printf("Decimal: %d   Hex: %x\n", -i, -i);
  }

  /* Now subtract y from x assuming an underlying 2's complement 
     implementation of integers */
  int x = 7, y = 5;       /* x in binary is 0111 and y is 0101 */
  y = ~y;                 /* 1's complement of y is 1010 */
  y += 1;                 /* increment y: in binary, 1011 */
  printf("2's complemented y is %d\n", y);

  int ans = x + y;  /* x + y is 0111 + 1011 is 0010, 2 in decimal */
  printf("%d - %d is %d\n", x, y, ans); 

  /* Changing signs at the 2's complement level */
  printf("\n");
  int n = 7;   /* 00...111 */
  n = ~n;      /* 11...000 */
  n += 1;      /* 11...001 */
  printf("n = 7; n = ~n; n += 1; ===> %d\n", n); /* -7 */
  n = ~n;      /* 00...110 */
  n += 1;      /* 00...111 */
  printf("Again ===> %d\n", n ); /* 7 */

  return 0;
}
