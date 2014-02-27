#include <stdio.h>
#include <stdlib.h>

void dump(int** array, int rows, int cols) {
  int i, j;
  for (i = 0; i < rows; i++) {
    printf("\n");
    int j;
    for (j = 0; j < cols; j++)
      printf("%i ", array[i][j]);
  }
  printf("\n");
}

void f1(int** arg, int n1, int n2) {
  int i;
  for (i = 0; i < n1; i++) {
    int j;
    for (j = 0; j < n2; j++)
      *(*(arg + i) + j) = rand() % 100;
  }
}

int** f2(int** arg, int n) {
  int** t = malloc(n * sizeof(int*));
  int i, k = 0;
  for (i = n - 1; i >= 0; i--)
    t[k++] = arg[i];
  
  return t;
}

int main() {
  int n = 0xffffffff;

  do {
    printf("Enter a positive integer: ");
    scanf("%i", &n);
  } while (n < 0);
  
  /* Create an N x N matrix using heap storage */
  int** q = malloc(n * sizeof(int*));
  
  int i;
  for (i = 0; i < n; i++)
    *(q + i) = malloc(n * sizeof(int));

  /* Fill the matrix with randomly generated integers */
  f1(q, n, n);

  dump(q, n, n);

  /* Create a new N x N matrix with the rows in reverse order
     of the rows in the argument matrix: the last row becomes
     the first, and so on. */
  int** r = f2(q, n);

  dump(r, n, n);
  
  for (i = 0; i < n; i++)
    free(*(q + i));
  free(q);

  return 0;
}
/* output from sample run:


Enter a positive integer: 4

83 86 77 15 
93 35 86 92 
49 21 62 27 
90 59 63 26 

90 59 63 26 
49 21 62 27 
93 35 86 92 
83 86 77 15 
*/
