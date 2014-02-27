#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>

typedef struct hostent host_info;

void show_bytes(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = 0; i < how_many; i++) printf(" %.2x", ptr[i]);
  printf("\n");
}

void dump_host_aux(host_info* host_ptr) {
  if (host_ptr == NULL) return;
  /* Here's the hostent structure layout:

     struct hostent {
        char*    h_name;       ;; official name
        char**   h_aliases;    ;; alias list
        int      h_addrtype;   ;; host address type 
        int      h_length;     ;; length of address 
        char**   h_addr_list;  ;; list of addresses 
     };
  */
  printf("\n");
  printf("Official name: %s\n", host_ptr->h_name);

  printf("Aliases: ");
  int i = 0;
  while (host_ptr->h_aliases[i] != NULL) {
    printf("%.21s\n", host_ptr->h_aliases[i]);
    i++;
  }
  
  int type = host_ptr->h_addrtype;
  const char* type_str = (type == 2) ? "AF_INET" : "AF_INET6";

  printf("Host type: %s\n", type_str);

  printf("Address length: %i\n", host_ptr->h_length);

  printf("Addresses: ");
  i = 0;
  while (host_ptr->h_addr_list[i] != NULL) {
    struct in_addr addr;
    addr.s_addr = *((unsigned int*) host_ptr->h_addr_list[i]);
    if (i > 0) printf("           ");
    printf("%.21s\n", inet_ntoa(addr));
    i++;
  }
  printf("\n");
}

void dump_host(const char* host_name) {
  host_info* host = gethostbyname(host_name);
  dump_host_aux(host);
}

int main() {

  /* host and network byte order */
  int n = 0xabcdef12;
  show_bytes("IA32 int:", (unsigned char*) &n, sizeof(int));
  unsigned u = htonl(n);
  show_bytes("htonl:", (unsigned char*) &u, sizeof(unsigned));
  u = ntohl(u);
  show_bytes("ntohl:", (unsigned char*) &n, sizeof(int));
  /* output:

     IA32 int: 12 ef cd ab
     htonl:    ab cd ef 12
     ntohl:    12 ef cd ab
  */

  /* dotted-decimal addresses in network byte order */
  struct in_addr inet_address;
  int flag = inet_aton("140.192.1.6", &inet_address);
  if (flag) {
    unsigned long addr = inet_address.s_addr;
    show_bytes("inet_aton:", (unsigned char*) &addr, sizeof(unsigned long));
    /*
        inet_aton: 8c c0 01 06 ;; 140 192 1 6
    */
  }

  /* some lookup stuff */
  dump_host("condor.depaul.edu");
  dump_host("www.google.com");
  dump_host("www.yahoo.com");
  dump_host("localhost");
  /* output:

    Official name: condor.depaul.edu
    Aliases:
    Host type:AF_INET
    Address length: 4
    Addresses: 140.192.1.6

    Official name: www.l.google.com
    Aliases: www.google.com
    Host type: AF_INET
    Address length: 4
    Addresses: 72.14.203.104
               72.14.203.99

    Official name: www.yahoo.akadns.net
    Aliases: www.yahoo.com
    Host type: AF_INET
    Address length: 4
    Addresses: 68.142.197.66
               68.142.197.74
               68.142.197.79
               68.142.197.82
               68.142.197.84
               68.142.197.85
               68.142.197.87
               68.142.197.90

    Official name: localhost.localdomain
    Aliases: localhost
    Host type: AF_INET
    Address length: 4
    Addresses: 127.0.0.1
  */

  return 0;
}
