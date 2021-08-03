#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define SIZE 1024

void *matrixMul(void *arg);

pthread_t threads[SIZE];

double matrixA[SIZE][SIZE], matrixB[SIZE][SIZE], matrixC[SIZE][SIZE];

int main(){
    static int i;

    srand(time(NULL));
    for(int i = 0; i < SIZE; i++){
        for(int j=0; j < SIZE; j++){
            matrixA[i][j] = rand() % 20;
            printf("%.2f", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    srand(time(NULL));
    for(int i = 0; i < SIZE; i++){
        for(int j=0; j < SIZE; j++){
            matrixB[i][j] = rand() % 20;
            printf("%.2f", matrixB[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //creates a thread for each row
    for(int i = 0; i < SIZE; i++)
        pthread_create(&threads[i], NULL, matrixMul, (void*)(size_t)i);

    //wait for each thread to finish and close
    for(int i = 0; i < SIZE; i++)
        pthread_join(threads[i], NULL);

    //print out matrixC after is has been changed
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            printf("%.2f ", matrixC[i][j]);
        }
        printf("\n");
    }
    
}

void *matrixMul(void *arg){
    for(int j = 0; j < SIZE; j++){
        double temp = 0;
        for(int k = 0; k < SIZE; k++){
            temp += matrixA[(int)(size_t)arg][k] * matrixB[k][j]; 
        }
        matrixC[(int)(size_t)arg][j] = temp;
    }

}