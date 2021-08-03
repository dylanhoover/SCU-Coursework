//Name: Dylan Hoover
//Data: 1/7/2021
//Title: Lab 1 sample code
//This code breaks out into a parent and child process using fork


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
    pid_t pid;
    int i, n = atoi(argv[1]); //n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    if (pid){
        //parent process
        for(i = 0; i < 100; i++){
            printf("\t \t \t Parent Process %d \n", i);
            usleep(n);
        }
    }
    else{
        //child process
        for(i = 0; i < 100; i++){
            printf("Child process %d\n", i);
            usleep(n);
        }
    }
    return 0;
}