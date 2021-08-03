// Name: Dylan Hoover
// Date: April 9 2021
// Title: Lab2 - 7 Process Forking
// Description: This program forks until exactly 7 process are made, including the parent.


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]){
    pid_t childL, childR;
    pid_t childLL, childLR;
    pid_t childRL, childRR;

    childL = fork();

    //If id = 0
    if(childL == 0){
        
        childLL = fork(); //child from child

        if(childLL == 0){
            printf("ChildLL %d PID %d PPID (Left-Left) \n\n", getpid(), getppid());
            exit(0);
        }
        else{
            childLR = fork(); //create second child from child

            if(childLR == 0){ //if id = 0 
                printf("ChildLR %d PID %d PPID(Left-Right)\n\n", getpid(), getppid());
                exit(0);
            }
            else{   //if id = 1 original child
                printf("ChildL %d PID %d PPID (Left)\n\n", getpid(), getppid());
                exit(0);
            }
        }

    }
    //second child
    else{
        childR = fork();

        if(childR == 0){
            childRL = fork();

            if(childRL == 0){
                printf("ChildRL %d PID %d PPID (Right-Left)\n\n", getpid(), getppid());
                exit(0);
            }
            else{
                childRR = fork();

                if(childRR == 0){
                    printf("ChildRR %d PID %d PPID (Right-Right)\n\n", getpid(), getppid());
                    exit(0);
                }
                else{
                    printf("ChildR %d PID %d PPID (Right)\n\n",getpid(), getppid());
                }
            }
        }
        else{
            printf("Parent %d PID\n\n", getpid());
        }
    }
    
}