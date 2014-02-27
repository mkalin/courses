#include <stdio.h>


void loop() {
  while (1) {
    printf("Hello, world!\n");
  }
}

void recur() {
  if (1) recur();
  printf("Hello, world!\n");
}


void f(unsigned int x) {
  unsigned int i = 0;
  while (i <= x) {
    printf("hi\n");
    i = i - 1;
  }
  printf("bye\n");
}

int main() {
  f(8);

  recur();
  /* loop(); */
  return 0;
}
