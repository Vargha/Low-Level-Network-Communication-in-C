/* * * * * * * * * * * * * * * * *
 * Vargha Hokmran  SID: 11543295 *
 * CS-360    Systems Programming *
 * Assignment-9         Networks *
 * * * * * * * * * * * * * * * * */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <errno.h>
# include <unistd.h>  // for close() and write()
# include <time.h>
# include <sys/wait.h>

# define MY_PORT_NUMBER 49999
# define BUFFER_SIZE 1024

int main(){
  struct hostent* hostEntry;
  char serverHostName[1024] = "\0";
  gethostname(serverHostName, 1023);      // get this machin's host name
  int listenfd;   // my socket, almost nothing more than a number
  if ( (listenfd=socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
		perror("Socket");
		exit(1);
  }

  // Setting Server Speifications
  struct sockaddr_in servAddr;
  struct in_addr **pptr;
  memset( &servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(MY_PORT_NUMBER);
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  // Bind the socket to my port
  if ( bind (listenfd, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0){
		perror("bind");
		exit(1);
  }

  listen( listenfd, 1);   // 1 level deep
  int connectfd;
  int length = sizeof(struct sockaddr_in);
  struct sockaddr_in clientAddr;
  
  while (1){
    if ((connectfd = accept(listenfd,    (struct sockaddr*) &clientAddr,     &length)) < 0){
      printf("Problem in connection\n");
      exit(1);
    }
    if (!fork()){   // Creating 1 Chile, per while loop **
      char* clientHostName;
      hostEntry = gethostbyaddr(&(clientAddr.sin_addr), sizeof(struct in_addr), AF_INET);
      clientHostName = hostEntry->h_name;
      printf ("%s\n", clientHostName);      // logs the hostname of the client to stdout
      time_t t = time(NULL);
      struct tm* tm = localtime(&t);
      char sendBuff[BUFFER_SIZE] = "\0";
      strcpy (sendBuff, ctime(&t));
      write(connectfd, sendBuff, strlen(sendBuff));
      close(connectfd);   // close the connection in child side **
      exit(0);
    }
    else  // in parent side
    {
      int status;
      waitpid(-1,&status ,0);   // Waiting for 1 child to die, per while loop
      close(connectfd);   // close the connection in parent side
    }
  }
  return 0;
}
