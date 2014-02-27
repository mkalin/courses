#include <stdio.h>

int by_val(int n, int m) { 
  n += 1; /* arg changed, not original */
  m -= 1; /* ditto */
  return n * m;
}

int by_ptr(int* n, int* m) {
  *n += 1; /* original changed */
  *m -= 1; /* ditto */
  return *n * *m;
}

int by_ptr_ptr(int** p1, int** p2) {
  int n1 = **p1;
  int n2 = **p2;
  return (n1 + 1) * (n2 - 1);
}

void dump(int a1, int a2, int a3) {
  printf("1st num: %i\n2nd num: %i\n3rd num: %i\n",
	 a1, a2, a3);
}

void dump_array(const int* p, unsigned len) {
  unsigned i;
  for (i = 0; i < len; i++) printf("%i ", p[i]);
  printf("\n");
}

typedef struct Emp {
  char     fname[40 + 1];
  char     lname[40 + 1];
  char     dept[20 + 1];
  float    sal;
  char     address[120 + 1];
  char     boss[40 + 1];
  unsigned married;
} Emp;

void pass_struct1(Emp e) { /* terrible */
  /* sizeof(Emp) == sizeof(e) */
  printf("%lu bytes passed to pass_struct1...\n", sizeof(e));
}

void pass_struct2(Emp* e) { /* now we're talking */
  printf("%lu bytes passed to pass_struct2...\n", sizeof(e));
}

int main() {
  int n = 27, m = 10;
  int r = by_val(n, m);
  dump(n, m, r);
  printf("\n");

  r = by_ptr(&n, &m);
  dump(n, m, r);
  printf("\n");

  /* what you can't do in Java */
  int *p = &n;
  int *q = &m;
  r = by_ptr_ptr(&p, &q);
  dump(n, m, r);
  printf("\n");

  /* arrays take care of themselves */
  unsigned array[ ] = {1, 2, 3, 4};
  dump_array(array, 4); /* address of array[0] is passed as argument */
  printf("\n");

  Emp e;
  pass_struct1(e);
  pass_struct2(&e);
  
  return 0;
}
/* Output:
1st num: 27
2nd num: 10
3rd num: 252

1st num: 28
2nd num: 9
3rd num: 252

1st num: 28
2nd num: 9
3rd num: 232

1 2 3 4 

276 bytes passed to pass_struct1...
8 bytes passed to pass_struct2...
 */
