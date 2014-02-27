#include <stdio.h>
#include <stdlib.h>

#define FileName "test.out"

int main() {
  FILE *fptr;
  char  string[80];
  int   n;

  if((fptr = fopen(FileName, "w")) == 0) { 
    printf("Can't open file.\n");
    exit(-1);
  }
  
  printf("Enter a string and a number: ");
  fscanf(stdin, "%s%d", string, &n); /* read from keyboard */

  fprintf(fptr, "%s %d", string, n); /* write to the file */
  fclose(fptr); 

  if((fptr = fopen(FileName, "r")) == 0) {
    printf("Cannot open file.\n");
    exit(-1);
  }

  fscanf(fptr, "%s%d", string, &n);      /* read from file */
  fprintf(stdout, "%s %d\n", string, n); /* print to screen */
  fclose(fptr);

  return 0;
}
