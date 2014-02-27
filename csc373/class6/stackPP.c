#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Size (16)

char stack[Size];
int top1 = 0;
int top2 = -1;

void push1(char item) {
  if (top1 >= Size) return;

  stack[top1] = item;
  top1++;
}

void push2(char item) {
  if (top2 + 1 >= Size) return;

  top2++;
  stack[top2] = item;
}

char pop1() {
  if (top1 - 1 < 0) return '\0';

  top1--;
  return stack[top1];
}

char pop2() {
  if (top2 - 1 < -1) return '\0';

  char retval = stack[top2];
  top2--;
  return retval;
}

void dump_stack1() {
  char c;
  while ((c = pop1()) != '\0') printf("%c ", c);
  printf("\n");
}

void dump_stack2() {
  char c;
  while ((c = pop2()) != '\0') printf("%c ", c);
  printf("\n");
}

void clear_stack() {
  memset(stack, '\0', Size);
}

int main() {
  char c = 'A';
  
  printf("1st approach:\n");
  int i = 0;
  while (i++ < Size) push1(c++);
  dump_stack1();

  clear_stack();

  printf("\n2nd approach:\n");
  c = 'A';
  i = 0;
  while (i++ < Size) push2(c++);
  dump_stack2();

  return 0;
}
/* output:

1st approach:
P O N M L K J I H G F E D C B A

2nd approach:
P O N M L K J I H G F E D C B A
*/
