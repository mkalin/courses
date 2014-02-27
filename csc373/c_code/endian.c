/** Excecuted on an Intel PC with Linux **/

#include <stdio.h>

void show_bytes(char*, unsigned char*, int);

int main() {

  int n;
  /* store address of n in ptr_to_n, which then "points to" n */
  unsigned char* ptr_to_n = (unsigned char*) &n;
 
  /* first, some small ints */
  n = 9;
  show_bytes("int", ptr_to_n, sizeof(int));      /* 09 00 00 00 */

  n = 17;                                        /* 11 00 00 00 */
  show_bytes("int", ptr_to_n, sizeof(int));

  /* 12,345 is 00110000 00111001 in binary and 3039 in hex */
  n = 12345;
  show_bytes("int", ptr_to_n, sizeof(int));       /* 39 30 00 00 */

  float f = 12345.0;
  ptr_to_n = (unsigned char*) &f;
  show_bytes("float", ptr_to_n, sizeof(float));   /* 00 e4 40 46 */

  double d = 12345.0;
  ptr_to_n = (unsigned char*) &d;
  show_bytes("double", ptr_to_n, sizeof(double)); /* 00 00 00 00 80 1c c8 40 */

  d = 3.1415;
  ptr_to_n = (unsigned char*) &d;
  show_bytes("double", ptr_to_n, sizeof(double)); /* 6f 12 83 c0 ca 21 09 40 */
  
  f = 3.1415;
  ptr_to_n = (unsigned char*) &f;
  show_bytes("float", ptr_to_n, sizeof(float));   /* 56 0e 49 40 */

  show_bytes("void*", (unsigned char*) &ptr_to_n, /* 2c 4b fc bf */
             sizeof(void*)); 

  return 0;
}

void show_bytes(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  /* The 2nd argument to printf, ptr[i], could be rewritten in
     two ways:
                 i[ptr]
                 *ptr++

     Quick exercise: Why does the first work?

     Quick explanation of *ptr++: The ++ associates with ptr, not
       with *ptr; so ptr++ increments ptr by the sizeof of whatever
       ptr points to, which is a char == 8 bits. The * operator
       dereferences the pointer, that is, gets the value pointed to.
       So *ptr++ first gets the value to which ptr currently points
       and then increments ptr by one char (8 bits).                     
  */
  for (i = 0; i < how_many; i++) printf(" %.2x", ptr[i]);
  printf("\n");

}
