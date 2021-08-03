/********************************************/
/*  Program college.c by Dylan Hoover 2019  */
/*         Term Project Application 1       */
/* This program is the main function for a  */
/* data set program, the program generates  */
/* 1000 random students, ID's and age, and  */
/* inserts them in the data set, random     */
/* student is then created to be found,     */
/*  Program college.c by Dylan Hoover 2019  */
/*                                          */
/* This program is the main function for a  */
/* data set program, the program generates  */
/* 1000 random students, ID's and age, and  */
/* inserts them in the data set, random     */
/* student is then created to be found,     */
/* then a random age is generated to delete */
/* the entire list of ID's based on the age */
/********************************************/


#include "set.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_STUDENTS 3000

int main()
{
    srand(time(NULL)); 

    int idCount, firstNum, id, age;
    int idPrev = 0;
    int i;

    SET *college;
    college = createDataSet(MAX_STUDENTS);

    for(i = 0; i < 1000; i++)
    {
        firstNum = (rand() % (2+1-1)+1); //random number of either 2 or 1
        //each ID is the previous one plus the newly generated one
        id = firstNum + idPrev;
        idPrev = id;
        age = (rand() % (30+1-18)+18); //random age between 18 and 30
        insertElement(college, age, id);
        idCount++;
    }

    /* Random student to search for */
    int sAge = (rand() % (30+1-18)+18);
    int sID = (rand() % (2000+1-1)+1);
    searchStudent(college, sAge, sID);

    /* Random age to delete */
    int dAge = (rand() % (30+1-18)+18);
    deleteElement(college, dAge);

    maxAgeGap(college);

    destroySet(college);

}