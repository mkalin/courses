#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M  (5)
#define N  (4)

/* sumTable1 has good "spatial locality" because the access order
   is the same as the memory layout, that is, "row major" order.
*/
int sumTable1(int a[M][N]) {
  int i, j, sum = 0;
  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      sum += a[i][j];
  return sum;
}

/* sumTable2 has poor spatial locality because the access order
   is "column major," which is not the memory layout 
*/
int sumTable2(int a[M][N]) {
  int i, j, sum = 0;
  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
      sum += a[j][i];
  return sum;
}

int my_rand() {
  return rand() % 100;
}

int main() {
  int array[M][N];

  srand(time(0));  /* seed the random number generator */

  /* populate array with random ints */
  int i, j;
  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      array[i][j] = my_rand();

  printf("Sum from sumTable1 is %i\n", sumTable1(array));
  printf("Sum from sumTable2 is %i\n", sumTable2(array));
  return 0;
}
/* output from sample run:

   Sum from sumTable1 is 991
   Sum from sumTable2 is 991
*/
