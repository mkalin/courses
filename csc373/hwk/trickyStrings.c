#include <string.h>
#include <stdio.h>

#define MAX_STRING (500)

int main() {
  const char* g1 = "Hello, world!";
  const char* g2 = "Goodbye, cruel world?";

  char s[MAX_STRING + 1];

  /* Document in as much detail as you can. At the least, please
     explain:
     
     1. What is the data type of str_stuff?
     2. What do the function calls labeled A, B, and C do?
     3. Pick one of A, B, or C and explain the syntax in detail.

  */
  char* (*str_stuff[ ])(char*, const char*) = {strcat, strcpy, strtok}; 
  
  str_stuff[1](s, g1);   /* A */
  str_stuff[0](s, g2);   /* B */
  str_stuff[2](s, ",");  /* C */

  return 0;
}
