#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>

#define BuffSize (4096)

void error_msg(const char* msg, int halt_flag) {
    perror(msg);
    if (halt_flag) exit(-1);
}

int main() {
  const int port = 80;  /* default port for a Web server */

  const char* request = 
    "GET /mkalin/index.html HTTP/1.1\nhost: condor.depaul.edu\n\n";
  /* GET /mkalin/index.html    ;; first-line in request
     host: condor.depaul.edu   ;; first and only line of header, a hash
     <newline>                 ;; two newlines signal end of header
     <newline>
                               ;; a GET request has no body -- end of request
  */
  
  int                sock, n;
  struct sockaddr_in serv_addr;
  struct hostent*    server;
  char               buffer[BuffSize + 1];
 
  /* get the server information */
  server = gethostbyname("condor.depaul.edu");
  if (server == NULL) error_msg("No such host.", -1);

  /* create socket descriptor */
  sock = socket(AF_INET,        /* address family */
		SOCK_STREAM,    /* type: in this case, TCP based */
		0);             /* protocol: 0 means get from 2nd arg */
  if (sock < 0) error_msg("Can't get socket descriptor.", -1);

  /* fill in the fields of the server's address structure */
  bzero(&serv_addr, sizeof(serv_addr)); /* zero everything out: memset is better */

  serv_addr.sin_family = AF_INET;       /* address family */

  /* copy from the hostent structure into the server address structure */
  bcopy((unsigned char*) server->h_addr, 
	(unsigned char*) &serv_addr.sin_addr.s_addr,
	server->h_length);
  serv_addr.sin_port = htons(port); /* host endian to network endian */

  /* try to connect to the server */
  if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) 
    error_msg("Can't connect.", -1);

  /* write to the socket */
  n = write(sock, request, strlen(request));
  if (n < 0) error_msg("Can't write to socket.", -1);

  /* read from the socket and print what comes back from server */
  bzero(buffer, BuffSize + 1); /* memset is better */
  n = read(sock, buffer, BuffSize);
  if (n < 0)  error_msg("Can't read from socket.", -1);
  printf("%s\n", buffer);

  if (close(sock) < 0) error_msg("Can't close socket.", -1);

  return 0;
}
/* output

   HTTP/1.1 200 OK
   Date: Wed, 15 Jun 2011 21:52:25 GMT
   Server: Apache/2.2.3 (Red Hat)
   Last-Modified: Wed, 25 May 2011 19:56:51 GMT
   ETag: "9c4654-801-4a41f1b0386c0"
   Accept-Ranges: bytes
   Content-Length: 2049
   Content-Type: text/html
   Connection: close
   
   <html>
   <title>Home page</title>
   
   <head>
   <style type = "text/css">
   .body  {background-color: rgb(225, 225, 225);}
   .links {text-decoration: none;}
   .bullets {background-color: rgb(225, 225, 225); }
   .raw {background-color: wheat; }
   h3 { color: black;}
   a { text-decoration: none; }
   </style>
   <title>Textbook and Course Listings</title>
   </head>
   <body>
   <p>
   <fieldset><legend>Basics</legend>
   <span>Martin Kalin</span><br/>
   <span>Professor and Associate Dean, College of Computing and Digital Media</span><br/>
   <span>DePaul University</span><br/>
   <span>1 East Jackson</span><br/>
   <span>Chicago, IL 60604</span><br/>
   <p><span>PhD, Northwestern University</span></p>
   </fieldset>
   </p>
   <p>
   <fieldset><legend>Books</legend>
   <div><a href="http://oreilly.com/catalog/9780596521127/">
                       Java Web Services: Up and Running</a></div>
   <div><a HREF="ed3/">Applications Programming in ANSI C (3rd edition)</a><div>
   <div><a HREF="cse/">C for Scientists and Engineers</a><div>
   <div><a HREF="apc/">Applications Programming in C++</a><div>
   <div><a HREF="oop2/">Object-Oriented Programming in C++ (2nd edition)</a><div>
   <div><a HREF="oopj/">Object-Oriented Programming in Java</a><div>
*/
