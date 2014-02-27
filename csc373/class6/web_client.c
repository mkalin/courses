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
Date: Tue, 30 Jun 2009 22:53:41 GMT
Server: Apache/2.0.53  HP-UX_Apache-based_Web_Server (Unix) PHP/4.3.8
Last-Modified: Mon, 15 Jun 2009 20:16:33 GMT
ETag: "17870-512-bbfa8a40"
Accept-Ranges: bytes
Content-Length: 1298
Content-Type: text/html

<title>Course Listings</title>

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
<body class = 'body'>
<h3><center>Minimalist Homepage for Marty Kalin</center></h3>
<hr/>
<h4>Books</h4>
<div><a href="http://oreilly.com/catalog/9780596521127/">
  Java Web Services: Up and Running</a></div>
<div><a HREF="ed3/">Applications Programming in ANSI C (3rd edition)</a><div>
<div><a HREF="cse/">C for Scientists and Engineers</a><div>
<div><a HREF="apc/">Applications Programming in C++</a><div>
<div><a HREF="oop2/">Object-Oriented Programming in C++ (2nd edition)</a><div>
<div><a HREF="oopj/">Object-Oriented Programming in Java</a><div>
<hr>
<h4>Graph Generation Program
</h4>
<div><a href="http://condor.depaul.edu/~rjohnson/source/graph_ge.c">graph_ge.c</a></div>
<hr/>
<h4>E-mail</h4>
<div><a class = 'links' href="mailto:kalin@cs.depaul.edu">kalin@cs.depaul.edu</a></div>
<hr/>
<h4>Current Courses</h4>
<h4>
<ul>
<li><a href="csc373/index.html">CSC373: Computer Systems 1</a></li>
</ul>
</h4>
</body>
</html>
*/
