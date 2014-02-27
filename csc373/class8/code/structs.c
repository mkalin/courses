#include <stdio.h>
#include <stdlib.h>

#define MaxLname    (60)
#define MaxFname    (60)
#define MaxAddress (120)

typedef struct Emp {
  char     lname[MaxLname + 1];
  char     fname[MaxFname + 1];
  char     address[MaxAddress + 1];
  unsigned id;
  char     dept;
  float    salary;
} Emp;


/* Not a good idea! */
Emp populate_emp1(Emp e) {
  /* fill in the fields */
  return e;
}

/* Far better idea */
void populate_emp2(Emp* e_ptr) {
  /* fill in the fields */
}

/* ok */
Emp* create_emp() {
  return (Emp*) malloc(sizeof(Emp));
}

int main() {
  Emp* fred = create_emp();
  populate_emp1(*fred);  /* bad */
  populate_emp2(fred);   /* good */

  Emp betty;
  populate_emp1(betty);  /* bad */
  populate_emp2(&betty); /* good */

  /* process fred and other Emps as needed */
  free(fred); /* critical */
  /*...*/
  return 0;
}
