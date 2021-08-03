//TCP Client
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#define SIZE 1024


int main(){
char recv_data[SIZE];
FILE *dest = fopen("newfile.txt", "w");

//Declare socket file descriptor. All Unix I/O streams are referenced by descriptors. nr is a declaration of the number of recieved bytes.
int sockfd, nr;

//Declare sending and recieving buffers of size 1k bytes
char sbuf[1024], rbuf[1024];

//Declare server address to connect to
struct sockaddr_in servAddr;
struct hostent *host;

//Converts domain names into numerical IP addresses via DNS
host = (struct hostent *)gethostbyname("10.0.0.18");

//Open a socket, if successful, returns adescriptor associated with an endpoint
 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Failure to setup an endpoint socket");
    exit(1);
 }

//Set the server address to send using socket addressing structure
servAddr.sin_family = AF_INET;
servAddr.sin_port = htons(5000);
servAddr.sin_addr.s_addr = *((struct in_addr *)host->h_addr);

//Connect to the server
if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))){
    perror("Failure to connect to the server");
    exit(1);
}

 //Client begins to write and read from the server
 while(1){
  printf("Client: Type a message to send to Server\n");
  scanf("%[^\n]%*c", sbuf);
  //printf("%s", sbuf);
  send(sockfd, sbuf, strlen(sbuf), 0);
  if(strcmp(sbuf, "Send me a file") == 0){
    int bytes_read = read(sockfd, recv_data, 1024);
    if(bytes_read < 0){
        perror("read");
    }
    fwrite(&recv_data, bytes_read, 1, dest);
    printf("File recieved\n");
    fclose(dest);
  }
  else{ 
    recv(sockfd, rbuf, 1024, 0);
    printf("Server: sent message: %s\n", rbuf);
  }
 }
 //Close socket descriptor
 close(sockfd);
 return 0;
}
