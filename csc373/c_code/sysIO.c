#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define FILE_NAME "nums.bin"

void report_and_die(const char* msg) {
  fprintf(stderr, msg);
  exit(-1);
}

int main() {
  const int bad_io = 0xffffffff;
  char error_msg[512];

  int file_descriptor = open(FILE_NAME,         /* name */
			     O_CREAT | O_RDWR,  /* create for read/write */
			     0);                /* permissions */
  if (file_descriptor == bad_io) {
    sprintf(error_msg, "Couldn't open file %s.\n", FILE_NAME);
    report_and_die(error_msg);
  }

  /* Write some data. */
  int n[ ] = { 9, 7, 5, 3, 1 };
  int read_in[5 * sizeof(int)];

  int flag = write(file_descriptor, n, sizeof(n));
  if (flag == bad_io) {
    sprintf(error_msg, "Couldn't write to file %s.\n", FILE_NAME);
    report_and_die(error_msg);
  }
  
  flag = close(file_descriptor);
  if (flag == bad_io) {
    sprintf(error_msg, "Couldn't close file %s.\n", FILE_NAME);
    report_and_die(error_msg);
  }
  
  ssize_t in_flag = read(file_descriptor, read_in, sizeof(read_in));
  
  if (in_flag == bad_io) {
    sprintf(error_msg, "Couldn't read from file %s.\n", FILE_NAME);
    report_and_die(error_msg);
  }

  file_descriptor = open(FILE_NAME, O_RDONLY, 0);
  if (file_descriptor == bad_io) {
    sprintf(error_msg, "Couldn't open file %s for reading.\n", FILE_NAME);
    report_and_die(error_msg);
  }

  flag = read(file_descriptor, read_in, sizeof(read_in));
  
  

  return 0;
}
