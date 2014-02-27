#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BuffSize (4096)

void error_msg(const char* msg, int halt_flag) {
    perror(msg);
    if (halt_flag) exit(-1);
}

int main() {
  
  const int port = 80;  /* default port for a Web server */

  /* a very simple GET request */
  const char* request = 
    "GET /~mkalin/index.html HTTP/1.1\nhost: condor.depaul.edu\n\n";
  /* GET /~mkalin/index.html   ;; first-line in request
     host: condor.depaul.edu   ;; first and only line of header, a hash
     <newline>                 ;; two newlines signal end of header
     <newline>
                               ;; a GET request has no body
  */
  
  int sock, n;
  struct sockaddr_in serv_addr;
  struct hostent* server;
  char buffer[BuffSize + 1];
 
  /* get the server information */
  server = gethostbyname("condor.depaul.edu");
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

  /* write to the socket */
  n = write(sock, request, strlen(request));
  if (n < 0) error_msg("Can't write to socket.", 0);

  /* read from the socket and print what comes back from server */
  bzero(buffer, BuffSize + 1);
  n = read(sock, buffer, BuffSize);
  if (n < 0)  error_msg("Can't read from socket.", 0);
  printf("%s\n", buffer);

  if (close(sock) < 0) error_msg("Can't close socket.", 0);

  return 0;
}
/* output

HTTP/1.1 200 OK
Date: Fri, 30 Jun 2006 19:34:43 GMT
Server: Apache/2.0.53  HP-UX_Apache-based_Web_Server (Unix) PHP/4.3.8
Last-Modified: Mon, 12 Jun 2006 21:39:27 GMT
ETag: "edf4-35a-c8daa1c0"
Accept-Ranges: bytes
Content-Length: 858
Content-Type: text/html


<title>Course Listings</title>
<head>
<title>Textbook and Course Listings</title>
</head>
<p>
<hr>
<h2>WWW Pages for Textbooks</h2>
<h3>
<body>
<p>
<ul>
<li><a HREF="ed3/">Applications Programming in ANSI C (3rd edition)</a><p>
<li><a HREF="cse/">C for Scientists and Engineers</a><p>
<li><a HREF="apc/">Applications Programming in C++</a><p>
<li><a HREF="oop2/">Object-Oriented Programming in C++ (2nd edition)</a><p>
<li><a HREF="oopj/">Object-Oriented Programming in Java</a><p>
</h3>
</ul>
<p>
<hr>
<h2>Graph Generation Program
<h3>
<ul>
<li><a href="http://condor.depaul.edu/~rjohnson/source/graph_ge.c">graph_ge.c</a>
</ul>
<p>
<hr>
<h2>WWW Pages for Courses: Summer 1, 2006</h2>
<h3>
<body>
<p>
<ul>
<li><a href="http://condor.depaul.edu/~mkalin/csc373/index.html">
    CSC 373: Computer Systems 1</a></li>
</ul></body></html>
*/


