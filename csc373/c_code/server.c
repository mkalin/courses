/* server.c

   A simple server in the internet domain using TCP. The port number
   is passed in as a command-line argument 

   To execute on a standalone machine, do the following:

   (1) Start the server with a specified port number (e.g., 9876):

            server 9876

   (2) Start the client. A sample start:

            client localhost 9876

       where the 1st command-line argument is the server's name
       and the second is the port number.
*/
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define BuffSize (2048)
#define MaxClients (100)

void error_msg(const char* msg, int halt_flag) {
  perror(msg);
  if (halt_flag) exit(-1);
}

int main(int argc, char** argv) {
  /* usage */
  if (argc < 2) {
    fprintf(stderr,"Usage: %s <port number>\n.", argv[0]);
    return -1;
  }

  int sock, client_sock, port, client, len, n;
  char buffer[BuffSize + 1];
  struct sockaddr_in serv_addr, client_addr;

  /* create socket descriptor */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) 
    error_msg("Can't create socket.", 1);
  
  /* fill in the server address information */
  bzero((char *) &serv_addr, sizeof(serv_addr));
  port = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);

  /* bind the socket, that is, assign a local protocol address; in
     particular, associate the s_addr in the server's address structure
     with the socket descriptor.
  */
  if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
    error_msg("Can't bind socket.", 1);
  
  while (1) {
    /* listen for client connections */
    listen(sock, MaxClients);
    
    /* when accepting a client connection, get a pointer to the client 
       socket that initiated the connection */
    len = sizeof(client_addr);
    client_sock = accept(sock, (struct sockaddr *) &client_addr, &len);
    if (client_sock < 0) error_msg("Can't accept connection.", 1);
    
    /* read from the client */
    bzero(buffer, BuffSize + 1);
    n = read(client_sock, buffer, BuffSize);
    if (n < 0) error_msg("Can't read from socket.", 1);
    printf("Client message: %s\n", buffer);
    
    /* respond to client */
    char return_buffer[BuffSize + 100];
    bzero(return_buffer, BuffSize + 100);
    strcpy(return_buffer, "Echo of your message: ");
    strcat(return_buffer, buffer);
    
    n = write(client_sock, return_buffer, strlen(return_buffer));
    if (n < 0) error_msg("Can't write to socket.", 0);
    
    /* close the socket */
    if (close(client_sock) < 0) error_msg("Can't close client socket.", 0);
  }
  return 0; 
}
