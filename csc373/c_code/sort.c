#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N (16)

unsigned fib_recur(unsigned n) {
  if (n < 2) return n;
  return fib_recur(n - 1) + fib_recur(n - 2);
}

unsigned fib_iter(unsigned n) {
  if (n < 2) return n;
  unsigned fib = 1, prev = 0;
  unsigned i = 0;
  for (i = 2; i <= n; i++) {
    unsigned temp = fib;
    fib += prev;
    prev = temp;
  }
  return fib;
}

void do_fib() {
  printf("\n");
  unsigned n1 = fib_recur(25); 
  printf("fib(25) is %d\n", n1); /* 75,025 */
  
  unsigned n2 = fib_iter(100);
  /* if (n1 != n2) fprintf(stderr, "What!\n"); */
  printf("%u\n", n2);
}

void print(int a[ ], int len) {
  int i;
  printf("\n");
  for (i = 0; i < len; i++) printf("%d ", a[i]);
}

int my_rand() { return rand() % 200; }

int comp(const void* p1, const void* p2) {
  return *((int*) p2) - *((int*) p1);
}

int main() {
  int a[N];
  srand(time(0)); 
  int i;
  for (i = 0; i < N; i++) a[i] = my_rand();
  print(a, N);

  qsort(a, N, sizeof(int), comp);
  print(a, N);

  do_fib();  
  return -1;
}

/* Output from sample run, slightly formatted for readability:
     183  60  97 147  74  95 185 135 101 110 116 30 165 143 188 181
     188 185 183 181 165 147 143 135 116 110 101 97  95  74  60  30
*/
