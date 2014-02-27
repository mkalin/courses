#include <stdio.h>
#include <stddef.h> /* for wide characters */

/* formatting summary: 
     sizeof(char) is defined to be 1
     all other sizes must be >= sizeof(char)

     The sizes shown here (Intel 32-bit machine run Linux)
     are common.
 */
int main() {
  /* character strings */
   char    *message  = "Printing different data types";
   wchar_t *wmessage = L"Wide character string";

   /* characters */
   char ca     = 'A';
   wchar_t wca = L'A';
   printf("sizeof(char) == %li\n", sizeof(char));       /* 1 */
   printf("sizeof(wchar_t) == %li\n", sizeof(wchar_t)); /* 4 */
   printf("\n");

   /* integers */
   unsigned short         usa  = 65535; 
   signed short           ssb  = -32768;
   unsigned int           usi  = 4294967295; 
   signed int             ssi  = -2147483648;
   unsigned long long int ulli = 4294967295L;
   long long int          lli  = -2147483647L;
   printf("sizeof(short)         == %li\n", sizeof(short));         /* 2 */
   printf("sizeof(int)           == %li\n", sizeof(int));           /* 4 */
   printf("sizeof(long)          == %li\n", sizeof(long));          /* 8 */
   printf("sizeof(long long int) == %li\n", sizeof(long long int)); /* 8 */
   printf("\n");

   /* floating-point types */
   float        fa  = 1e+37,  fb = 1e-37;
   double       da = 1e+37,   db = 1e-37;
   long double lda = 1e+37L, ldb = 1e-37L;
   printf("sizeof(float)       == %li\n", sizeof(float));       /*  4 */
   printf("sizeof(double)      == %li\n", sizeof(double));      /*  8 */
   printf("sizeof(long double) == %li\n", sizeof(long double)); /* 16 */
   printf("\n");

   /* pointers */
   int* p = &ssi;
   printf("sizeof(int*) == %li\n", sizeof(int*));    /* 4 */
   printf("sizeof(void*) == %li\n", sizeof(void*));  /* 4 */
   printf("\n");

   /* shorts */
   printf("%hu %hi\n", usa, ssb); 
   printf("%hx %hx\n\n", usa, ssb);
   
   /* ints and long ints */
   printf("%u %i\n", usi, ssi); 
   printf("%x %x\n\n", usi, ssi);

   printf("%llu %lli\n", ulli, lli);
   printf("%llx %llx\n\n", ulli, lli);

   printf("%f %f\n", fa, fb); 

   printf("%f %f\n", da, db);
   printf("%e %e\n\n", da, db);

   printf("%Lf %Lf\n", lda, ldb);
   printf("%Le %Le\n\n", lda, ldb);

   return 0;
}
