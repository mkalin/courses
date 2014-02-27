#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ArraySize  (10)
#define HowMany    (12)
#define MaxName    (120)
#define MaxAddress (150)
#define NL         printf("\n")

typedef unsigned bool;
enum {false, true};
typedef struct {
  char           lname[MaxName + 1];
  char           fname[MaxName + 1];
  char           address[MaxAddress + 1];
  bool           married;
  unsigned short age; 
} Emp;

/* pass by value: copy of address of array's 1st element */
void dump_lname(char lname[]) {
  NL;
  printf("Last name is %s", lname);
  NL;
}

/* pass by value: copy of address of Emp struct */
void dump(Emp* emp) {
  printf("First name: %s", emp->fname); NL;
  printf("Last name:  %s", emp->lname); NL;
  printf("Address:    %s", emp->address); NL;
  printf("Married?    %s", (emp->married) ? "Yes" : "No"); NL;
}

void call_by_value_for_array_in_struct(Emp emp) {
  strcpy(emp.lname, "FooBar");
  dump_lname(emp.lname); /* Last name is FooBar */
}

int comp1(const void* p1, const void* p2) {
  return *((const int*) p1) - *((const int*) p2); /* ascending */
}

int comp2(const void* p1, const void* p2) {
  return **((const int**) p2) - **((const int**) p1);
}

void dump_array(int array[ ], unsigned n) {
  NL;
  unsigned i;
  for (i = 0; i < n; i++) printf("%i ", array[i]);
  NL;
}

void dump_ptrs(int* array[ ], unsigned n) {
  NL;
  unsigned i;
  for (i = 0; i < n; i++) printf("%i ", *array[i]);
  NL;
}

int main() {
  /* Three aggregates of Emps, one on the stack, two on the heap 
     The storage within all three structures is contiguous. 
   */
  Emp  emps1[HowMany];                         /* stack */
  Emp* emps2 = malloc(HowMany * sizeof(Emp));  /* heap, uninitialized */
  Emp* emps3 = calloc(HowMany,  sizeof(Emp));   /* heap, initialized */

  /* Initialize one of each */
  strcpy(emps1[0].lname, "Vanger");
  strcpy(emps1[0].fname, "Martin");
  strcpy(emps1[0].address, "1 Yellow Brick Road, HereOrThere, Somewhere");
  emps1[0].married = false;
  emps1[0].age = 47;

  strcpy(emps2[0].lname, "Vanger");
  strcpy(emps2[0].fname, "Martin");
  strcpy(emps2[0].address, "1 Yellow Brick Road, HereOrThere, Somewhere");
  emps2[0].married = false;
  emps2[0].age = 47;

  strcpy(emps3[0].lname, "Vanger");
  strcpy(emps3[0].fname, "Martin");
  strcpy(emps3[0].address, "1 Yellow Brick Road, HereOrThere, Somewhere");
  emps3[0].married = false;
  emps3[0].age = 47;

  /* Dump each */
  dump(&emps1[0]); NL; /* one way */
  dump(emps2 + 0); NL; /* another way */
  dump(emps3);     NL; /* same as the above */

  dump_lname((emps3 + 1)->lname); /* safe because calloc initializes to zero */

  /* call by value (copy) illustration */
  call_by_value_for_array_in_struct(emps1[0]); /* Last name is FooBar */
  dump_lname(emps1[0].lname);                  /* Last name is Vanger */

  /* free the heap storage */
  free(emps2);
  free(emps3);

  /* some ints */
  int array[ ] = {2, 1, 5, 3, 4, 8, 7, 9, 6, 0};
  int* ptrs[ArraySize];
  
  /* store addresses in ptrs */
  int i;
  for (i = 0; i < ArraySize; i++) ptrs[i] = array + i;

  qsort(ptrs, ArraySize, sizeof(int*), comp2);
  dump_array(array, ArraySize); /* 2 1 5 3 4 8 7 9 6 0 */
  dump_ptrs(ptrs, ArraySize);   /* 9 8 7 6 5 4 3 2 1 0 */

  dump_array(array, ArraySize); /* 2 1 5 3 4 8 7 9 6 0 */
  qsort(array, ArraySize, sizeof(int), comp1);
  dump_array(array, ArraySize); /* 0 1 2 3 4 5 6 7 8 9 */

  /* tricky but powerful stuff */
  int* nums = calloc(ArraySize, sizeof(int));
  for (i = 0; i < ArraySize; i++) nums[i] = i + 1;
  dump_array(nums, ArraySize); /* 1 2 3 4 5 6 7 8 9 10 */
  nums = realloc(nums, 5);
  if (!nums) 
    fprintf(stderr, "%s", "realloc failed...\n");
  else {
    for (i = ArraySize; i < (ArraySize + 5); i++) nums[i] = i + 1;
    dump_array(nums, ArraySize + 5); /* 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 */
  }

  return 0;
}
