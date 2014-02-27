/* Problem 3: What does the function mystery do?
   You should answer at two levels. First, explain in general what it 
   does by giving some sample inputs and outputs. For example, on a 
   sample run I got

            1234 ===> -771489792

   as my output. How did the function mystery map 1234 to -771489792?
   If you know how the function works, you might also suggest a better
   name for it.

   Second, document the lines of code in the function. There are four
   such lines, involving shifts and logical-ands. What do they do?
*/

#include <stdio.h>
#include <stdlib.h>

unsigned int mystery2(unsigned int n) {
  /* >> is the right-shift operator. The shift is logical, not arithmetic,
     because the data type is unsigned. (P. 50 in the textbook.)
     << is the left-shift operator.
     & is the bitwise logical-and operator.
     | is the bitwise logical-or operator.
  */
  unsigned int temp = 
    (n >> 24) | 
    ((n << 8) & 0x00FF0000) |
    ((n >> 8) & 0x0000FF00) |
    (n << 24);
  
  return temp;
}

unsigned int prompt_and_read() {
  unsigned int next;
  printf("\nprompt> Please enter an integer (0 to exit): ");
  scanf("%u", &next);
  if (next == 0) exit(0);
  return next;
}

int main() {
  while (1) {
    unsigned int next = prompt_and_read();
    unsigned int result = mystery2(next);
    printf("%d ===> %d\n", next, result);
  }
  return 0;
}

/* 

On a few sample runs, some of the answers I obtained are as follows:
5 ===> 83886080
1 ===> 16777216
1561 ===> 419823616

The user is prompted to enter a number through the prompt_and_read function.  The input is scanned from the keyboard and is assigned to the variable
"next".  An if statement has been set so that if the user enters in a "0" then the system will exit.
  
Once a value has been entered, the main function will call the prompt_and_read function and assign the obtained value to "next".  Once the value of
next has been assigned, the function mystery2 is called using the assigned value for next.  The function mystery2 will change the byte order.  The 
result of mystery2 is assigned to the variable "result".  The program will then output the value that the user entered as well as the result.  Since
this is in a while loop, it will continue as long as the loop is true and does not equal 0.

The four lines that involve shifts and logical-ends are lines 27, 28, 29, and 30.  An unsigned int has a byte size of 4.
Line 27 will move a byte 24  bytes (or 6 places) to the right
Line 28 will move a byte 8 bytes (2 places) to the left...and the hex denotes the 2nd value?
Line 29 will move a byte 8 bytes (2 places) to the right...and the hext denotes the 3rd value?
Line 30 will move a byte 24 bytes (or 6 places) to the left
