#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

#define BUFF_SIZE (1024)

enum {false, true};    /* 0 and 1, respectively */
typedef unsigned bool; /* bool aliases unsigned int */

/* Print error message and halt if specified. */
void error_msg(const char* msg, bool halt_flag) {
    perror(msg);
    if (halt_flag) exit(-1);
}

/* Create a server socket for accepting client connections. */
int create_server_socket(bool non_blocking) {
  /* Modify these as needed. */
  const int port = 3000; /* port at which the server listens */
  const int backlog = 8; /* max number of pending connections */
  
  /* Address structure for socket. */
  struct sockaddr_in server_addr;
  
  /* Try to create a socket for the server. */
  int sock = socket(AF_INET,     /* address family */
		    SOCK_STREAM, /* type: in this case, TCP based */
		    0);          /* protocol: 0 means infer from 2nd arg */
  if (socket < 0) error_msg("Problem with socket call", true);

  /* Make the socket non-blocking if specified. */
  if (non_blocking) fcntl(sock, F_SETFL, O_NONBLOCK);
  
  /* Bind the socket to an address structure. */
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port); /* host to network endian */
  if (bind(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) 
    error_msg("Problem with bind call", true);

  /* Listen for and accept incoming requests. */  
  fprintf(stderr, "Listening for requests on port %i...\n", port);
  if (listen(sock, backlog) < 0)
    error_msg("Problem with listen call", true);

  return sock;
}

void announce_client(struct in_addr* addr) {
  char buffer[BUFF_SIZE + 1];

  /* Dump client's IP (in dotted-decimal format) to stderr. */
  inet_ntop(AF_INET, addr, buffer, sizeof(buffer));
  fprintf(stderr, "Client connected from %s...\n", buffer);
}

void generate_echo_response(char request[ ], char response[ ]) {
  bzero(response, sizeof(response));
  strcpy(response, "HTTP/1.1 200 OK\n");
  strcat(response, "Content-Type: text/*\n");
  strcat(response, "Accept-Ranges: bytes\n"); 
  strcat(response, "Connection: close\n\n");
  strcat(response, request);
}

int main() {
  /* Avoid zombies by having parent ignore forked child's exist status. */
  signal(SIGCHLD, SIG_IGN);

  /* Buffer for I/O operations. */
  char buffer[BUFF_SIZE + 1];      

  /* Arguments for the accept call. */
  struct sockaddr_in client_addr;
  socklen_t len = sizeof(struct sockaddr_in);

  /* Create a server socket to accept client connections. */
  int sock = create_server_socket(false);

  /* Accept requests indefinitely. */
  while (true) {
     int client = accept(sock, 
			(struct sockaddr*) &client_addr, 
			&len);
    if (client < 0) error_msg("Problem with accept call", true);

    announce_client(&client_addr.sin_addr);

    /* Fork a process to handle client and resume awaiting new requests. */
    pid_t pid = fork();
    if (pid < 0) error_msg("Problem with fork call", false);

    /* If fork succeeds, it returns 0 to the child. */
    if (0 == pid) {  /* child rather than parent */
      /* Close the child's inherited copy of the listening socket. */
      close(sock);

      /* Read a client request. */
      bzero(buffer, sizeof(buffer));
      int bytes_read = recv(client, buffer, sizeof(buffer), 0); /* 0 == no flags */
      if (bytes_read < 0) error_msg("Problem with recv call", false);
      
      /* Send a response. */
      char response[BUFF_SIZE * 2]; /* twice as big to be safe */
      generate_echo_response(buffer, response);
      int bytes_written = send(client, response, strlen(response), 0); /* 0 == no flags */
      if (bytes_written < 0) error_msg("Problem with send call", false);

      close(client); /* clean up */
      exit(0);       /* terminate child process */
    } /* if (0 == pid) */
    else             /* parent rather than child */
      close(client); /* parent's copy */
  } /* while(true) */

  return 0; 
}
