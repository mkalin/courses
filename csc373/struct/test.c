#include <stdio.h>

int main() {
  if ('\0') printf("yes\n");
  if ('\0' == 0) printf("yep\n");
  return 0;
}
