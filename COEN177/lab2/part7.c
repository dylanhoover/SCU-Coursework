// Name: Dylan Hoover
// Date: April 9 2021
// Title: Lab2 - Part 7: Two process
// Description: This program is the same as part 1 but utilizes a system call to exec()

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
    pid_t pid;
    int i, n = atoi(argv[1]);
    printf("\n Before forking. \n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    else if(pid == 0)
        execlp("/bin/ls", "ls", NULL);
    else{
        wait(NULL);
        printf("Child Complete");
        exit(0);
    }
    return 0;
}