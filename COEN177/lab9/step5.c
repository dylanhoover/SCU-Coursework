#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

int SIZE;
char inputter[20];
//char outputter[20];

void *helper(void *arg){
    char outputter[20];
    FILE *in = fopen(inputter, "rb");
    char buffer[SIZE];
    sprintf(outputter, "output%d.txt", (int)arg);
    FILE *out = fopen(outputter, "wb");
    while(fread(buffer, SIZE, 1, in)){
        fwrite(buffer,SIZE, 1, out);
    }
    sleep(1);
    
    fclose(in);
    fclose(out);
    return NULL;
}

int main(int argc, char *argv[]){
    SIZE = atoi(argv[2]);
    int NTHREADS = atoi(argv[3]);
    pthread_t threads[NTHREADS];
    strcpy(inputter, argv[1]);
    printf("%s\n", inputter);
    static int i;
    for(i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, helper, (void *)(size_t)i);
    for(i = 0; i < NTHREADS; i++)
        pthread_join(threads[i],NULL);
    return 0;
}