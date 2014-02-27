#include <stdio.h>
#include <stdlib.h>

char buffer[1024 + 1];

char* prompt_and_read() {
  printf("\nPlease enter a string (-1 to exit): ");
  fgets(buffer, 1024, stdin);
  return buffer;
}

int main() {
  float f = -118.6;
  printf("%f %f\n", f, (int) f >> 1);

  /*
  while (1) {
    char* ptr = prompt_and_read();
    int flag = atoi(ptr);    
    if (flag < 0) break;     
    printf("You entered: %s\n", ptr);
  }
  */
  return 0;
}
