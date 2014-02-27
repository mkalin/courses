#include <stdio.h>

/* Overview

   Consider a recursive definition for the sum of a list of numbers: 
   sum [] = 0
   sum [first:rest] = first + sum(rest)

   A recursive definition for the product of a list of numbers would
   be similar except that the operation would be multiplication 
   rather than addition. 

   Now consider a more general function, reduce, that applies some
   numerical operation (e.g., sum or product) to a list of numbers,
   collects the results of the operations on each list member, and
   returns the appropriate reduced value (e.g., the sum or the product). 
   A function such as reduce is higher-order in that it expects a 
   function as an argument.
 */

unsigned sum(unsigned list[], unsigned len) { 
  unsigned sum = 0;
  unsigned i;
  for (i = 0; i < len; i++) sum += list[i];  
  return sum;
}

unsigned product(unsigned list[], unsigned len) { 
  unsigned product = 1;
  unsigned i;
  for (i = 0; i < len; i++) { product *= list[i]; }
  return product;
}

/* num_op is a pointer to function that takes two
   arguments, an array of integers and the array's
   length, and then returns an integer.
*/
typedef unsigned (*num_op)(unsigned list[], unsigned len);

/* Apply a numeric function to a list of integers. */
unsigned reduce(num_op func, unsigned list[], unsigned len) {
  return func(list, len); 
}

int main() {
  unsigned nums[] = 
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
     11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
     21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

  printf("Sum of list:     %i\n", reduce(sum, nums, 30));
  printf("Product of list: %i\n", reduce(product, nums, 30));
  /* Output:

     Sum of list:     465
     Product of list: 1,409,286,144  ;; commas added
  */  
  return 0;
}
