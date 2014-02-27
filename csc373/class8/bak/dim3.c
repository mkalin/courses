#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define D1 (3)
#define D2 (2)
#define D3 (3)
#define UB (100)

/* Output from a sample run:

     24 9 24 98 39 21 29 56 59 21 86 6 76 93 44 21 37 58 
*/


/* Explain, in words and/or pictures, how this loop works. 
   The syntax is correct and the loop does what it should.

   Why does the compiler need D2 and D3 in the argument
   but not D1?
*/
void dump_array(int a[][D2][D3]) {
  int i, j, k;
  for (i = 0; i < D1; i++)
    for (j = 0; j < D2; j++)
      for (k = 0; k < D3; k++)
      printf("%i ", a[i][j][k]);
  printf("\n");
}

int main() {
  /* Uncomment the next line if you'd prefer different output every time. */
  /* srand(time(0)); */

  int d3[D1][D2][D3];

  /* 
     What is the data type of d3?
     What is the data type of *d3?
     What is the data type of **d3?
     What is the data type of ***d3?

     What is the data type of ptr?
  */
  int* ptr = (int*) d3;

  /* 
     Your compiler should not issue any warning/error on the line above.
     What not?

     What if the line changes to:

     int* ptr = d3;

     What happens then with the compiler and why?
  */

  
  int n =  D1 * D2 * D3 * sizeof(int) - sizeof(int);

  /* What does this line do? In particular, why is d3 cast to an int? */
  /* Why, in the initialization of n above, do I subtract sizeof(int) at the end? */
  int* foo = (int*) ((int) d3 + n);

  /* Explain, in words and/or pictures, what this loop does. */
  while (foo > ptr) {
    *foo = rand() % UB; /* generate and assign a 1-digit or 2-digit integer */
    foo--;              /* Explain in words or pictures what's going on here. */
  }
  
  dump_array(d3); /* Could I call dump_array(ptr) here? Explain. */

  return 0;
}
