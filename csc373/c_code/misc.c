#include <stdio.h>
#include <limits.h>

void print_per(unsigned char);

void show_bytesBE(char* msg, unsigned char* ptr, int how_many) {
  printf("%s ==> ", msg);
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
  int n = 2, m = 7; mystery(&n, &m);
  float f = 0.0;                /*  0.0:   00 00 00 00 */
  f = -f;                       /*   -f:   80 00 00 00 */
  f = 129.1;                    /* 43 01 19 9a */
  f = (float) (((int) f) << 1); /* 43 81 00 00 */
  printf("%f\n", f);            /* 258.0 */

  int k = 0xabcdef12;         /* k: ab cd ef 12 */
  show_bytesBE("k:", (unsigned char*) &k, sizeof(int));

  short* ptr;   /* sizeof(short) == 2, sizeof(int) == 4 */
  ptr = (short*) &k;

  short t = *ptr;
  show_bytesBE("t:", (unsigned char*) &t, sizeof(short)); /* ? */

  *ptr = *(ptr + 1);
  *(ptr + 1) = t;

  show_bytesBE("k:", (unsigned char*) &k, sizeof(int));   /* ? */

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
  unsigned char big = UCHAR_MAX; /* ff ==> 11111111 */
  signed char small = SCHAR_MIN; /* 80 ==> 10000000 */

  show_bytesBE("big:", &big, 
	       sizeof(char ));         /* ff ==> 11111111 */

  show_bytesBE("small:", (unsigned char*) 
	       &small, sizeof(char));  /* 80 ==> 10000000 */

  unsigned char xor = big ^ small;/* 7f ==> 01111111 */
  show_bytesBE("xor:", &xor, 
	       sizeof(char));          /* 7f ==> 01111111 */

  unsigned char or = big | small;/* ff ==> 11111111 */
  show_bytesBE("or:", &or, 
	       sizeof(char));          /* ff ==> 11111111 */

  printf("sizeof double is %d\n", sizeof(double)); /* 8 */
  
  return 0;
}

void print_per(unsigned char n) {
  switch (n) {
  case 1: printf("1 ==> Read\n"); break;
  case 2: printf("2 ==> Write\n"); break;
  case 3: printf("3 ==> Read/write\n"); break;
  case 4: printf("4 ==> Execute\n"); break;
  case 7: printf("7 ==> Read/write/execute\n"); break;
  default: printf("%i ==> No such permission.\n", n);
  }
}
