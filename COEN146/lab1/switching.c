//Name: Dylan Hoover
//Data: 1/7/2021
//Title: Lab 1 steps 6-7
//This code calculates probability values for circuit and packet switching

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int factorial(int n){
    double result = 1;
    for(int i = 1; i <= n; i++){
        result = (result * i);
    }
    return result;
}

double binomial(double x, double y){
    double result = (factorial(x)/factorial(y)*factorial(x - y));
    return result;
}

int main(int argc, char *argv[]){
    int linkBandwidth = atoi(argv[1]);
    int userBandwidth = atoi(argv[2]);
    double tPSuser = atof(argv[3]);
    int nPSusers = atoi(argv[4]);

    //step 6
    int nCSusers = linkBandwidth/ userBandwidth;
    printf("6a - nCSusers: %d \n", nCSusers);

    //step 7a
    double pPSusers = tPSuser;
    printf("7a - pPSusers: %lf \n", pPSusers);

    //step 7b
    double pPSusersNotBusy = 1 - pPSusers;
    printf("7b - pPSusersNoyBusy: %lf \n", pPSusersNotBusy);

    //step 7c
    double all = pow((1-pPSusers),(nPSusers - 1));
    printf("7c - Probability of all other users: %e \n", all);

    //step 7d
    double notTransmitting = pPSusers * pow(pPSusersNotBusy, (nPSusers - 1));
    printf("7d - Probability that one specific user is transmitting and remaining users are not: %e \n", notTransmitting);  

    //step 7e
    double onlyOne = nPSusers * notTransmitting;
    printf("7e - Probability that exactly one user is busy: %e \n", onlyOne);

    //step 7f
    double onlyTen = pow(pPSusers, 10) * pow(pPSusersNotBusy, (nPSusers - 10));
    printf("7f - Probability that 10 specific users are transmitting: %e \n", onlyTen);

    //step 7g
    double coefficient = binomial(nPSusers, 10);
    double anyTen = coefficient * pow(pPSusers, 10) * pow(pPSusersNotBusy, (nPSusers-10));
     printf("7g - Probability that any 10 users are transmitting: %e \n", anyTen);

    //step 7h
    double sum = 0;
    for(int i = 11; i <= nPSusers; i ++){
        sum += binomial(nPSusers, i) * pow(pPSusers, i) * pow(pPSusersNotBusy, (nPSusers-i));
    }
    printf("7h - Probability that more than 10 users are transmitting: %e \n", sum);
}