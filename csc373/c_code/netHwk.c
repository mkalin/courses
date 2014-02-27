#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <netinet/in.h>

void show_bytesBE(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = how_many - 1; i >= 0; i--) printf(" %.2x", ptr[i]);
  printf("\n");
}

/* ???
   This array is an "extern" rather than a stack variable in C; that is,
   storage for this buffer is not allocated on the stack but rather in
   the text area. 
   The question is: Why isn't just a local variable in prompt_and_read? 
*/
char buffer[1024];                /* buffer to hold input string */

unsigned int m1 = UINT_MAX - 15;  /* ??? */

/* Prompt for and read the next input from the standard input. */
char* prompt_and_read() {  
  printf("\nAddress in dotted decimal (or -1 to exit): ");
  scanf("%s", buffer);
  return buffer;
}

/* ??? */
int get_p1(unsigned int n) {
  return n | m1;
}

/* ??? */
int get_p2(unsigned int n) {

  unsigned int ret_val;
  return 0;
}

int main() {
  /* Loop indefinitely */
  while (1) {
    char* next = prompt_and_read();                /* get next input */
    unsigned int next_int = (unsigned) atoi(next); /* convert string to number */
    if ((int) next_int < 0) break;

    unsigned int p1 = get_p1(next_int);
    show_bytesBE("p1", (unsigned char*) &p1, sizeof(unsigned));
    unsigned int p2 = get_p2(next_int);
  }

  return 0;
}
