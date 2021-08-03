/********************************************/
/*  Program college.c by Dylan Hoover 2019  */
/*      Term Project Application 3          */
/* This program is the main function for a  */
/* data set program, the program generates  */
/* 1000 random students, ID's and age, and  */
/* inserts them in the data set, random     */
/* student is then created to be found,     */
/* then a random age is generated to delete */
/* the entire list of ID's based on the age */
/********************************************/

#include "dataSet.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


int main()
{
    srand(time(NULL)); 

    int idCount, firstNum, id, age;
    int idPrev = 0;
    int i;

    SET *college;
    college = createSet();

    for(i = 0; i < 1000; i++)
    {
        firstNum = (rand() % (2+1-1)+1);
        id = firstNum + idPrev;
        idPrev = id;
        age = (rand() % (30+1-18)+18);
        printf("new student aged %d, with ID: %d\n", age, id);
        insertElement(college, age, id);
        idCount++;
    }

    int sID = (rand() % (2000+1-1)+1);
    int sAge = (rand() % (30+1-18)+18);
    studentSearch(college, sAge, sID);

    int dID = (rand() % (2000+1-1)+1);
    deleteElement(college, dID);

    maxAgeGap(college);

    destroy(college);

}