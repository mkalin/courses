/* Memory layout on an Intel 32-bit microprocessor (hereafter, IA32) 

  Process address space:

  High Addresses (0xBFFFFFFF = 3,221,225,471)

     environment pointer

     DYNAMICALLY ALLOCATED STORAGE

       stack grows down    ;; parameters and local variables: LIFO behavior

       heap grows up       ;; dynamically allocated storage (malloc, calloc)
                           ;; that must be freed (free)
  
     SEGMENTS

       .data               ;; static initialized data

       .bss                ;; static uninitialized data

       .text               ;; read only: holds program instructions

     shared libraries      

  Low Addresses (0x80000000 = 2,147,483,648)

  High - Low = 3FFFFFFF (1,073,741,823) 
  So each process gets roughly 1G of virtual address space
*/

int add(int n1, int n2) {
  int ans = n1 + n2;
  return ans;
}

int main() {
  int x = add(8, 7);
  printf("%d\n", x);
  return 0;
} 

/* Here's the steps I followed to get the output shown below. This file is 
   Memory.c. I'm using $ as the command-line prompt, which becomes (gdb) inside 
   the debugger. My comments begin with ;;, the traditional comment delimiter
   in assembler.

      ;; The flag "preferred-stack-boundary" tells the compiler to increment the
      ;; stack pointer (%esp) by IA32 DWORD increments, that is, 4 bytes or 32 bits.
      ;; (In the original Intel architecure, a "word" was 16 bits; hence, a 
      ;; "double word" or dword is 32 bits and a "long word" is 64 bits.)
      ;; Without this flag, the compiler would do some funky optimizations and the
      ;; assembler would be much more difficult to read. The -ggdb option tells the
      ;; compiler to include debugging information, as we're going into the debugger.
      $ gcc -mpreferred-stack-boundary=2 -ggdb Memory.c -o Memory

      ;; debug the compiled Memory program
      $ gdb Memory
      ;; in the debugger, disassemble the function main
      (gdb) disas main

      ;; Here's the output. %ebp (extended base pointer) is the "frame pointer" and
      ;;                    %esp (extended stack pointer) is the "stack pointer"
      ;; Typically, the frame pointer serves as a fixed reference for offsets, much
      ;; as an array's name in Java (and C) serves as the base address for indexed
      ;; offsets. The frame pointer points to the "call frame," the part of the
      ;; stack allocated for a particular function call; so, in this example,
      ;; main gets its own call frame as does the function add. By contrast to the
      ;; frame pointer, the stack pointer moves around during the execution; and it
      ;; move anywhere in the stack but largely remains with a call frame.
  Dump of assembler code for function main:
  0x0804837c <main+0>:    push   %ebp       ;; 1st step in setup: push EBP onto stack  
  0x0804837d <main+1>:    mov    %esp,%ebp  ;; 2nd step: copy stack ptr into frame ptr
                                            ;; We now have a "call frame" for main.

  0x0804837f <main+3>:    sub    $0x4,%esp  ;; decrement ESP by 4 (recall that the stack
                                            ;; grows downwards so that, in effect, this
                                            ;; sets the ESP to a new TOP position
                                            ;; (Note that 4 is one DWORD)

  0x08048382 <main+6>:    push   $0x7       ;; push 7 (2nd parameter) onto stack
  0x08048384 <main+8>:    push   $0x8       ;; push 8 (1st parameter) onto stack
  0x08048386 <main+10>:   call   0x8048368 <add> ;; transfer control to add function

  0x0804838b <main+15>:   add    $0x8,%esp       ;; add has returned: add 8 to ESP
                                                 ;; (Move down the stack two DWORDS)
                                                 ;; Basically, stack ptr is now back to
                                                 ;; where it was before the arguments
                                                 ;; 7 and 8 were pushed onto it

  0x0804838e <main+18>:   mov    %eax,0xfffffffc(%ebp) ;; 0xfffffffc = 4,294,967,292 
                                                       ;; 2*32 is 4,294,967,296
                                                       ;; So the contents of EAX is
                                                       ;; is being moved from a base
                                                       ;; address + an offset
                                                       ;; Basically, return value copied
                                                       ;; into x

  0x08048391 <main+21>:   pushl  0xfffffffc(%ebp)      ;; pushl decrements stack ptr by 
                                                       ;; 2 DWORDs rather than 1
  0x08048394 <main+24>:   push   $0x8048488            ;; decrements stack ptr by 1 DWORD
  0x08048399 <main+29>:   call   0x80482b0             ;; call to printf
  0x0804839e <main+34>:   add    $0x8,%esp             ;; move stack ptr down the stack
  0x080483a1 <main+37>:   mov    $0x0,%eax             ;; put 0 in EAX
  0x080483a6 <main+42>:   leave                        ;; clear the call frame
  0x080483a7 <main+43>:   ret                          ;; return 0
  End of assembler dump.

  ;; Now here's the dump of add:
  
  Dump of assembler code for function add:
  0x08048368 <add+0>:     push   %ebp        ;; prepare call frame
  0x08048369 <add+1>:     mov    %esp,%ebp   ;; ditto

  0x0804836b <add+3>:     sub    $0x4,%esp   ;; new TOP for stack

  0x0804836e <add+6>:     mov    0xc(%ebp),%eax ;; 1st arg into EAX
  0x08048371 <add+9>:     add    0x8(%ebp),%eax ;; add 2nd arg to EAX

  0x08048374 <add+12>:    mov    %eax,0xfffffffc(%ebp) ;; return val location
  0x08048377 <add+15>:    mov    0xfffffffc(%ebp),%eax ;; copy return val into EAX
  0x0804837a <add+18>:    leave  ;; clear the call frame
  0x0804837b <add+19>:    ret    ;; return control to invoker
  End of assembler dump.
*/
