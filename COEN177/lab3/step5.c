#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);
    if (fork() == 0){
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n", argc);
        close(fds[0]);
       for(i = 0; i < argc; i++){
            write(fds[1], argv[i], strlen(argv[i]));
            write(fds[1], " ", 1);
        }
        exit(0);
    }
    else if(fork() == 0){
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]); 
        count = read(fds[0], buff, 60);
        printf("Received: %s\n", buff);
        printf("\n");
        exit(0);
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}