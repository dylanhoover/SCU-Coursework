// Dylan Hoover
// Lab 4
// 1/28/2021
// This program is a tcp client that requests a file from a tcp server

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

#define SIZE 40

int main(int argc, char *argv[]){

    //declare socket file descriptor
    int sockfd;

    //Declare server address to connect to
    struct sockaddr_in servAddr;
    struct hostnet *host;

    //get hostname
    host = (struct hostent *) gethostbyname("10.0.0.18");

    //Open socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("failur to setup an endpoint socket");
        exit(1);
    }

    //set server address to send using socket addressing structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5000);
    servAddr.sin_addr.s_addr = inet_addr("10.0.0.18");

    //connect socket
    if(connect(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr)) < 0){
        perror("failed to connect to socket");
        exit(1);
    }
    else{
        printf("Connected to the server\n");
    }

    char buffer[SIZE];
    FILE *fp;
    size_t readFile;
    fp = fopen("dest.txt", "w");
    while(1){
        readFile = read(sockfd, buffer, 1024);
        if(readFile < 0) perror("read");

        fwrite(&buffer, 1, readFile, fp);
        if(readFile == 0) break;
    }
    fclose(fp);
    printf("%d\n", readFile);
    //close socket descriptor
    close(sockfd);
    return 0;
}




