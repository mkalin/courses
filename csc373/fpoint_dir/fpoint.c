#include <stdio.h>
#include <float.h>
/* the next include, for math.h, includes the header file; but the C
   linker does not automatically link in the corresponding math library,
   which is libm.a on a Unix/Linux system. To force the link, you'd

         gcc -o fpoint -lm fpoint.c

   where fpoint.c is this file.
*/
#include <math.h>

/* The industry standard for floating-point numbers is called IEEE 754.

   Short and dirty overview:

   Sign bit: 1 for negative, 0 for nonnegative (just like 2's complement)
   
   Significand ("mantissa"): fractional binary number

   Exponent: weights the value of the significand by a power of 2

   C representations:

   The IEEE 754 single-precision type is a C float. There's a 1-bit sign,
   an 8-bit exponent, and a 23-bit fraction value for a 32-bit floating
   point type. For the IEEE 754 double-precision type, C has double. Again
   there's a 1-bit sign but the exponent is now 11 bits and the fraction
   value is 52 bits for a 64-bit type.

   Here's the layout for single-precision:

    s exponent   significand
   +-+--------+-----------------------+
   | |        |                       |
   +-+--------+-----------------------+

   Normalized Values:
   
   The exponent's bit pattern is neither all zeros 00..000 nor all ones 11..111.
   In this case, the exponent represents a signed integer in "biased" form; that
   is, the exponent's value 

   E = e - bias

   where e is the value of the exponent bit pattern and bias is 127 for 
   single-precision and 1023 for double-precision. The upshot is that the
   biased exponent now ranges between -126 to +127 for single-precision and
   between -1022 to +1023 for double-precision floating points.

   In normalized values, the fractional part F represents a value 

   0 <= F < 1

   or 0.xxxxxxx...xxx in binary. Note that the binary point is to the left of
   the most significant bit, the leftmost "x" in this example. The signficand M
   is then definted to be

   M = 1 + F

   sometimes called the "implied leading 1" representation. This representation
   saves a bit (the assumed 1), which then can be used in the exponent.

   Example 1:
 
   The problem: To represent the decimal number -118.625 in IEEE 754 
                single-precision format.

   The solution:

   ** The number is negative so that the sign bit must be 1.

   ** -118.6 in decimal is -1110110.101 in binary.

   ** If we move the binary point left so that there is a single 1 to its left
      (the "implied leading 1"), we get -1.110110101 * 2**6 (where the power 6
      represents the number of positions that the the binary point moved to the
      left).

   ** So the unbiased exponent is 6 and the bias is -127 (that is, 2**(8 - 1) - 1).
      Adding 6 to 127 gives 133 so that subtracing the bias (133 - 127) gives us
      the exponent, 6. In binary, 133 is 10000101 as an unsigned integer.
 
   ** The significand is 110110101. Right fill with zeros until the length is
      23 bits. This yields 11011010100000000000000.

   ** The full representation (with spaces for readability) is

   sign exponent      significand
      1 10000101 11011010100000000000000
   

   Example 2:

   Show the layout of 

           float  pi_f = 3.1415f;
           double pi_d = 3.14.15;

   in IEEE 754 single and extended precision.

      Single precision:

                +  128 - 127          1.57575 in decimal
         sign bit  exponent           significand

                0  10000000     1.10010010000111001010110

             [31]  [30]-[23]    [22]    ...            [0]

         -3.1415 is exactly the same except for the sign bit, 
         which becomes 1

      Note that the internal representation is little endian in the
      exponent, with the left side as the least significant. The value
      is 1, 128 - 127.

      Double precision:

                +  1024 - 1023
         sign bit  exponent

                0  10000000000  1.1001001000011100101011000000100000110001001001101111

             [63]  [62]...[52]  [51]    ...                                        [0]

   Denormalized Values:

   If the exponent field is all zeros, the represented number is "denormalized." 
   In this cae, the exponent value is 

            E = 1 - bias   

   and the significand value is 

            M = f

   or the fraction without the "implied leading 1."

   Denormalized numbers are needed for two reasons:

      (1) To represent zero. In a normalized number, note that M >= 1 because
          of the "implied leading 1."

      (2) To support "gradual underflow." Numbers very close to zero can be
          represented in denormalized form.

   One result of denormalized numbers is that, for floating points as for 
   integers, -0.0 == +0.0. -0.0 is all zeros except for the sign bit, whereas
   +0.0 is all zeros. 

   Special Values and NaN:

   Consider the case in which the exponent field is all 1s and the fraction field
   is all 0s. If the sign is 0, then we have "positive infinity"; and if the 
   sign is 1, then we have "negative infinity". If the exponent is all 1s but the
   fraction is non-zero, the result is NaN (Not a Number). An example would be

                    3.1415 / 0.0

*/

void show_bytes(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = 0; i < how_many; i++) printf(" %.2x", ptr[i]);
  printf("\n");
}

#define POS_INFINITY (1e5000)
#define NEG_INFINITY (-POS_INFINITY)
#define NEG_ZERO     (-1.0 / POS_INFINITY)

int main() {

  int n = 3490593;     /* 3,490,593 */
  float f = (float) n; /* 3,490,593.0 */

  show_bytes("n = 3490593", (unsigned char*) &n, 
	     sizeof(int)); /* n = 3490593 21 43 35 00 */

  show_bytes("f = 3490593", (unsigned char*) &f, 
	     sizeof(int)); /* f = 3490593 84 0c 55 4a */

  float f1 = 100000.0f;
  float f2 = (f1 * 1e-5) * 1e5;
  printf("%f %f\n", f1, f2);
  
  printf("Integer -0 equals +0: %d\n", 
	 -0 == +0);         /* true */
  printf("F-point -0.0 equals +0.0: %d\n", 
	 -0.0 == +0.0);     /* true */

  printf("pi / 0 is %f\n", 
	 3.1415f / 0.0f);              /* pi / 0 is inf */

  printf("pi / -0 is %f\n", 
	 3.1415f / -0.0f);             /* pi / -0 is -inf */

  printf("-INF == +INF: %d\n", 
	 1.1f / 0.0f == 1.1f / -0.0f); /* false */

  printf("square root of -1 is %f\n", 
	 sqrt(-1.0));                  /* square root of -1 is nan */

  printf("Macroed +inf: %f\tMacroed -inf: %f\t Macroed -0: %f\n",
	 POS_INFINITY, NEG_INFINITY, NEG_ZERO); /* inf, -inf, -0 */

  /* cheap C trick: introduce a block so that we can redefine some
     variables definted above
  */
  {
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
  }

  {
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
  }
  return 0;
}
