//TCP Server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define SIZE 1024

int main(){
 //initialize time
 time_t now;
 time(&now);

 //set up file stuff
 FILE *fp;
 char *filename = "send.txt";
 char buffer[SIZE];
 
 //Declare socket file descriptor. All Unix I/O streams are referenced by descriptors
 int sockfd, connfd, rb, sin_size;

 //Declare receiving and sending buffers of size 1k bytes
 char rbuf[1024], sbuf[1024];

 //Declare server address to which to bind for receiving messages and client address to fill in sending address
 struct sockaddr_in servAddr, clienAddr;

 //Open a TCP socket, if successful, returns adescriptor associated with an endpoint
 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Failure to setup an endpoint socket");
    exit(1);
 }

 //Setup the server address to bind using socket addressing structure
 servAddr.sin_family = AF_INET;
 servAddr.sin_port = htons(5000);
 servAddr.sin_addr.s_addr = INADDR_ANY;

 //Set address/port of server endpoint for socket socket descriptor
 if ((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0){
    perror("Failure to bind server address to the endpoint socket");
    exit(1);
 }

 printf("Server waiting for client at port 5000\n");

 // Server listening to the socket endpoint, and can queue 5 client requests
 listen(sockfd, 5);
 sin_size = sizeof(struct sockaddr_in);

while (1){
 //Server accepting to establish a connection with a connecting client, if successful, returns a connection descriptor  
 if ((connfd = accept(sockfd, (struct sockaddr *)&clienAddr, (socklen_t *)&sin_size)) < 0){
	perror("Failure to accept connection to the client");
    exit(1);
 }

fp = fopen(filename, "r");
         if(fp == NULL){
            perror("Error in reading file.");
            exit(1);
         }

 //Connection established, server begins to read and write to the connecting client
 printf("Connection Established with client: IP %s and Port %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));
 while ((rb = recv(connfd, rbuf, 1024,0))>0){
		rbuf[rb] = '\0';
		printf("Client sent: %s\n", rbuf);
      if(strcmp(rbuf, "How are you?") == 0){
         char buffer[1024] = "I am fine";
	      send(connfd, buffer, sizeof(buffer), 0);
      }
      else if(strcmp(rbuf, "Time?") == 0){
         send(connfd, ctime(&now), 1024,0);
      }
      else if(strcmp(rbuf, "File") == 0){
         while(!feof(fp)){
            int bytes_read = fread(&buffer, 1, sizeof(buffer), fp);
            send(connfd, buffer, bytes_read, 0);
         }
      }
      else{
         send(connfd, "Not an option", 1024, 0);   
      }
    }
    close(connfd);
}
fclose(fp);
close(sockfd);
return 0;
}
