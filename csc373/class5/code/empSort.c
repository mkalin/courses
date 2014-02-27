#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxName     (80)
#define BuffSize   (280)

typedef unsigned int bool;
enum {false, true}; 

typedef struct Emp {
  unsigned char  lname[MaxName + 1]; /* + 1 for '\0' */
  unsigned char  fname[MaxName + 1];
  unsigned char  nickname[MaxName + 1];
  unsigned int   id;
  unsigned char  dept;
  bool           married;
} Emp;

void set_name(char* target, char* source) {
  if (strlen(source) > MaxName) return;
  strcpy(target, source);
}

void set_id(unsigned int* id_ptr) {
  *id_ptr = rand();
}

void set_dept(unsigned char* dept_ptr, unsigned char code) {
  *dept_ptr = code;
}

void set_married(unsigned int* married, unsigned int status) {
  *married = status;
}

void to_string(Emp* this, char* buffer) {
  unsigned char temp[32];

  printf("\n** Employee information **");
  
  strcpy(buffer, "");

  strcat(buffer, "\nLast name:   "); 
  strcat(buffer, this->lname);
  strcat(buffer, "\nFirst name:  ");
  strcat(buffer, this->fname);  
  strcat(buffer, "\nNickname:    ");
  strcat(buffer, this->nickname);

  sprintf(temp, "%i", this->id);
  strcat(buffer, "\nEmployee id: ");
  strcat(buffer, temp);

  sprintf(temp, "%c", this->dept);
  strcat(buffer, "\nDepartment:  ");
  strcat(buffer, temp);

  strcat(buffer, "\nMarried?:    ");
  if (this->married) 
    strcat(buffer, "yes");
  else
    strcat(buffer, "no");
}

/** Homework: documentation assignment starts here 
    Specific issues:

    (1) Why are there two dump_emps functions rather than
        just one? How do they differ?

    (2) Same for the compA and compB functions, the callbacks
        for the two qsorts.

    (3) I do two qsorts. In each case, as the output shows,
        the Employees are printed in (the same) sorted order.
        Which approach (the first qsort or the second) is better 
        and why? Explain, in particular, how the two qsorts
        differ.

    You can ignore the const business. What 

        const Emp* ptr;

    means is that the object to which ptr points cannot be changed. 
    (I'm using "object" here in a generic sense to mean "thing," not in 
    the object-oriented sense.)
*/

void dump_emps1(Emp a[ ], unsigned n) {
  int i;
  char buffer[BuffSize + 1];
  for (i = 0; i < n; i++) {
    to_string(&a[i], buffer);
    printf("%s\n", buffer);
  }  
}

void dump_emps2(Emp* a[ ], unsigned n) {
  int i;
  char buffer[BuffSize + 1];
  for (i = 0; i < n; i++) {
    to_string(a[i], buffer);
    printf("%s\n", buffer);
  }
}

/* void* is the generic pointer type; that is, any
   pointer type (such as Emp*) can be cast to or
   from void*. In object-oriented languages such as
   Java and C#, the Object type is the counterpart 
   of C's void* type.

   The fourth argument to qsort must be a pointer to
   a function that (1) returns an int and (2) takes
   two arguments of type const void*.

   The returned int has the following "qsort semantics,"
   which are used by virtually every sort routine in
   every modern programming language. Here are the
   semantics, explained with reference to the pointers
   item1 and item2:

      return 0 if item1->object and item2->object are
      equal with respect to sorted order

      return a negative integer if item1->object precedes
      item2->object in sorted order

      return a positive integer if item1->object succeeds
      item2->object in sorted order
*/
int compA(const void* item1, const void* item2) {
  const Emp* emp1 = (const Emp*) item1;
  const Emp* emp2 = (const Emp*) item2;
  
  unsigned char buff1[BuffSize + 1];
  unsigned char buff2[BuffSize + 1];

  strcpy(buff1, emp1->lname);
  strcat(buff1, emp1->fname);
  strcpy(buff2, emp2->lname);
  strcat(buff2, emp2->fname);

  return strcmp(buff1, buff2);
}

int compB(const void* item1, const void* item2) {
  const Emp** emp1 = (const Emp**) item1;
  const Emp** emp2 = (const Emp**) item2;

  unsigned char buff1[BuffSize + 1];
  unsigned char buff2[BuffSize + 1];

  strcpy(buff1, (*emp1)->lname);
  strcat(buff1, (*emp1)->fname);
  strcpy(buff2, (*emp2)->lname);
  strcat(buff2, (*emp2)->fname);

  return strcmp(buff1, buff2);
}

void create_emps(Emp emps[ ]) {
 /* populate the array: don't bother to document this */
  set_name(emps[0].lname, "Ruble");
  set_name(emps[0].fname, "Barney");
  set_name(emps[0].nickname, "The Animal");
  set_id(&emps[0].id);
  set_dept(&emps[0].dept, 'Q');
  set_married(&emps[0].married, true);

  set_name(emps[1].lname, "Ruble");
  set_name(emps[1].fname, "Betty");
  set_name(emps[1].nickname, "The Princess");
  set_id(&emps[1].id);
  set_dept(&emps[1].dept, 'R');
  set_married(&emps[1].married, true);

  set_name(emps[2].lname, "Flintstone");
  set_name(emps[2].fname, "Pebbles");
  set_name(emps[2].nickname, "The Child Prodigy");
  set_id(&emps[2].id);
  set_dept(&emps[2].dept, 'C');
  set_married(&emps[2].married, false);

  set_name(emps[3].lname, "Flintstone");
  set_name(emps[3].fname, "Wilma");
  set_name(emps[3].nickname, "The Boss");
  set_id(&emps[3].id);
  set_dept(&emps[3].dept, 'A');
  set_married(&emps[3].married, true);

  set_name(emps[4].lname, "Flintstone");
  set_name(emps[4].fname, "Baby Puss");
  set_name(emps[4].nickname, "The Child from Hell");
  set_id(&emps[4].id);
  set_dept(&emps[4].dept, 'C');
  set_married(&emps[4].married, false);

  set_name(emps[5].lname, "Flintstone");
  set_name(emps[5].fname, "Fred");
  set_name(emps[5].nickname, "The Man");
  set_id(&emps[5].id);
  set_dept(&emps[5].dept, 'Z');
  set_married(&emps[5].married, true);
}

int main() {
  /* Seed the pseudo-random number generator with the current time. 
     An Emp's id is set to a pseudo-random number. */
  srand(time(0)); 

  const int n = 6;
  Emp emps[n];
  create_emps(emps);

  /* emps before any sorting */
  printf("**** Before sorting:\n");
  dump_emps1(emps, n);

  int i;
  Emp* emps_a[n];
  for (i = 0; i < n; i++) emps_a[i] = emps + i;

  /* 1st qsort: better or worse approach than 2nd? why? */
  qsort(emps_a, n, sizeof(Emp*), compB);
  printf("\n**** After 1st sort:\n");
  dump_emps2(emps_a, n);

  /* 2nd qsort: better or worse approach than 1st? why? */
  qsort(emps, n, sizeof(Emp), compA);
  printf("\n**** After 2nd sort:\n");
  dump_emps1(emps, n);

  return 0;
}

