#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N (100)

/* What's good?
   What's bad?
   What's pointless in this example but useful in general?
*/

typedef struct Array {
  int array[N];
} Array;

int sum1(int* a) {
  int sum = 0;
  unsigned i;
  for (i = 0; i < N; i++) sum += *(a + i);

  return sum;
}

int sum2(int** ptr) {
  int sum = 0;
  unsigned i;
  int* a = *ptr;
  for (i = 0; i < N; i++) sum += *(a + i);

  return sum;
}

int sum3(Array a) {
  int sum = 0;
  unsigned i;
  for (i = 0; i < N; i++) sum += a.array[i];

  return sum;
}

int sum4(Array* a) {
  int sum = 0;
  unsigned i;
  for (i = 0; i < N; i++) sum += a->array[i];

  return sum;
}

int main() {
  srand(time(0));

  int array[N];   /* array */
  Array structA;  /* structure with array as member */

  unsigned i;
  for (i = 0; i < N; i++) {
    array[i] = structA.array[i] = rand();
  }
 
  int*  ptr1 = array;
  int** ptr2 = &ptr1;

  int ans1 = sum1(ptr1);      /* same as sum1(array) */
  int ans2 = sum2(ptr2); 
  int ans3 = sum3(structA);
  int ans4 = sum4(&structA);

  printf("The four sums (should be the same):\n");
  printf("sum1: %i\n", ans1);
  printf("sum2: %i\n", ans2);
  printf("sum3: %i\n", ans3);
  printf("sum4: %i\n", ans4);
  return 0;
}
/* 
   The four sums (should be the same):
   sum1: 1878631935
   sum2: 1878631935
   sum3: 1878631935
   sum4: 1878631935
*/
