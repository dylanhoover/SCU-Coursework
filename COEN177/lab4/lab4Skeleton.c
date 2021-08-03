// Lab4 - skeleton for step 3
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//values of N,M, and L 
#define N 1024  
#define M 1024
#define L 1024

pthread_t threads[N];

//A, B, C matrices
double matrixA[N][M], matrixB[M][L], matrixC[N][L];

//function prototypes
void initializeMatrix(int r,int c, double matrix[r][c]);
void *multiplyRow(void* arg);
void printMatrix(int r,int c, double matrix[r][c]);

int main(){
	int i;
	initializeMatrix(N, M, matrixA);  //initilaize matrixA with random values
	initializeMatrix(M, L, matrixB); //initialize matrixB with random values
	//create N threads, each multiplying row A by all columns fo B to produce row of C
	//your code
	for(i = 0; i < N; i++){
		pthread_create(&threads[i], NULL, multiplyRow, (void*)(size_t)i); //runs through a for loop creating the threads to multiply each row individually, one thread per row
	}

	//Main thread waits for child threads to complete
	for(i=0;i<N;i++){
		pthread_join(threads[i],NULL); //runs through a for loop joining the threads one by one
	}
	//Print Matrix A, B, and C
	//your code
	//passes the size and matrices to the print matrix function
	printf("Printing MatrixA: \n");
	printMatrix(N, M, matrixA);
	printf("\n");
	printf("Printing MatrixB: \n");
	printMatrix(M,L, matrixB);
	printf("\n");
	printf("Printing MatrixC: \n");
	printMatrix(N,L, matrixC);

	return 0;
}

//Initialize matrixA and matrixB with random values
void initializeMatrix(int r,int c, double matrix[r][c]){
	srand(time(NULL));
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++)
			matrix[i][j] = rand() % 20; //set to only go up to 20
	}

}

//thread function: multiply row of A by columns of B --> row of C
void* multiplyRow(void* arg){
	for(int j = 0; j < L; j++){ //row of first matrix loop
		double temp = 0;
		for(int k = 0; k < M; k++){ //columns of second matrix loop
			temp += matrixA[(int)(size_t)arg][k] * matrixB[k][j]; //sets a temp variable to hold the answer of the multiplication
		}
		matrixC[(int)(size_t)arg][j] = temp; //sets the correct row of matrix C to the temp variable
	}

    return 0;
}

//Print matrices
void printMatrix(int r,int c, double matrix[r][c]){
	int i, j;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++)
			printf("%lf ",matrix[i][j]);
		printf("\n");
	}
}