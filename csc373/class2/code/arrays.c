/* arrays, structs, and alignment issues */

#include <stdio.h>

void array_stuff();     /* declaration */
void struct_stuff();    /* declaration */
void function_stuff();  /* declaration */

int main() {
  array_stuff();
  struct_stuff();
  function_stuff();
  return 0;
}

void array_stuff() {
  /* First, a quick look at how N-dimensional arrays are stored.
     A "table" or "matrix" is a 2-dimensional array, whereas a
     "vector" is a 1-dimensional array. However, at the implemenation
     level 1-dimensional and multi-dimensional arrays are laid out the
     same way --- as contiguous elements in memory. In C, a table or
     matrix is stored in "row major" order. In this example, the first
     row consists of 1 and 2 and the first column consists of 1, 3, and
     5; hence, the C layout is 1 2 3 4 5 6 rather than 1 3 5 2 4 6.
  */
  int table[3][2] =
    { {1, 2},
      {3, 4},
      {5, 6}
    };
  int i, j;

  /* cast because table's type is "pointer to an array of arrays." */
  int* ptr = (int*) table;
			      
  /* normal way to access elements: row-major order in IA32 */
  for (i = 0; i < 3; i++)
    for (j = 0; j < 2; j++)
      printf("table[%i][%i] == %i\n", i, j, table[i][j]);
  /* output:
     
     table[0][0] == 1
     table[0][1] == 2
     table[1][0] == 3
     table[1][1] == 4
     table[2][0] == 5
     table[2][1] == 6
  */

  /* treating an N-dimensional array as a 1-dimensional array */
  printf("\n");
  for (i = 0; i < (3 * 2); i++) 
    printf("table[%i] == %i\n", i, ptr[i]);
   /* output:

     table[0] == 1
     table[1] == 2
     table[2] == 3
     table[3] == 4
     table[4] == 5
     table[5] == 6
  */
}

void struct_stuff() {
  struct Sample {
    int n1;   /* 4 bytes */
    char c;   /* 1 byte */
    int n2;   /* 4 bytes */
  };

  /* code to illustrate use */
  struct Sample* ptr_s1 = malloc(sizeof(struct Sample));
  ptr_s1->n1 = 1;
  ptr_s1->c = 'A';
  ptr_s1->n2 = 2;
  (*ptr_s1).n2 += 4; /* same as ptr_s1->n2 += 4 */
  free(ptr_s1);

  printf("A struct Sample instance requires %d bytes\n",
	 sizeof(struct Sample));
  /* Output on my Linux box: A struct Sample instance requires 12 bytes */

  /* layout issues:
                              
                      Bytes:     4       1      4
     Minimalist possibility: +--------+----+--------+
                             |  n1    |  c |   n2   |
                             +--------+----+--------+

     If you disassemble struct Sample, you'll likely see the pertinent 
     assembler begins with the directive

         .align 4

     The directive means that the struct's fields are laid out in memory
     on DW0RD (that is, 4-byte) boundaries. So the picture becomes

                                4        4        4
                            +--------+--------+--------+
                            |   n1   |   c    |   n2   |
                            +--------+--------+--------+

     This layout "wastes" 3 bytes, as the char requires only 4; but the
     resulting processing is simpler in that memory fetches are always from
     addresses on DWORD boundaries.
  */
}

int f(int n) {          /* definition */
  return n * 2 + 1;
}

void function_stuff() {
  int ans;
  struct Object {
    int id;
    int (*method)(int);
  };
  typedef struct Object Obj;

  Obj obj1;
  obj1.id = 1234;
  obj1.method = f;

  ans = (*obj1.method)(25);  /* technically correct */
  ans = obj1.method(27);     /* now allowed in standard C */
  printf("%i\n", ans);  
}
