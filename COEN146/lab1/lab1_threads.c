//Name: Dylan Hoover
//Data: 1/7/2021
//Title: Lab 1 sample code
//This code breaks out into a parent and child threads using the pthread library

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

void *routine(void *arg){
    //parent process
        for(int i = 0; i < 100; i++){
            printf("\t \t \t Parent Process %d \n", i);
            usleep(*(int*)arg);
        }
}

int main(int argc, char *argv[]){
    pid_t pid;
    int i, n = atoi(argv[1]); //n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, routine, &n);
    //child process
    for(i = 0; i < 100; i++){
        printf("Child process %d\n", i);
        usleep(n);
    }
    pthread_join(thread_id, NULL);
    return 0;
}   