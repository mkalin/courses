/* stack.c */
#include <stdio.h>

/* global variables: shared among all calls to all functions 
   in this file.
*/
char* greeting_pieces[ ] = {"Hello", ",", " world", "!"};
int state = 4; /* number of strings in array greeting_pieces */

int main() {
  if (--state < 0) return 0;        /* decrement status and return to invoker */
  int i = state;                    /* make a local copy of status */
  main();                           /* recursively invoke main */
  printf("%s", greeting_pieces[i]); /* print your greeting piece */
  return 0;
}
/* Symbolic trace: current value of state is shown as an argument to main
   for trace purposes. In fact, state is a global variable that tracks the
   state of the application.

   main(4) 
      i = 3
      invoke main(3)
         i = 2
         invoke main(2)
            i = 1
            invoke main(1)
               i = 0
               invoke main(0)
               return to main(1) because state is now -1 (return from the if)
            print greeting_pieces[0]
            return to main(2) (return at the end of main)
         print greeting_pieces[1]
         return to main(3) (return at the end of main)
      print greeting_pieces[2]
      return to main(4) (return at the end of main)
   print greeting_pieces[3]
   return to system (return at the end of main)
*/
