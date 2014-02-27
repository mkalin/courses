#include <stdlib.h>
#include <stdio.h>

int main() {
  char* strings[ ] = { "foo", "bar", "baz", -1 };
  int i = 0;
  while (strings[i] != NULL)
    printf("%s\n", strings[i++]);
  return 0;
}
