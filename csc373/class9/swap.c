#include <stdio.h>
#include <limits.h>

void print_per(unsigned char);

void show_bytesBE(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = how_many - 1; i >= 0; i--) printf(" %.2x", ptr[i]);
  printf("\n");
}

void mystery(int* p1, int* p2) {
  *p1 = *p1 + *p2;
  *p2 = *p1 - *p2;
  *p1 = *p1 - *p2;
}

int main() {
  /* mystery function call */
  int n = 2, m = 7;
  printf("n == %i\tm == %i\n", n, m);
  mystery(&n, &m);
  printf("n == %i\tm == %i\n", n, m);

  /* some float stuff */
  float f = 0.0;                /*  0.0:   07 00 00 00 00 */
  show_bytesBE("0.0:", (unsigned char*) &f, sizeof(float)); 
  f = -f;                       /*   -f:   80 00 00 00 */
  show_bytesBE("-f:", (unsigned char*) &f, sizeof(float)); 

  printf("f == %f\t-f == %f\n", 
	 f, -f);                /* f == -0.000000  -f == 0.000000 */

  f = (float) (((int) f) << 1); /* f << 1: 00 00 00 00 */
  show_bytesBE("f << 1:", (unsigned char*) &f, sizeof(float));

  /* playing with pointers */
  int k = 0xabcdef12;         /* k: ab cd ef 12 */
  show_bytesBE("k:", (unsigned char*) &k, sizeof(int));
  short* ptr;   /* sizeof(short) == 2, sizeof(int) == 4 */
  ptr = (short*) &k;
  short t = *ptr;
  show_bytesBE("t:", (unsigned char*) &t, sizeof(short)); /* ? */
  *ptr = *(ptr + 1);
  *(ptr + 1) = t;
  show_bytesBE("k:", (unsigned char*) &k, sizeof(int));   /* ? */

  /* output? */
  int array[ ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -2 };
  int* int_ptr = array;
  while (*int_ptr >= 0) {
    printf("%i ", *int_ptr);
    int_ptr += 2;
  }
  printf("\n");

  unsigned char r   = 1;
  unsigned char w   = 2;
  unsigned char rw  = r | w;
  unsigned char e   = 4;
  unsigned char rwe = rw | e;

  printf("r == %i\nw == %i\nrw == %i\ne == %i\nrwe == %i\n",
	 r, w, rw, e, rwe);
  int i;
  for (i = 0; i < 10; i++)
    print_per(i);

  /* little more at the bit level */
  unsigned char big = UCHAR_MAX;
  signed char small = SCHAR_MIN;
  show_bytesBE("big:", &big, 
	       sizeof(char ));         /* ff ==> 11111111 */
  show_bytesBE("small:", (unsigned char*) 
	       &small, sizeof(char));  /* 80 ==> 10000000 */

  unsigned char xor = big ^ small;
  show_bytesBE("xor:", &xor, 
	       sizeof(char));          /* 7f ==> 01111111 */
  unsigned char or = big | small;
  show_bytesBE("or:", &or, 
	       sizeof(char));          /* ff ==> 11111111 */

  /* the problem with doubles: in C or Java on an IA32 machine 
        -- register and memory access is at the 32-bit level
	-- think multithreading
  */
  printf("sizeof double is %d\n", sizeof(double)); /* 8 */
  
  return 0;
}

void print_per(unsigned char n) {
  switch (n) {
  case 1:
    printf("1 ==> Read\n");
    break;
  case 2:
    printf("2 ==> Write\n");
    break;
  case 3:
    printf("3 ==> Read/write\n");
    break;
  case 4:
    printf("4 ==> Execute\n");
    break;
  case 7:
    printf("7 ==> Read/write/execute\n");
    break;
  default:
    printf("%i ==> No such permission.\n", n);
  }
}
