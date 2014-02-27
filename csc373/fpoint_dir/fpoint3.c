#include <float.h>
#include <stdio.h>

void show_bytes(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = 0; i < how_many; i++) printf(" %.2x", ptr[i]);
  printf("\n");
}


int main() {
  float f1 = 0.666667f;
  show_bytes("f1: 0.666667f:", (unsigned char*) &f1, sizeof(float));

  float f2 = 0.666666f;
  show_bytes("f2: 0.666666f:", (unsigned char*) &f1, sizeof(float));

  float f3 = 0.6666666f;
  show_bytes("f3: 0.666666f:", (unsigned char*) &f1, sizeof(float));

  float f4 = 2.0f / 3.0f;
  show_bytes("f4: 2.0f / 3.0f:", (unsigned char*) &f1, sizeof(float));

  float f5 = 2.00001f / 3.000001f;
  show_bytes("f5: 200001f / 3.000001f:", (unsigned char*) &f1, sizeof(float));

  printf("f1 == %f\tf2 == %f\tf3 == %f\nf4 == %f\tf5 == %f\n", 
	 f1, f2, f3, f4, f5);

  printf("%f == %f ==> %i\n", f4, f5, f4 == f5);
  printf("fabs(%f - %f) > FLT_EPSILON ==> %d\n",
	 f4, f5, fabs(f4 - f5) > FLT_EPSILON);

  printf("FLT_EPSILON == %f\nFLT_EPSILON  == 0.0f ==> %d\n", 
	 FLT_EPSILON, FLT_EPSILON == 0.0f);
  /* output:

     f1: 0.666667f: b0 aa 2a 3f
     f2: 0.666666f: b0 aa 2a 3f
     f3: 0.666666f: b0 aa 2a 3f
     f4: 2.0f / 3.0f:         b0 aa 2a 3f
     f5: 200001f / 3.000001f: b0 aa 2a 3f

     f1 == 0.666667  f2 == 0.666666  f3 == 0.666667
     f4 == 0.666667  f5 == 0.666670
     0.666667 == 0.666670 ==> 0

     fabs(0.666667 - 0.666670) > FLT_EPSILON ==> 1

     FLT_EPSILON == 0.000000
     FLT_EPSILON == 0.0f ==> 0
  */
  return 0;
}
