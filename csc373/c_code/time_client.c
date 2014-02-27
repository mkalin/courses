#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BuffSize (128)

void error_msg(const char* msg, int halt_flag) {
    perror(msg);
    if (halt_flag) exit(-1);
}

int main() {
  
  const int port = 13;  /* default port for a time server */
  
  int sock, n;
  struct sockaddr_in serv_addr;
  struct hostent* server;
  char buffer[BuffSize + 1];
 
  /* get the server information */
  server = gethostbyname("www.yahoo.com");
  if (server == NULL) error_msg("No such host.", 1);

  /* create socket descriptor */
  sock = socket(AF_INET,        /* address family */
		SOCK_STREAM,    /* type: in this case, TCP based */
		0);             /* protocol: 0 means get from 2nd arg */
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

  /* read from the socket and print what comes back from server */
  bzero(buffer, BuffSize + 1);
  n = read(sock, buffer, 1); /* number of bytes in typical time string */
  if (n < 0)  error_msg("Can't read from socket.", 0);
  printf("%s\n", buffer);

  if (close(sock) < 0) error_msg("Can't close socket.", 0);

  return 0;
}



