#include <stdio.h>

#define Size1 (4)
#define Size2 (3)
#define Size3 (5)

int main() {
  int* a1 = malloc(4 * sizeof(int));
  int* a2 = malloc(3 * sizeof(int));
  int* a3 = malloc(5 * sizeof(int));
  a1[0] = 1; a1[1] = 2; a1[2] = 3; a1[3] = 4;
  a2[0] = 9; a2[1] = 8; a2[3] = 7;
  a3[0] = -1; a3[1] = -2; a3[2] = -3; a3[3] = -4; a3[4] = -5;

  int sizes[ ] = {Size1, Size2, Size3, 0};

  int** ptr2ptr = malloc(sizeof(int*) * 4);
  ptr2ptr[0] = a1;
  ptr2ptr[1] = a2;
  ptr2ptr[2] = a3;
  ptr2ptr[3] = 0;

  int i = 0;
  while (ptr2ptr[i]) {
    int j;
    for (j = 0; j < sizes[i]; j++)
      printf("%i ", ptr2ptr[i][j]);
    printf("\n");
    i++;
  }
  return 0;
}
