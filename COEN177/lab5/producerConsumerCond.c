#include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <pthread.h>
 #include <signal.h>
 #include <time.h>
 #include <fcntl.h>

#define BUFSIZE 10
#define NP 4
#define NC 10

pthread_t tidP[NP], tidC[NC];
int buff[BUFSIZE];
pthread_mutex_t mutex;
pthread_cond_t full, empty;
int p = 0;
int c = 0;
int in, out;
int count;

void *producer(void *arg) {
    int data;
    int p = (int)arg;
    srand(time(0));
    do {
        data = (rand() % 100);  // random number for producer
        pthread_mutex_lock(&mutex);  //
        while(count == BUFSIZE)  //the buffer is full so cant produce to it
            pthread_cond_wait(&empty, &mutex);
        //entered the critical section
        buff[in] = data;
        printf ("Producer #: %d produced item: %d at buffer space: %d\n", p, data, in);
        in = (in +1)%BUFSIZE;
        count++;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        //exited the critical section
        sleep(1);
    } while (1);
    return (NULL);
}

void *consumer(void *arg) {
    int data;
    int c = (int)arg;
    srand(time(0));
    do {
        pthread_mutex_lock(&mutex);
        while (count == 0)  //buffer is empty so cant consume
            pthread_cond_wait(&full, &mutex);
        //entered critical section
        data=buff[out];
        printf ("\t\t\tConsumer #: %d consumed item: %d at buffer space: %d\n", c, data, out);
        out = (out+1)%BUFSIZE;
        count--;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        //exited the critical section
        sleep(3);
    } while (1);
    return (NULL);
}

void cleanup(int sigtype){
    //preparing the termination of the threads
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    printf("\n Terminating\n");
    exit(0);
}

int main () {
    signal(SIGINT, cleanup);
    pthread_mutex_init(&mutex, NULL); //initilize the mutex
    pthread_cond_init(&empty, NULL);  //initialize the conditional variables
    pthread_cond_init(&full, NULL);
    for (p = 0; p < NP; p++)  //creating the producer threads
        pthread_create (&tidP[p], NULL, producer, (void*)(size_t)p);
    for (c = 0; c < NC; c++)  //creating the consumer threads
        pthread_create (&tidC[c], NULL, consumer, (void*)(size_t)c);
    for (p = 0; p < NP; p++) {   //the producer threads calling on the main thread to wait for it
        pthread_join(tidP[p], NULL);
        printf("Producer thread %d returned\n", p);
    }
    for (c = 0; c < NC; c++) { //the consumer threads calling on the main thread to wait for it
        pthread_join(tidC[c], NULL);
        printf("\t\t\tConsumer thread %d returned\n", c);
    }
    printf("Main thread finished\n");
    //preparing to terminate the program
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    return 0;
}