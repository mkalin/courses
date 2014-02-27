#include <float.h>
#include <stdio.h>

int main() {
  float f1 = 0.666667f;
  float f2 = 0.666666f;
  float f3 = 0.6666666f;
  float f4 = 2.0f / 3.0f;
  float f5 = 2.00001f / 3.000001f;

  printf("f1 == %f\tf2 == %f\tf3 == %f\nf4 == %f\tf5 == %f\n", 
	 f1, f2, f3, f4, f5);

  printf("%f == %f ==> %i\n", f4, f5, f4 == f5);
  printf("%f == %f ==> %i\n", f4, f5, f4 - f5 <= FLT_EPSILON);
  /* output:

     f1 == 0.666667  f2 == 0.666666  f3 == 0.666667
     f4 == 0.666667  f5 == 0.666670
     0.666667 == 0.666670 ==> 0
     0.666667 == 0.666670 ==> 1
  */
  return 0;

}
