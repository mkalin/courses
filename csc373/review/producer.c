/** Producer
 *  Produces a random number of a randomly selected byte to a file.
 *  After producing MaxProducts, waits until consumer consumes at least one.
 *    Checks a flag file to see if consumer has consumed.
 *  Sleeps a random interval inbetween productions.
 *  Produces indefinitely.
 *  Logs productions to the standard output.
**/

/* Invoke as: producer <data file> <flag file> 

   producer and consumer can be started in either order.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/** globals **/
#define MaxFileName (200)

const char* products = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
unsigned productsLen;

const unsigned true = 1;
const unsigned false = 0;

unsigned readCount = 0;
unsigned okToWrite;

char flagFile[MaxFileName + 1];
char outputFile[MaxFileName + 1];

const unsigned NoSuchFile = -1;
const unsigned MaxZs = 4;
const unsigned MaxProducts = 10;

/* Returns a named file's size in bytes, or
   NoSuchFile if the file does not exist.
*/
unsigned fileSize(const char name[ ]) {
   FILE* fptr = fopen(name, "rb");
   unsigned n = 0;
   if (!fptr) return NoSuchFile;

   while (fgetc( fptr ) != EOF) n++;

   fclose(fptr);
   return n;
}

/* Returns a random integer in the range 1 to k */
unsigned ran(unsigned k) {
   return 1 + rand() * (k / (RAND_MAX + 1.0));
}

/* Sleep for z ticks. */
void sleep(unsigned z) {
   time_t now = time( 0 );
   while (difftime(time(0), now) < z)
      ;
}

/* Set okToWrite to true if consumer has consumed,
   else to false.
*/
void checkForReads() {
  unsigned n = fileSize(flagFile);
  if (readCount == n) /* any reads occur? */
    return;
  readCount = n;    /* there's been a read so update readCount */
  okToWrite = true; /* continue producing */
}

int main(int argc, char* argv[ ]) {   
   /* locals */
   FILE* outfile;
   unsigned n = 0, i, count = 0;
   int byte;

   /* See random number generator */
   srand(time(0));

   /* Get file names from command line and store them. */
   if (argc < 3) {
     fprintf( stderr, "***** Invoke as: producer <write file> <flag file>\n" );
     exit(EXIT_FAILURE);
   }
   strcpy(outputFile, argv[1]);
   strcpy(flagFile, argv[2]);

   okToWrite = true;

   productsLen = strlen(products);
   while (true) { /*** produce forever ***/
      /* Open the output file. */
      do {
        outfile = fopen(outputFile, "ab"); /* append mode */
      } while (!outfile);

      /* Is it OK to produce? */
      while (!okToWrite) {
        checkForReads();
        sleep(ran(MaxZs));
      }

      /* Pick a byte to write and how many times */
      byte = products[ran(productsLen) - 1];
      n = ran(MaxProducts);
      for (i = 0; i < n; i++) {
        fputc(byte, outfile);
        fputc(byte, stdout); /* log to standard output */
        if (++count >= MaxProducts) {
          okToWrite = false;
          count = 0;
          break;
        }
      }
      fclose(outfile);
      fputc('\n', stdout);
      sleep(ran(MaxZs));
   }
   return 0;
}

