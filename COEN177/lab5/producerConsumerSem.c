#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>


#define BUFSIZE 10
#define NP 2
#define NC 2

pthread_t tidP[NP], tidC[NC];
int buff[BUFSIZE];
sem_t *mutex, *full, *empty;
int p = 0;
int c = 0;
int in, out;
int count;

void *producer(void *arg){
    int item;
    int p = (int)arg;
    srand(time(0));
    do{
        sem_wait(empty);
        //while(count == BUFSIZE)
        sem_wait(mutex);  //entering critical section
        item = (rand() % 100);
        buff[in] = item;  //putting item in buffer
        printf ("Producer #: %d produced item: %d at buffer space: %d\n", p, item, in);
        in = (in + 1)%BUFSIZE;
        count++;
        sem_post(mutex); //exit critical section
        sem_post(full);  //ready for a consumer
        sleep(1);
    }while(1);
}

void *consumer(void *arg){
    int item;
    int c = (int)arg;
    do{
        sem_wait(full);
        //while(count == 0)
        sem_wait(mutex);  //entering critical section
        item = buff[out];  //getting item from buffer
        printf ("\t\t\tConsumer #: %d consumed item: %d at buffer space: %d\n", c, item, out);
        out = (out + 1)%BUFSIZE;
        count--;
        sem_post(mutex);  //exit the critical section
        sem_post(empty); //ready for a producer
        sleep(3);
    }while(1);
}


void cleanup(int sigtype){
    //cleaning up as threads are done
    sem_unlink("mutex");
    sem_unlink("full");
    sem_unlink("empty");
    printf("\n Terminating\n");
    exit(0);
}



int main() {
    //sem_init(&full, 0, 0);
    //sem_init(&empty, 0, BUFSIZE);
    //sem_init(&mutex, 0, 1);
    signal(SIGINT,cleanup);
    mutex = sem_open("mutex", O_CREAT, 0644, 1);  //init known name semaphores
    full = sem_open("full", O_CREAT, 0644, 1);
    empty = sem_open("empty", O_CREAT, 0644, BUFSIZE);
    
    for(p = 0; p < NP; p++) //create producer threads
        pthread_create(&tidP[p], NULL, producer, (void *)(size_t)p);
    for(c = 0; c < NC; c++) //create consumer threads
        pthread_create(&tidC[c], NULL, consumer, (void *)(size_t)c);
    for (p = 0; p < NP; p++) { //have the producer threads call on main thread to wait
        pthread_join(tidP[p], NULL);
        printf("Producer thread %d returned\n", p);
    }
    for (c = 0; c < NC; c++) { //have the consumer threads call on main thread to wait
        pthread_join(tidC[c], NULL);
        printf("\t\t\tConsumer thread %d returned\n", c);
    }
    //cleaning up as threads are done
    sem_unlink("mutex");
    sem_unlink("full");
    sem_unlink("empty");
    printf("\nMain thread finished\n");
    return 0;
    
}