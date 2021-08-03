#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t m; //setup mutex

void* go(void* arg) { 
  pthread_mutex_lock(&m); //lock the thread
  printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
  sleep(1); 
  pthread_mutex_unlock(&m); //unlock the thread
  return (NULL);
} 

int main() { 
    pthread_mutex_init(&m, NULL);//initialize the mutex locks
    static int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
        printf("\t\t\tThread %d returned \n", i);
    }
        printf("Main thread done.\n");
    pthread_mutex_destroy(&m); //destroy the locks upon completion of code
    return 0; 
} 