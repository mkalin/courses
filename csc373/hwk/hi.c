#include <stdio.h>

/* global variables: shared among all calls to all functions 
   in this file.
*/
char* greeting_pieces[ ] = {"Hello", ",", " world", "!"};
/* int state = 4; number of strings in array greeting_pieces */

int main() {
  int state = 4;
  if (--state < 0) return 0;        /* decrement status & return to invoker */

  int i = state;                    /* make a local copy of status */

  main();                           /* recursively invoke main */
  printf("%s", greeting_pieces[i]); /* print your greeting piece */

  return 0;
}
