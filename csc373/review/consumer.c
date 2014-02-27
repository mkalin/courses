/** Consumer
 * Consumes bytes from a file created by the producer.
 *    Random number of bytes consumed at random intervals.
 *    Sleeps inbetween consumptions.
 *    Signals producer that it has consumed.
 *    Consumes indefinitely.
 *    In principle, consumes all bytes produced in the order of 
 *      their production.
 *    Logs consumptions to the standard output.
**/


/* Invoke as: consumer <data file from producer> <flag file> */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/** globals **/
#define MaxFileName (200)
const unsigned true = 1;
const unsigned false = 0;
char flagFile[MaxFileName + 1];
char inputFile[MaxFileName + 1];
const unsigned NoSuchFile = -1;
const unsigned MaxZs = 4;
const unsigned MaxProducts = 10;

/* Returns a named file's size in bytes, or
   NoSuchFile if the file does not exist.
*/
unsigned fileSize(const char name[]) {
   FILE* fptr = fopen(name, "rb");
   unsigned n = 0;
   if (!fptr) // NULL == does not exist
     return NoSuchFile;
   while (fgetc(fptr) != EOF)
     n++;
   fclose(fptr);
   return n;
}

/* Returns a random integer in the range 1 to k */
unsigned ran(unsigned k) {
   return 1 + rand() * (k / (RAND_MAX + 1.0));
}

/* Sleep for z ticks. */
void sleep(unsigned z) {
   time_t now = time(0);
   while (difftime(time(0), now) < z)
      ;
}

void setFlag() {
   FILE* fptr;
   do {
     fptr = fopen(flagFile, "a");
   } while (!fptr);
   fputc('!', fptr);
   fclose(fptr);
}

int main(int argc, char* argv[]) {   
   /* locals */
   FILE* infile;
   unsigned n = 0, i, count;
   unsigned long readCount = 0, size;
   int byte;

   /* See random number generator */
   srand(time(0));

   /* Get file names from command line and store them. */
   if (argc < 3) {
     fprintf(stderr, "***** Invoke as: consumer <read file> <flag file>\n");
     exit(EXIT_FAILURE);
   }
   strcpy(inputFile, argv[1]);
   strcpy(flagFile, argv[2]);

   while (true) { /*** consume forever ***/
      /* Anything to read? */
      do {
        infile = fopen(inputFile, "rb"); /* read mode */
        if (!infile)
          sleep(ran(MaxZs));
      } while (!infile);
    
      /* Read new bytes, if any. */
      size = fileSize(inputFile);      
      if (size > readCount) { /* anything new? */
        char buf[100];
        /* Move beyond bytes already read. */
        fseek(infile, readCount, SEEK_SET); 
        count = 0;
        n = ran(MaxProducts);
        while (count < n) {
          buf[count++] = fgetc(infile);
          readCount++;
          if (readCount >= size) 
            break;
        }
        setFlag();
        fclose(infile);
        buf[count] = '\0';
        fprintf(stdout, "%s\n", buf); /* log to standard output */
      } /* if(fileSize > readCount) */
      sleep(ran(MaxZs));
   }
   return 0;
}

