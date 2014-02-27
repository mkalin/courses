#include <stdio.h>

unsigned find_ESP() {
  asm("movl %esp, %eax");
}

unsigned find_EBP() {
  asm("movl %ebp, %eax");
}

void dump_registers(const char* msg ) {
  unsigned esp = find_ESP();
  unsigned ebp = find_EBP();

  printf("%s\nesp ==> %x\nebp ==> %x\n", msg, esp, ebp);
}

/* p. 146 in text */
int arith(int x, int y, int z) {
  dump_registers("\nstart of arith");
  int t1 = x + y;   /* movl 12(%ebp), %eax        ;; %eax = y */
                    /* addl  8(%ebp), %eax        ;; t1 = x + y */

  dump_registers("\ninside arith");

  int t2 = z * 48;  /* movl 16(%ebp), %edx        ;; %edx = z */
                    /* leal means "load effective address," that is,
                       load a memory address into a register. Howerver,
                       it also can used as a hack to express basic arithmetic
                       operations. In the example below, the expression
                       leal (%edx, %edx, 2) means "add %edx to itself twice."
                       Note that one copy of z is already in %edx so that, in
                       effect, we're tripling z. The second operand is %edx, 
                       the destination.
                    /* leal (%edx, %edx, 2), %edx ;; z = z * 3 */

                        /* sall $4, %edx  ;; t2 = z * 48 (sall is SHIFT LEFT) */

  int t3 = t1 & 0xffff; /* andl $65535, %eax ;; 0xffff == 65,535 */

  int t4 = t2 * t3;     /* imull %eax, %edx  ;; t4 = t2 * t3 */

  dump_registers("\nend of arith");

  return t4;            /* movl %edx, %eax   ;; %eax holds return value */
}

int main() {
  dump_registers("\nstart of main");
  int ans = arith(1, 2, 3);
  dump_registers("\nmiddle of main");
  printf("return from arith is %d\n", ans);  /* 432 */
  dump_registers("\nend of main");

  return 0;
}
/* output on a sample run (commas added for readability):
start of main
esp ==> bfe3caa8
ebp ==> bfe3caa8

start of arith
esp ==> bfe3ca78
ebp ==> bfe3ca78

inside arith
esp ==> bfe3ca78
ebp ==> bfe3ca78

end of arith
esp ==> bfe3ca78
ebp ==> bfe3ca78

middle of main
esp ==> bfe3caa8
ebp ==> bfe3caa8
return from arith is 432

end of main
esp ==> bfe3caa8
ebp ==> bfe3caa8
*/







