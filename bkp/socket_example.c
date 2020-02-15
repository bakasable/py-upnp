/*
 * This program creates a datagram socket, binds a name to it, and
 * then reads from the socket.
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
   int sock, length;
   struct sockaddr_in name;
   char buf[1024];
   /* Create a socket from which to read. */
   sock = socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
      perror("opening datagram socket");
      exit(1);
   }

   /* Create name with wildcards. */
   name.sin_family = AF_INET;
   name.sin_addr.s_addr = INADDR_ANY;
   name.sin_port = htons(5550); 
   if (bind(sock, (struct sockaddr *)&name, sizeof(name))) {
      perror("binding datagram socket");
      exit(1);
   } 

   /* Find assigned port value and print it out. */
   length = sizeof(name);
   if (getsockname(sock, (struct sockaddr *)&name, &length)) {
      perror("getting socket name");
      exit(1);
   }

   printf("Socket has port #%d\n", ntohs(name.sin_port));
   /* Read from the socket. */
   if (read(sock, buf, 1024) < 0)
      perror("receiving datagram packet");
   printf("-->%s\n", buf);
   close(sock);
}
