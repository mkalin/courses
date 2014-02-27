/* output from this program:
   
   foo
   bar
   baz
*/
#include <stdlib.h>
#include <stdio.h>

int main() {
  char* strings[ ] = { "foo", "bar", "baz", NULL };
  int i = 0;
  while (strings[i] != NULL)
    printf("%s\n", strings[i++]);
  return 0;
}
