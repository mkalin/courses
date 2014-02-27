/* process.c */
#include <unistd.h>     /* symbolic constants */
#include <sys/types.h>  /* system data types */ 
#include <errno.h>      /* error codes */
#include <stdio.h>      /* printf, etc. */
#include <sys/wait.h>   /* waiting on process termination */
#include <stdlib.h>     /* utilities */
 
int main() {
  pid_t cpid;    /* process id (pid) of child or forked process */
  int   retval;  /* user-supplied return code for child */
  int   status;  /* child's exit status for parent process */
  
  /* Child process will "inherit" the three variables listed above so
     that the parent and the child now have three distinct variables
     that share the same names.
  */
  cpid = fork(); /* create the child process */
  
  /* fork succeeded */
  if (cpid >= 0) {
    printf("cpid after fork is:         %d\n\n", cpid);
 
    /* Parent and child are executing the same code; hence,
       we need to distinguish between the two. */

    /* child code */
    if (cpid == 0) { /* fork() returns 0 to the child */
      printf("Child's pid (in child):   %d\n", getpid());
      printf("Child's parent's pid:     %d\n\n", getppid());
      printf("Child sleeping for 1 second...\n");
      sleep(1); /* 1 second */
      
      printf("\nEnter an exit value (0 to 100): ");
      scanf("%d", &retval);
      printf("Child exiting...\n\n");    

      exit(retval); /* child terminates and returns status code */
    }
    /* parent code */
    else { /* fork() returns new pid to the parent process */
      printf("Parent's pid:             %d\n", getpid());
      printf("Child's  pid (in parent): %d\n", cpid);
      printf("Waiting for child to exit...\n");
      wait(&status); /* wait for child to exit and store its status code */
      printf("Child's exit code is: %d\n", WEXITSTATUS(status)); /* macro ensures normal */
      printf("Parent exiting...\n");             

      exit(0); /* parent exits with normal termination */       
    }
  }
  /* fork failed (-1 is status code) */
  else { 
    perror("fork"); /* display error message */
    exit(0); 
  }
  return 0;
}



/* output from a sample run:

   cpid after fork is:       2410

   Parent's pid:             2408
   Child's  pid (in parent): 2410
   Waiting for child to exit...
   cpid after fork is:          0
   
   Child's pid (in child):   2410
   Child's parent's pid:     2408
   
   Child sleeping for 1 second...
   
   Enter an exit value (0 to 100): 99
   Child exiting...
   
   Child's exit code is: 99
   Parent exiting...
*/
