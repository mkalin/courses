#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MaxBuffer (1024)

typedef struct List {
  char         data[MaxBuffer + 1];
  struct List* next;
} List;

typedef List* Link;

Link make_node() {
  return malloc(sizeof(List));
}

Link add_node(Link node, char* content) {
  Link t = make_node();
  if (!t) return;

  node->next = t;
  strncpy(t->data, content, MaxBuffer);
  t->next = 0;
  return t;
}

void traverse_list(Link node) {
  while (node) {
    printf("%s\n", node->data);
    node = node->next;
  }
}

int main() {
  /* basics of internal representation and operations */
  int n = 0xffffffff; /* -1 */
  
  printf("n     ==> %i\n", n);
  printf("!n    ==> %i\n", !n);
  printf("-n    ==> %i\n", -n);
  printf("~n    ==> %i\n", ~n);
  printf("n ^ n ==> %i\n", n ^ n);
  printf("n & n ==> %i\n", n & n);

  printf("~n + 1 == -n: %i\n", -n == (~n + 1));

  /* Computing what? */
  int k = 1;
  while ((n = (n << 1)) < 0) {
    printf("n: %i\n", n);
    k++;
  }
  printf("k == %i\n", k);


  /* Computing what? */
  n = 1;
  while (n > 0) n = n << 1;
  printf("n + 1 == %i\n", -(n + 1));

  printf("\n");
  int d3[2][3][2];
  int* p = (int*) d3;
  int i = 1;
  while (i < 13) *p++ = i++;

  i = 0;
  while (i < 12) printf("%i ", ((int*) d3)[i++]);
  printf("\n");

  /* What's printed? */
  int h = sizeof(d3) / 12;
  *(((int*) d3) + h) = 0xffffffff;
  i = 0;
  while (i < 12) printf("%i ", ((int*) d3)[i++]);
  printf("\n");

  Link head = make_node();
  Link node;
  node = add_node(head, "Hello, world!");
  node = add_node(node, "This is an intermediate node.");
  node = add_node(node, "That's all, folks!");

  traverse_list(head);
  return 0;
}
/*
  n     ==> -1
  !n    ==>  0
  -n    ==>  1
  ~n    ==>  0

  n ^ n  ==>  0
  n & n  ==> -1

  ~n + 1 == -n: 1

  n: -2
  n: -4
  n: -8
  n: -16
  n: -32
  n: -64
  n: -128
  n: -256
  n: -512
  n: -1024
  n: -2048
  n: -4096
  n: -8192
  n: -16384
  n: -32768
  n: -65536
  n: -131072
  n: -262144
  n: -524288
  n: -1048576
  n: -2097152
  n: -4194304
  n: -8388608
  n: -16777216
  n: -33554432
  n: -67108864
  n: -134217728
  n: -268435456
  n: -536870912
  n: -1073741824
  n: -2147483648

  k == 32
  n + 1 == 2147483647
  
  1 2 3 4  5 6 7 8 9 10 11 12 
  1 2 3 4 -1 6 7 8 9 10 11 12 
  
  Hello, world!
  This is an intermediate node.
  That's all, folks!
*/
