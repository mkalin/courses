#include <stdio.h>
#include <stdlib.h>

#define HowMany  (16)
#define Mod     (100)

void dump(const char* msg, int a[], unsigned len) {
  printf("%s\n", msg);

  unsigned i;
  for (i = 0; i < len; i++) printf("%i ", a[i]);
  printf("\n");
}

/* Assumed semantics for returned value:
   
   0   -- the compared values are equal
   < 0 -- the first precedes the second
   > 0 -- the second precedes the first
 */
int comp(const void* p1, const void* p2) {
  /* for clarity, break down casting/dereferncing */
  const int* pp1 = (const int*) p1;
  const int* pp2 = (const int*) p2;
  int n1 = *pp1;
  int n2 = *pp2;

  /* sort in ascending order: reverse to sort
     in descending order
  */
  return n1 - n2; 
}

int main() {
  /* seed random number generator with current time */
  srand(time(0)); 
  
  /* populate array with random ints */
  int a[HowMany];
  unsigned i;
  for (i = 0; i < HowMany; i++) a[i] = rand() % Mod;
  dump("Unsorted:", a, HowMany);

  /* sort and dump again */
  qsort(a,           /* array to sort */
	HowMany,     /* length */
	sizeof(int), /* sizeof each element */
	comp);       /* pointer to comparision function */
  dump("\nSorted:", a, HowMany);

  /* binary-search array, which must be sorted in ascending order */
  int key = rand(); /* generate a random key */
  int* result = (int*) bsearch(&key,         /* key */
			       a,            /* array */
			       HowMany,      /* length */
			       sizeof(int),  /* element size */
			       comp);        /* comparer */
  if (result) printf("\n%i found in array.\n", key);
  else printf("\n%i not found in array.\n", key);

  /* ensure a key that's in the array */
  key = a[2];
  result = (int*) bsearch(&key,         /* key */
			  a,            /* array */
			  HowMany,      /* length */
			  sizeof(int),  /* element size */
			  comp);        /* comparer */
  if (result) printf("\n%i found in array.\n", key);
  else printf("\n%i not found in array.\n", key);
  
  return 0;
}
/* output:

   Unsorted:
   15 5 45 43 95 68 1 8 89 70 10 88 61 26 46 78 

   Sorted:
   1 5 8 10 15 26 43 45 46 61 68 70 78 88 89 95 
   
   1212608186 not found in array.
   
   8 found in array.
*/
