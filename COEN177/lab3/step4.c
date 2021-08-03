#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int fds[2];
    pipe(fds);

    if(fork() == 0){
        dup2(fds[0], 0);
        close(fds[1]);
        //need to now do the /bin/grep part
        execlp("/bin/grep", "grep", "root", 0);
    }
    else if(fork() == 0){
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("/bin/cat", "cat", "/etc/passwd", 0);
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}