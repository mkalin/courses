#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxName    (60)
#define MaxString (250)

typedef unsigned int bool;
enum truth_values { false = 0, true }; 

typedef struct Emp {
  unsigned char lname[MaxName + 1]; /* + 1 for '\0' */
  unsigned char fname[MaxName + 1];
  unsigned int  id;
  unsigned char dept;
  bool          married;
} Emp; /* on a straight count, 131 bytes */

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

/* safest */
void to_string(Emp* this, char* buffer) {
  unsigned char temp[32];

  printf("\n** Employee information **");
  
  strcpy(buffer, "");

  strcat(buffer, "\nLast name:   "); 
  strcat(buffer, this->lname);
  strcat(buffer, "\nFirst name:  ");
  strcat(buffer, this->fname);  

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

/* ok */
unsigned char* to_string2(Emp* this) {
  unsigned char temp[256];

  char* buffer = malloc(256);

  printf("\n** Employee information **");
  
  strcpy(buffer, "");

  strcat(buffer, "\nLast name:   "); 
  strcat(buffer, this->lname);
  strcat(buffer, "\nFirst name:  ");
  strcat(buffer, this->fname);  

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
  return buffer;
}

/* DIASTER: never do this! (gcc compiler issues warning.) */
unsigned char* to_string3(Emp* this) {
  unsigned char buffer[256];
  unsigned char temp[32];

  printf("\n** Employee information **");
  
  strcpy(buffer, "");

  strcat(buffer, "\nLast name:   "); 
  strcat(buffer, this->lname);
  strcat(buffer, "\nFirst name:  ");
  strcat(buffer, this->fname);  

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

  return buffer;
}

void dump_addresses(Emp* emp) {
  printf("Address of Emp:     %p\n", emp);
  printf("Address of lname:   %p\n", emp->lname);
  printf("Address of fname:   %p\n", emp->fname);
  printf("Address of id:      %p\n", &emp->id);
  printf("Address of dept:    %p\n", &emp->dept);
  printf("Address of married: %p\n", &emp->married);
}

int main() {
  /* Seed the pseudo-random number generator with the current time. 
     An Emp's id is set to a pseudo-random number. */
  srand(time(0)); 

  Emp fred;
  /* sizeof(fred) also would work. */
  printf("sizeof(Emp) is %i\n", sizeof(Emp)); /* 136 on my system */

  dump_addresses(&fred);
  /* on my system:

     Address of Emp:     0xbff7b1a0 (3220681120)
     Address of lname:   0xbff7b1a0 (3220681120)
     Address of fname:   0xbff7b1dd (3220681181)
     Address of id:      0xbff7b21c (3220681244)
     Address of dept:    0xbff7b220 (3220681248)
     Address of married: 0xbff7b224 (3220681252)
  */

  /* Give fred's properties some values */
  set_name(fred.lname, "Flintstone");
  set_name(fred.fname, "Fred");
  set_id(&fred.id);

  set_dept(&fred.dept, 'Z');
  set_married(&fred.married, true);

  /* preferred to_string */
  unsigned char buffer[256];
  to_string(&fred, buffer);
  printf("%s\n", buffer);
  /* output:

      ** Employee information **
      Last name:   Flintstone
      First name:  Fred
      Employee id: 2084589247
      Department:  Z
      Married?:    yes 
  */

  /* to_string2: same output as above */
  unsigned char* ptr = to_string2(&fred);
  printf("%s\n", ptr);
  free(ptr);  /* critical */

  /* to_string3: if it doesn't crash, it's pure luck.
     (In this case, it's because nothing is called 
     after to_string3.)
  */
  printf("%s\n", to_string3(&fred));
  
  return 0;
}
