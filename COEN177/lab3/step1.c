#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fds[2];
    pipe(fds);
    if (fork() == 0){
        dup2(fds[0] , 0);
        close(fds[1]);
        execlp("sort", "sort", 0);
    }
    else if (fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("ls", "ls", 0);
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}