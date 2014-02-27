#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE (1024) 

enum {false, true};    /* 0 and 1, respectively */
typedef unsigned bool; /* bool aliases unsigned int */

void error_msg(const char* msg, bool halt_flag) {
    perror(msg);
    if (halt_flag) exit(-1);
}

int main() {
  /* Change as needed: server name and standard HTTP port. */
  const char* host_name = "condor.depaul.edu";
  const int port = 80;

  /* Create a GET request. Format is shown below. */
  const char* request = 
    "GET /mkalin/index.html HTTP/1.1\nhost: condor.depaul.edu\n\n";
  /* GET /mkalin/index.html    ;; first-line in request
     host: condor.depaul.edu   ;; first and only line of header 
     <newline>                 ;; two newlines signal end of header
     <newline>
                               ;; a GET request has no body -- end of request
  */
  
  /* Set up the server information. */
  struct hostent* server = gethostbyname(host_name);
  if (server == NULL) error_msg("No such host", true);

  /* Create the socket. */
  int sock = socket(AF_INET,        /* address family */
		    SOCK_STREAM,    /* type: in this case, TCP based */
		    0);             /* protocol: 0 means get from 2nd arg */
  if (sock < 0) error_msg("Can't get socket descriptor", true);

  /* Fill in required info in the server's address structure. */
  struct sockaddr_in addr;
  bzero(&addr, sizeof(addr)); /* zero out the structure */
  addr.sin_family = AF_INET;  /* address family */

  /* Copy from the hostent structure into the server address structure */
  bcopy((char*) server->h_addr, 
	(char*) &addr.sin_addr.s_addr,
	server->h_length);
  addr.sin_port = htons(port); /* Set the port (host to network endian). */

  /* Try to connect to the server. */
  if (connect(sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) 
    error_msg("Can't connect to server", true);

  /* Send the GET request. */
  int n = send(sock, request, strlen(request), 0); /* 0 == no flags */
  if (n < 0) error_msg("Can't write to the socket", true);

  /* Read from the socket and print what comes back from server */
  char buffer[BUFF_SIZE + 1];
  do {
    bzero(buffer, sizeof(buffer));        /* zero out the buffer */
    n = recv(sock, buffer, BUFF_SIZE, 0); /* read the next chunk */
    if (n > 0) printf("\n### Next chunk of bytes:\n\n%s\n", buffer); 
  } while(n > 0); /* until there are no more bytes to read. */

  /* Clean up. */
  if (close(sock) < 0) error_msg("Can't close socket.", false); 

  return 0;
}
/* output

*/
