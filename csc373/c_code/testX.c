#include <stdio.h>
#include <ctype.h> /* for isalpha, which tests whether an character code is
		      for an alphabetic character */

const int n = 60;

/* document */
int comp(const void* v1, const void* v2) {
  return (*(const unsigned char*) v2) - (*(const unsigned char*) v1);
}

/* document */
void dump(unsigned char* p, unsigned int n) {
  unsigned int i;
  for (i = 0; i < n; i++) printf("%c ", p[i]);
  printf("\n");
}

int main() {
  /* 'A' is 65 in either ASCII or Unicode.
     The ASCII codes are, in fact, preserved in Unicode. 
     For the uppercase letters, the codes are consecutive.
  */
  unsigned char c = 'A';
  unsigned int n = 'Z' - 'A' + 1;

  /* these two statements are equivalent to a single calloc
     statement. From the documentation on calloc, figure out
     what the appropriate calloc statement would be and
     replace these two with the appropriate calloc statement. */
  unsigned char* ptr = malloc(2 * n);
  bzero(ptr, n);
  unsigned char* base = ptr;

  /* document from here until the end: give the output as well */
  while (isalpha(c)) 
    *ptr++ = c++;

  unsigned int k = n / 2;
  unsigned char* p1 = malloc(k);
  unsigned char* p2 = malloc(k);
  memcpy(p1, base, k);
  memcpy(p2, base + k, k);
  qsort(p1, k, 1, comp);
  qsort(p2, k, 1, comp);

  dump(p1, k);
  dump(p2, k);

  return 0;
}
