// Name: Dylan Hoover
// Date: April 9 2021
// Title: Lab2 - Part 6: Two threads
// Description: This program performs 100 iterations of print statements for each of the two threads

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void *threadStart1(void *n){
    int i;
    for(i = 0; i < 100; i++){
        printf("\t \t Hello from thread1 %d \n\n", i);
        usleep(*((int*)n));
    }
    pthread_exit((void *)n);
}
void *threadStart2(void *n){
    int i;
    for(i = 0; i < 100; i++){
        printf("\t \t Hello from thread2 %d \n\n", i);
        usleep(*((int*)n));
    }
    pthread_exit((void*)n);
}

int main(int argc, char *argv[]){
    pthread_t tid1, tid2;
    int i, n = atoi(argv[1]);
    int *nArg = malloc(sizeof(*nArg));
    *nArg = n;
    printf("\n Before thread creation \n");
    pthread_create(&tid1, NULL, threadStart1, nArg);
    pthread_create(&tid2, NULL, threadStart2, nArg);
    pthread_join(tid1, (void**)&nArg);
    pthread_join(tid2, (void**)&nArg);
    free(nArg);
    return 0;
}