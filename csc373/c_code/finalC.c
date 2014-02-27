#include <stdio.h>


/* the operator % is the C modulus operator, which returns a
   remainder. For instance, 

                0 % 3 == 0
                1 % 3 == 1
                2 % 3 == 2
                3 % 3 == 0
                4 % 3 == 1
                ...

   the operator && is the boolean AND operator
*/

int comp(const void* p1, const void* p2) {
  const int* ptr1 = (const int*) p1;
  const int* ptr2 = (const int*) p2;

  if (*ptr1 % 2 == 0 && *ptr2 % 2 == 0) return 0;
  else return *ptr2 - *ptr1;
}

void dump(int a[ ], int n) {
  int i;
  for (i = 0; i < 9; i++) printf("%i ", a[i]);
  printf("\n");
}

int main() {
  int a[ ] = {9, 4, 3, 7, 1, 8, 6, 2, 5};
  dump(a, 9);

  qsort(a, 9, sizeof(int), comp);
  dump(a, 9);
 
  return 0;
}
/* Here's the output:

    9 4 3 7 1 8 6 2 5
    9 8 7 4 6 5 3 2 1

   Explain how this output results from the qsort. Be as specific
   as possible. Hint: Start by carefully documenting qsort.
*/
