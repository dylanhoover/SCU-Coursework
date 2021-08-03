// Dylan Hoover
// Lab 4
// 1/28/2021
// This program is a tcp server that sends a file to connected client

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SIZE 40
#define N 10

void* fileTransfer();

pthread_t clients[N];
int tidCount = 0;
FILE *src;

//declare socket file descriptor
    int sockfd, connfd;
    int sin_size;

//declare server address
struct sockaddr_in serverAddr, clientAddr;

int main(int argc, char *argv[]){



    //open tcp socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Failure to setup endpoint socket");
        exit(1);
    }

    //setup server address to bind using socket addressing structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    //set address/port of server endpoint for socket descriptor
    if(bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) < 0){
        perror("Failure to bind server address to the endpoint socket");
        exit(1);
    }

    printf("Server waiting for client at port 5000\n");

    //Server listening to the socket endpiont, and can queue 5 clients
    listen(sockfd, 5);
    sin_size = sizeof(struct sockaddr_in);

    while(1){
        connfd = accept(sockfd, (struct sockaddr *)&clientAddr, (socklen_t *)&sin_size);
        puts("A new connection accepted");
        if(pthread_create(&clients[tidCount], NULL, fileTransfer, (void*) &connfd) < 0){
            perror("Unable to create a thread");
            return 1;
        }
        else{
            printf("Thread has been created\n");
            tidCount++;
        }
        pthread_detach(clients[tidCount]);
    
    }

    close(sockfd);

}


void* fileTransfer(void * sock){
    char buffer[SIZE];
    int sockNum = *(int*) sock;
    size_t readFile;

    printf("Connection established with client: IP %s and Port %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

    //open file and send to client
    FILE *fp;
    fp = fopen("src.txt", "r");

    if(fp == NULL){
        perror("Unable to open file");
        exit(1);
    }

    while((readFile = fread(&buffer, sizeof(char), sizeof(buffer), fp))){
        write(sockNum, buffer, readFile);
        printf("%d\n",readFile );
    }

    printf("File transfer complete\n");
    fclose(fp);
    
}
