#include <stdio.h>
#include <stdlib.h>

char buffer[1024 + 1];

char* prompt_and_read() {
  printf("\nPlease enter a string (-1 to exit): ");
  fgets(buffer, 1024, stdin);
  return buffer;
}

int main() {
  while (1) {
    char* ptr = prompt_and_read();
    int flag = atoi(ptr);    /* converts string to int */
    if (flag < 0) break;     /* break out of the loop */
    printf("You entered: %s\n", ptr);
  }
  return 0;
}
