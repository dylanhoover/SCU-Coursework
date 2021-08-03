#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char*argv[]){

    int RTT0 = 3;
    int RTT1 = 20;
    int RTT2 = 26;
    int HTTPRTT = 47;
    int n = atoi(argv[1]);

    //part a
    int a = RTT0 + RTT1 + RTT2 + (2*HTTPRTT);
    printf("Time it takes to receive 1 object: %d\n", a);

    //part b
    int b = RTT0 + RTT1 + RTT2 + (14*HTTPRTT);
    printf("Time it takes to receive 6 objects: %d\n", b);


    double packets = (n >= 6) ? 1: 6.0/n;
    int parallel = ceil(packets);

    //part c non-persistant
    int c = RTT0 + RTT1 + RTT2 + (2*HTTPRTT) + (2 * parallel * HTTPRTT);
    printf("Time it takes to receieve 6 objects with n parallel connections and non-persistent HTTP: %d\n", c);

    //part c persistant
    int c2 = RTT0 + RTT1 + RTT2 + (2 *HTTPRTT) + (parallel * HTTPRTT);
    printf("Time it takes to receieve 6 objects with n parallel connections and persistent HTTP: %d\n", c2);

}
