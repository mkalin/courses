/* Exercise 1:
   
   This program populates a 3-dimensional array with randomly generated
   integers and prints them out.

   The exercise is to write the code that treats the 3-dimensional array 
   as if it were a 1-dimensional array, which is how the system actually
   stores the array. Your code should print the array out twice: left to
   right and right to left, that is, in regular order and then in reverse
   order. For example, if the 10 is the first number and 87 is the last,
   one print out would be

   10,...,87

   and the other would be

   87,...,10

   In treating the 3-dimensional array as a 1-dimensional array, you won't
   need nested loops of the sort that I have in the function dump. Your
   code will look more like

   for (...)
      printf("%i ",...);

   You're free to use a while loop if you prefer, of course. The key thing
   is that your two print outs won't require nested loops.

 */

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

  /* treat as 1-dimensional */
  unsigned len = 3 * 2 * 3; /* sizes of each dimension given above */
  int* front = (int*) array3;
  int* back = front + len - 1; /* pointer arithmetic */
  int* p = front;
  printf("Front to back:\n");
  while (p <= back) printf("%i ", *p++);
  printf("\nBack to front:\n");
  p = back;
  while (p >= front) printf("%i ", *p--);
  printf("\n");
  

  int *foobar = &array3[0][0][0];


  int *ptr = &(array3[0][0][0]);
  i = 0;
  while (i < 3*2*3)
  {
	printf("%i ", *ptr++);
	i++;
  }
  printf("\n");
  
  /*print array as if it were a one dimensional array backwards*/
  printf("printing 3-dimensional array as a 1-dimensional array backwards.");
  printf("\n");
  ptr = &(array3[2][1][2]);
  i = 3*2*3 -1;
  while (i >= 0)
  {
    printf("%i ", *ptr--);
    i--;
  }
  printf("\n");

  
  return 0;
}
