/* client.c

   To execute on a standalone machine, do the following:

   (1) Start the server with a specified port number (e.g., 9876).

   (2) Start the client (this compiled file). A sample start:

            client localhost 9876

       where the 1st command-line argument is the server's name
       and the second is the port number.
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BuffSize (2048)

void error_msg(const char* msg, int halt_flag) {
    perror(msg);
    if (halt_flag) exit(-1);
}

int main(int argc, char** argv) {
  /* usage */
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <hostname> <port>.\n", argv[0]);
    return -1;
  }
  
  int sock, port, n;
  struct sockaddr_in serv_addr;
  struct hostent* server;
  char buffer[BuffSize + 1];
  
  /* get the server information */
  server = gethostbyname(argv[1]);
  if (server == NULL) error_msg("No such host.", 1);
  port = atoi(argv[2]);

  /* create socket descriptor */
  sock = socket(AF_INET,           /* address family */
		  SOCK_STREAM,     /* type: in this case, TCP based */
		  0);              /* protocol: 0 means get from 2nd arg */
  if (sock < 0) error_msg("Can't get socket descriptor.", 1);

  /* fill in the fields of the server's address structure */
  bzero(&serv_addr, sizeof(serv_addr));  /* zero everything out to begin */
  serv_addr.sin_family = AF_INET;        /* address family */
  /* copy from the hostent structure into the server address structure */
  bcopy((unsigned char*) server->h_addr, 
	(unsigned char*) &serv_addr.sin_addr.s_addr,
	server->h_length);
  serv_addr.sin_port = htons(port); /* host endian to network endian */

  /* try to connect to the server */
  if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) 
    error_msg("Can't connect.", 1);

  /* prompt user for a message to send to server */
  printf("Enter a message: ");
  /* note that the buffer is of size BuffSize + 1, where the + 1
     accommodates the null terminator. in the call to fgets, the
     second argument is BuffSize, thereby ensuring enough room that
     a buffer overflow won't occur. 
  */
  bzero(buffer, BuffSize + 1);     /* zero out the buffer */
  fgets(buffer, BuffSize, stdin);  /* read from the standard input */

  /* write to the socket */
  n = write(sock, buffer, strlen(buffer));
  if (n < 0) error_msg("Can't write to socket.", 0);

  /* read from the socket and print what comes back from server */
  bzero(buffer, BuffSize + 1);
  n = read(sock, buffer, BuffSize);
  if (n < 0)  error_msg("Can't read from socket.", 0);
  printf("%s\n", buffer);

  if (close(sock) < 0) error_msg("Can't close socket.", 0);

  return 0;
}
