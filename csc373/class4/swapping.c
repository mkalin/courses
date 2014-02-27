#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE (16)

/*
  This program can be compiled and executed in the usual way.
  The function main is documented but the function swap is not.
  Document swap in two ways:
   -- Explain what it does in general.
   -- Document each line within the for loop.

  Don't change any of my code but feel free to add any code that 
  you like.
 */
void swap(int* p1, int* p2) {
  int i;
  for (i = 0; i < SIZE; i++) {
    int n = *p1;
    *p1 = *p2;
    *p2 = n;
    p1++;
    p2--;
  }
}

void dump(char* msg, int* a) {
  printf("%s\n", msg);
  int i;
  for (i = 0; i < SIZE; i++)
    printf(" %i", a[i]);
}

int main() {
  srand(time(0));
  int a1[SIZE];
  int a2[SIZE];
  int i;
  
  /* Populate arrays. */
  for (i = 0; i < SIZE; i++) {
    a1[i] = rand() % 100;
    a2[i] = rand() % 100;
  }
  dump("\na1 before:", a1);
  dump("\na2 before:", a2);
  /* Do a swap. */
  swap(a1, a2 + SIZE - 1);
  printf("\n");
  dump("\na1 after:", a1);
  dump("\na2 after:", a2);
  printf("\n");
  return 0;
}
