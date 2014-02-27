#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Mod (100) /* limit numbers to small ones */

/* print the contents of a 3-dimensional int array */
void dump(int a[][2][3]) {
  int i, j, k;
  for (i = 0; i < 3; i++) {
    printf("\n");
    for (j = 0; j < 2; j++) {
      printf("\n");
      for (k = 0; k < 3; k++)
	printf("%i ", a[i][j][k]);
    }
  }	
  printf("\n");
}

int main() {
  /* If you want always to get the same numbers,
     comment out the next line.

     If you want different numbers each time,
     leave the next line as is.
  */
  srand(time(0)); /* seed the random number generator */

  int array3[3][2][3];
  int i, j, k;

  /* fill the 3-dimensional array with random numbers */
  for (i = 0; i < 3; i++)
    for (j = 0; j < 2; j++)
      for (k = 0; k < 3; k++)
	array3[i][j][k] = rand() % Mod;

  /* print out the array */
  dump(array3);
  
  return 0;
}
