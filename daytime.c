/* * * * * * * * * * * * * * * * *
 * Vargha Hokmran  SID: 11543295 *
 * CS-360    Systems Programming *
 * Assignment-9         Networks *
 * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>  // for close() and write()

#define MY_PORT_NUMBER 49999
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]){
  if (argc != 2){   // if not host or bad cmd arg
    printf ("Program use: daytime <Host_Name / IP_Address>\n");
    exit (1);
  }
  struct sockaddr_in servAddr;

  int socketfd = socket( AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0){
    perror("socketfd");
    exit(1);
  }

  memset(&servAddr, 0, sizeof(servAddr)+1);
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(MY_PORT_NUMBER);

  struct hostent* hostEntry;
  struct in_addr **pptr;
  hostEntry = gethostbyname(argv[1]);
  /* this is magic, unless you want to dig into the man pages */
  pptr = (struct in_addr**) hostEntry->h_addr_list;
  memcpy(&servAddr.sin_addr, *pptr, sizeof(struct in_addr));

  if ((connect(socketfd, (struct sockaddr *) &servAddr, sizeof(servAddr)+1)) < 0){
    printf("Unable to connect to Server\n");
    exit(1);
  }
  char txtBuff[BUFFER_SIZE] = "\0";
  read(socketfd, txtBuff, BUFFER_SIZE-1);
  printf("%s\n", txtBuff);
  return 0;
}
