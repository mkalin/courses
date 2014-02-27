#include <stdio.h>

int main() {
  int table[3][2] = { {1, 2}, {3, 4}, {5, 6} };

  int i, j;
  for (i = 0; i < 3; i++) {
    printf("Address of indexed row %i is %p\n", 
	   i, table[i]);
    for (j = 0; j < 2; j++) {
      printf("Address of indexed col % in row %i is %p\n", 
	     j, i, &table[i][j]);
      printf("\tContent is %i\n", table[i][j]);
    }      
  }
  return 0;
}
/* output from sample run:
Address of indexed row 0 is 0xbfe9ca60
Address of indexed col  0n row 0 is 0xbfe9ca60
        Content is 1
Address of indexed col  1n row 0 is 0xbfe9ca64
        Content is 2
Address of indexed row 1 is 0xbfe9ca68
Address of indexed col  0n row 1 is 0xbfe9ca68
        Content is 3
Address of indexed col  1n row 1 is 0xbfe9ca6c
        Content is 4
Address of indexed row 2 is 0xbfe9ca70
Address of indexed col  0n row 2 is 0xbfe9ca70
        Content is 5
Address of indexed col  1n row 2 is 0xbfe9ca74
        Content is 6
*/
