#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>

#define BUFF_SIZE  (1024)
#define MAX_EVENTS   (12)

enum {false, true};    /* 0 and 1, respectively */
typedef unsigned bool; /* bool aliases unsigned int */

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
  /* Buffer for I/O operations. */
  char buffer[BUFF_SIZE + 1];      

  /* Data structures for epoll. */
  struct epoll_event event, event_buffers[MAX_EVENTS];
  
  /* Create the epoll descriptors. */
  int epollfd = epoll_create1(0); 
  if (epollfd < 0) error_msg("Problem with epoll_create1", true);
  int epollfds = epoll_create(MAX_EVENTS);
  if (epollfds < 0) error_msg("Problem with epoll_create", true);

  /* Arguments for the accept call. */
  struct sockaddr_in client_addr;
  socklen_t len = sizeof(struct sockaddr_in);

  /* Create a non-blocking server socket to accept client connections. */
  int sock = create_server_socket(true);

  /* Initialize polling. */
  event.events = EPOLLIN | EPOLLET; /* incoming events, edge-triggered */
  event.data.fd = sock;   /* register the listening socket */
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &event) < 0) 
    error_msg("Problem with epoll_ctl call", true);
  
  /* Await events and handle as needed. */
  while (true) {
    /* Await events (no delay). System will store event info in the buffers. */
    int n = epoll_wait(epollfd, event_buffers, MAX_EVENTS, -1);
    if (n < 0) error_msg("Problem with epoll_wait call", true);

    /* Loop through the events, checking for two possibilities:

       -- If the listening socket has a new connection, then
          add the connecting client to the polling process. There
	  may be multiple connecting clients or none at all.

       -- If there's data from a connected client, then read the data and
          echo the data back as a response. There may be no data to 
	  read from a given client.
    */
    int i;
    for (i = 0; i < n; i++) {
      /* Check for connecting events on the listening socket. */
      if (event_buffers[i].data.fd == sock) {
	/* Multiple clients may connect at once so handle them all. */
	while (true) {
	  socklen_t len = sizeof(client_addr);
	  int client = accept(sock,
			      (struct sockaddr *) &client_addr, 
			      &len);

	  /* If there's no client, continue for-looping. */
	  if (client < 0 && (EAGAIN == errno || EWOULDBLOCK == errno)) break;
	  
	  /* Otherwise, register the client for polling. */
	  fcntl(client, F_SETFD, O_NONBLOCK); 
	  event.events = EPOLLIN | EPOLLET; /* incoming, edge-triggered */
	  event.data.fd = client;
	  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, client, &event) < 0)
	    error_msg("Problem with epoll_ctl ADD call", false);	  
	  
	  announce_client(&client_addr.sin_addr);
	} /* nested while (true) loop */
      }
      /* Check for read events on the client sockets. */
      else {
	/* Try to read a client request. */
	bzero(buffer, sizeof(buffer));
	int bytes_read = read(event_buffers[i].data.fd, buffer, sizeof(buffer)); 

	/* If there are bytes, echo them back to the client. */
	if (bytes_read > 0) {
	  /* Send a response. */
	  char response[BUFF_SIZE * 2]; /* twice as big to be safe */
	  generate_echo_response(buffer, response);
	  int bytes_written = send(event_buffers[i].data.fd, response, strlen(response), 0); /* 0 == no flags */
	  if (bytes_written < 0) error_msg("Problem with send call", false);
	
	  /* Stop polling this client and close the connection. */
	  if (epoll_ctl(epollfd, EPOLL_CTL_DEL, event_buffers[i].data.fd, &event) < 0)
	    error_msg("Problem with epoll_ctl DEL call", false);
	  close(event_buffers[i].data.fd); 
	}  /* if (bytes_read > 0) */
      } /* else -- client read events */
    } /* for-loop through event buffers */
  } /* while (true) */

  return 0;
}
