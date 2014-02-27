#include <stdio.h>
#include <string.h>

#define BuffSize (1000)
#define MaxIndent (12)

int main() {
  
  unsigned char buffer[BuffSize + 1];
  while (fgets(buffer, BuffSize, stdin) != 0) {
    unsigned char* ptr = buffer;
    unsigned int n = 0;

    while (isspace(*ptr)) ptr++;
    while (isdigit(*ptr) && ++n < MaxIndent) ptr++;
    if (*ptr == '\t') ptr++;
    printf("%s", ptr);
  }
  return 0;
}
