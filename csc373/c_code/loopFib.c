/* fibonacci number N is defined recursively as

               1 if n <= 2
   Fib(n) =
               Fib(n - 1) + Fib(n - 2) if n > 2

   The sequence starts 1, 1, 2, 3, 5, 8, 13, 21, 34, 55,...
*/
int fib_recursive(int n) {
  if (n <= 2) return 1;
  return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int fib_dw(int n) {
  int i = 0;         /* loop counter */
  int val = 0;   
  int next = 1;  

  /* Assembler for the loop:

       ;; %eax holds temp
       ;; %ebx holds val
       ;; %edx holds next
       ;; %ecx holds i
       ;; %esi holds the parameter, n

     .L6:
         leal (%edx, %ebx), %eax  ;; temp = val + next
	 movl %edx, %ebx          ;; val = next
	 movl %eax, %edx          ;; next = temp
         incl %ecx                ;; i += 1
         cmpl %esi, %ecx          ;; (i < n) ?
         jl .L6                   ;; if (i < n) goto .L6
         movl %ebx, %eax          ;; return val
  */
  do {
    int temp = val + next;
    val = next;
    next = temp;
    i++;
  } while(i < n);

  return val;
}

int fib_w(int n) {
  /* Assembler for fib_w:

       ;; %eax holds n and then temp (after .L10)
       ;; %ebx holds val
       ;; %ecx holds next
       ;; %edx holds i

           movl 8(%ebp), %eax       ;; get parameter n
	   movl $1, %ebx            ;; val = 1
           movl $1, %ecx            ;; next = 1
	   cmpl %eax, %ebx          ;; (val > n) ?
           jge .L9                  ;; if (val >= n) return
           leal -1(%eax), %edx      ;; i = n - 1
     .L10:
           leal (%ecx, %ebx), %eax  ;; temp = next + val
           movl %ecx, %ebx          ;; val = next
           movl %eax, %ecx          ;; next = temp
	   decl %edx                ;; i--
           jnz  .L10                ;; if (i != 0) goto .L10
     .L9:       
  */
  int i = 1;
  int val = 1;
  int next = 1;

  while (i < n) {
    int temp = val + next;
    val = next;
    next = temp;
    i++;
  }
  
  return val;
}

int main() {
  int i;
  for (i = 1; i < 8; i++) {
    printf("Fib(%i) == %i (recursive) and %i (dw) and %i (w)\n",
	   i, fib_recursive(i), fib_dw(i), fib_w(i));
  }

  return 0;
}
