     1	#include <stdio.h>
     2	#include <float.h>
     3	/* the next include, for math.h, includes the header file; but the C
     4	   linker does not automatically link in the corresponding math library,
     5	   which is libm.a on a Unix/Linux system. To force the link, you'd
     6	
     7	         gcc -o fpoint -lm fpoint.c
     8	
     9	   where fpoint.c is this file.
    10	*/
    11	#include <math.h>
    12	
    13	/* The industry standard for floating-point numbers is called IEEE 754.
    14	
    15	   Short and dirty overview:
    16	
    17	   Sign bit: 1 for negative, 0 for nonnegative (just like 2's complement)
    18	   
    19	   Significand ("mantissa"): fractional binary number
    20	
    21	   Exponent: weights the value of the significand by a power of 2
    22	
    23	   C representations:
    24	
    25	   The IEEE 754 single-precision type is a C float. There's a 1-bit sign,
    26	   an 8-bit exponent, and a 23-bit fraction value for a 32-bit floating
    27	   point type. For the IEEE 754 double-precision type, C has double. Again
    28	   there's a 1-bit sign but the exponent is now 11 bits and the fraction
    29	   value is 52 bits for a 64-bit type.
    30	
    31	   Here's the layout for single-precision:
    32	
    33	    s exponent   significand
    34	   +-+--------+-----------------------+
    35	   | |        |                       |
    36	   +-+--------+-----------------------+
    37	
    38	   Normalized Values:
    39	   
    40	   The exponent's bit pattern is neither all zeros 00..000 nor all ones 11..111.
    41	   In this case, the exponent represents a signed integer in "biased" form; that
    42	   is, the exponent's value 
    43	
    44	   E = e - bias
    45	
    46	   where e is the value of the exponent bit pattern and bias is 127 for 
    47	   single-precision and 1023 for double-precision. The upshot is that the
    48	   biased exponent now ranges between -126 to +127 for single-precision and
    49	   between -1022 to +1023 for double-precision floating points.
    50	
    51	
    52	
    53	
    54	
    55	
    56	
    57	
    58	
    59	
    60	
    61	
    62	   In normalized values, the fractional part F represents a value 
    63	
    64	   0 <= F < 1
    65	
    66	   or 0.xxxxxxx...xxx in binary. Note that the binary point is to the left of
    67	   the most significant bit, the leftmost "x" in this example. The signficand M
    68	   is then definted to be
    69	
    70	   M = 1 + F
    71	
    72	   sometimes called the "implied leading 1" representation. This representation
    73	   saves a bit (the assumed 1), which then can be used in the exponent.
    74	
    75	   Example 1:
    76	 
    77	   The problem: To represent the decimal number -118.625 in IEEE 754 
    78	                single-precision format.
    79	
    80	   The solution:
    81	
    82	   ** The number is negative so that the sign bit must be 1.
    83	
    84	   ** -118.6 in decimal is -1110110.101 in binary.
    85	
    86	   ** If we move the binary point left so that there is a single 1 to its left
    87	      (the "implied leading 1"), we get -1.110110101 * 2**6 (where the power 6
    88	      represents the number of positions that the the binary point moved to the
    89	      left).
    90	
    91	   ** So the unbiased exponent is 6 and the bias is -127 (that is, 2**(8 - 1) - 1).
    92	      Adding 6 to 127 gives 133 so that subtracing the bias (133 - 127) gives us
    93	      the exponent, 6. In binary, 133 is 10000101 as an unsigned integer.
    94	 
    95	   ** The significand is 110110101. Right fill with zeros until the length is
    96	      23 bits. This yields 11011010100000000000000.
    97	
    98	   ** The full representation (with spaces for readability) is
    99	
   100	   sign exponent      significand
   101	      1 10000101 11011010100000000000000
   102	   
   103	
   104	
   105	
   106	
   107	
   108	
   109	
   110	
   111	
   112	
   113	
   114	
   115	
   116	
   117	
   118	
   119	
   120	
   121	
   122	   Example 2:
   123	
   124	   Show the layout of 
   125	
   126	           float  pi_f = 3.1415f;
   127	           double pi_d = 3.14.15;
   128	
   129	   in IEEE 754 single and extended precision.
   130	
   131	      Single precision:
   132	
   133	                +  128 - 127          1.57575 in decimal
   134	         sign bit  exponent           significand
   135	
   136	                0  10000000     1.10010010000111001010110
   137	
   138	             [31]  [30]-[23]    [22]    ...            [0]
   139	
   140	         -3.1415 is exactly the same except for the sign bit, 
   141	         which becomes 1
   142	
   143	      Note that the internal representation is little endian in the
   144	      exponent, with the left side as the least significant. The value
   145	      is 1, 128 - 127.
   146	
   147	      Double precision:
   148	
   149	                +  1024 - 1023
   150	         sign bit  exponent
   151	
   152	     0  10000000000  1.1001001000011100101011000000100000110001001001101111
   153	
   154	    [63]  [62]...[52]  [51]    ...                                        [0]
   155	
   156	   Denormalized Values:
   157	
   158	   If the exponent field is all zeros, the represented number is "denormalized." 
   159	   In this cae, the exponent value is 
   160	
   161	            E = 1 - bias   
   162	
   163	   and the significand value is 
   164	
   165	            M = f
   166	
   167	   or the fraction without the "implied leading 1."
   168	
   169	   Denormalized numbers are needed for two reasons:
   170	
   171	      (1) To represent zero. In a normalized number, note that M >= 1 because
   172	          of the "implied leading 1."
   173	
   174	      (2) To support "gradual underflow." Numbers very close to zero can be
   175	          represented in denormalized form.
   176	
   177	   One result of denormalized numbers is that, for floating points as for 
   178	   integers, -0.0 == +0.0. -0.0 is all zeros except for the sign bit, whereas
   179	   +0.0 is all zeros. 
   180	
   181	
   182	   Special Values and NaN:
   183	
   184	   Consider the case in which the exponent field is all 1s and the fraction field
   185	   is all 0s. If the sign is 0, then we have "positive infinity"; and if the 
   186	   sign is 1, then we have "negative infinity". If the exponent is all 1s but the
   187	   fraction is non-zero, the result is NaN (Not a Number). An example would be
   188	
   189	                    3.1415 / 0.0
   190	
   191	*/
   192	
   193	void show_bytes(char* msg, unsigned char* ptr, int how_many) {
   194	  printf("%s\n", msg);
   195	  int i;
   196	  for (i = 0; i < how_many; i++) printf(" %.2x", ptr[i]);
   197	  printf("\n");
   198	}
   199	
   200	#define POS_INFINITY (1e5000)
   201	#define NEG_INFINITY (-POS_INFINITY)
   202	#define NEG_ZERO     (-1.0 / POS_INFINITY)
   203	
   204	int main() {
   205	
   206	  int n = 3490593;     /* 3,490,593 */
   207	  float f = (float) n; /* 3,490,593.0 */
   208	
   209	  show_bytes("n = 3490593", (unsigned char*) &n, 
   210		     sizeof(int)); /* n = 3490593 21 43 35 00 */
   211	
   212	  show_bytes("f = 3490593", (unsigned char*) &f, 
   213		     sizeof(int)); /* f = 3490593 84 0c 55 4a */
   214	
   215	  float f1 = 100000.0f;
   216	  float f2 = (f1 * 1e-5) * 1e5;
   217	  printf("%f %f\n", f1, f2);
   218	  
   219	  printf("Integer -0 equals +0: %d\n", 
   220		 -0 == +0);         /* true */
   221	  printf("F-point -0.0 equals +0.0: %d\n", 
   222		 -0.0 == +0.0);     /* true */
   223	
   224	  printf("pi / 0 is %f\n", 
   225		 3.1415f / 0.0f);              /* pi / 0 is inf */
   226	
   227	  printf("pi / -0 is %f\n", 
   228		 3.1415f / -0.0f);             /* pi / -0 is -inf */
   229	
   230	  printf("-INF == +INF: %d\n", 
   231		 1.1f / 0.0f == 1.1f / -0.0f); /* false */
   232	
   233	  printf("square root of -1 is %f\n", 
   234		 sqrt(-1.0));                  /* square root of -1 is nan */
   235	
   236	  printf("Macroed +inf: %f\tMacroed -inf: %f\t Macroed -0: %f\n",
   237		 POS_INFINITY, NEG_INFINITY, NEG_ZERO); /* inf, -inf, -0 */
   238	
   239	
   240	
   241	
   242	  /* cheap C trick: introduce a block so that we can redefine some
   243	     variables definted above
   244	  */
   245	  {
   246	    float f1 = 0.666667f;
   247	    float f2 = 0.666666f;
   248	    float f3 = 0.6666666f;
   249	    float f4 = 2.0f / 3.0f;
   250	    float f5 = 2.00001f / 3.000001f;
   251	    
   252	    printf("f1 == %f\tf2 == %f\tf3 == %f\nf4 == %f\tf5 == %f\n", 
   253		   f1, f2, f3, f4, f5);
   254	    
   255	    printf("%f == %f ==> %i\n", f4, f5, f4 == f5);
   256	    printf("%f == %f ==> %i\n", f4, f5, f4 - f5 <= FLT_EPSILON);
   257	    /* output:
   258	       
   259	    f1 == 0.666667  f2 == 0.666666  f3 == 0.666667
   260	    f4 == 0.666667  f5 == 0.666670
   261	    0.666667 == 0.666670 ==> 0
   262	    0.666667 == 0.666670 ==> 1
   263	    */
   264	  }
   265	
   266	  {
   267	    float f1 = 0.666667f;
   268	    show_bytes("f1: 0.666667f:", (unsigned char*) &f1, sizeof(float));
   269	    
   270	    float f2 = 0.666666f;
   271	    show_bytes("f2: 0.666666f:", (unsigned char*) &f1, sizeof(float));
   272	    
   273	    float f3 = 0.6666666f;
   274	    show_bytes("f3: 0.666666f:", (unsigned char*) &f1, sizeof(float));
   275	    
   276	    float f4 = 2.0f / 3.0f;
   277	    show_bytes("f4: 2.0f / 3.0f:", (unsigned char*) &f1, sizeof(float));
   278	    
   279	    float f5 = 2.00001f / 3.000001f;
   280	    show_bytes("f5: 200001f / 3.000001f:", (unsigned char*) &f1, sizeof(float));
   281	    
   282	    printf("f1 == %f\tf2 == %f\tf3 == %f\nf4 == %f\tf5 == %f\n", 
   283		   f1, f2, f3, f4, f5);
   284	    
   285	    printf("%f == %f ==> %i\n", f4, f5, f4 == f5);
   286	    printf("fabs(%f - %f) > FLT_EPSILON ==> %d\n",
   287		   f4, f5, fabs(f4 - f5) > FLT_EPSILON);
   288	    
   289	    printf("FLT_EPSILON == %f\nFLT_EPSILON  == 0.0f ==> %d\n", 
   290		   FLT_EPSILON, FLT_EPSILON == 0.0f);
   291	    /* output:
   292	       
   293	    f1: 0.666667f: b0 aa 2a 3f
   294	    f2: 0.666666f: b0 aa 2a 3f
   295	    f3: 0.666666f: b0 aa 2a 3f
   296	    f4: 2.0f / 3.0f:         b0 aa 2a 3f
   297	    f5: 200001f / 3.000001f: b0 aa 2a 3f
   298	    
   299	
   300	
   301	
   302	    f1 == 0.666667  f2 == 0.666666  f3 == 0.666667
   303	    f4 == 0.666667  f5 == 0.666670
   304	    0.666667 == 0.666670 ==> 0
   305	    
   306	    fabs(0.666667 - 0.666670) > FLT_EPSILON ==> 1
   307	    
   308	    FLT_EPSILON == 0.000000
   309	    FLT_EPSILON == 0.0f ==> 0
   310	    */
   311	  }
   312	  return 0;
   313	}
   314	
