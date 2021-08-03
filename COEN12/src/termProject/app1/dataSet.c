/*************************************************/
/*     Program: dataSet.c by Dylan Hoover 2019   */
/*        Term project Application 1             */
/* This program takes in integers and creates a  */
/* sorted array based on one value and then      */
/* creates a chained array, using a linked list  */
/* with the other value                          */
/*                                               */ 
/* This program must be used in conjunction with */
/* a linked list data structure program for the  */
/* chaining to work, other wise the value is just*/
/* passed to random programs                     */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#include "list.h"

struct set
{
    LIST **list;
    int *age;
    int count;
    int length;
};
/*
Function: createDataSet
Usage: creates the data set
Runtime: O(n)
*/
SET *createDataSet(int maxStudents)
{
    //printf("creating set\n");
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxStudents;
    sp->age = malloc(sizeof(int*)*sp->length);
    sp->list = malloc(sizeof(void*)*sp->length);
    int i;
    for(i = 0; i < sp->length; i++)
    {
        sp->list[i] = createList();
    }
    assert(sp->list != NULL);
   // printf("set created\n");
    return sp;
}

/*
Function: destroySet
Usage: destroys the entire data set
Runtime: O(n)
*/
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    /*Iteratively goes down the array freeing the the list*/
     for(i = 0; i<sp->count; i++)
    {
        destroy(sp->list[i]);
    }
    //free the rest of the array
    free(sp->age);
    free(sp->list);
    free(sp);
}

/*
Function: compare
Usage: Used by the search function to compare the given age and the current middle value of the array
Runtime: O(1)
*/
int compare(int age, SET *sp, int mid)
{
    assert(sp != NULL);
    int test = sp->age[mid]; //set the test number to the middle number
    if(test > age) //if its bigger return a negative
        return(-1);
    else if(test < age) //if its smaller return a positive
        return(1);
    else //return 0 when they are equal
        return(0);
}

/*
Function: searchAge
Usage: Uses binary search to go through the sorted array searching for the correct position for the age
Runtime: O(logn)
*/
int searchAge(SET *sp, int age, bool *found)
{
    int lo, hi, mid;
    int i;
    lo = 0;
    hi = (sp->count -1);
    printf("Searching for a student aged %d\n", age);
    while(lo<=hi)
    {
        mid = (lo+hi)/2;
        if(compare(age, sp, mid) < 0) //when compare is less than 1 the top half of the array doens't have the string
        {
            hi = mid -1; //hi is now mid, begin again
        }
        else if(compare(age, sp, mid) > 0) //when compare is greater than 0 the bottom half of the array doesn't have the string
        {
            lo = mid +1; //lo is now mid
        }  
        else 
        {
            //when the string is found mid is the location
            *found = true;
            printf("Student found\n");
            return(mid);
        }
    }
    *found = false;
    printf("No student with that age\n");
    return(lo);
}


/*
Function: insertElement
Usage: takes the given information and puts it through the search function, when the correct index is returned the age is added to the age array while the ID is passed to the parallel linked list array
Runtime: O(n)
*/
void insertElement(SET *sp, int age, int ID)
{
    assert(sp != NULL);
    bool found;
    int i;
    int idx = searchAge(sp, age, &found); //set the index
    if(sp->count == sp->length)
        return;
    for(i = sp->count; i > idx; i--) //insert into the array, shifting all the elements to the right
        sp->age[i] = sp->age[i-1];
    sp->age[idx] = age;
    addLast(sp->list[idx], &ID); //pass the ID to the linked list array
    sp->count++;
    return;
}

/*
Function: deleteElement
Usage: passes the given age to the search function to find the index to pass to the remove fuctnion in list.c which is O(n) runtime
Runtime: O(n)
*/
void deleteElement(SET *sp, int age)
{
    assert(sp != NULL);
    bool found;
    int idx = searchAge(sp, age, &found); //set the index

    if(found == true) //if the age is found then the index can be passed to the removeItem function to delete all the entries
    {
        printf("Attempting to remove student aged %d\n", age);
        removeItem(sp->list[idx]);
        free(sp->list[idx]);
        sp->count--;
        printf("Student removed\n");
        return;
    }
    else
    {
        printf("student does not exist\n");
    }
    
}

/*
Function: maxAgeGap
Usage: Takes the first index of the array and the last and subtracts the last from the first to find the gap
Runtime: O(1)
*/
int maxAgeGap(SET *sp)
{
    int maxAge = sp->age[sp->count]; //always the largest
    int minAge = sp->age[0]; //always the smallest
    int gap = maxAge - minAge;
    printf("The largest age Gap is %d\n", gap);
    return(gap);
}

/*
Function: searchStudent
Usage: takes the given information and searches for the age first to make sure it is there, if found the ID is searched for on that index to see if the randomized student exists
Runtime: O(logn)
*/
void searchStudent(SET *sp, int age, int ID)
{
    assert(sp != NULL);
    /*Two boolean values are needed*/
    bool foundAge;
    bool foundID;
    printf("Searching for a student aged %d with ID: %d\n", age, ID);
    int idx = searchAge(sp, age, &foundAge); //set the index
    if(foundAge == true)
    {
        searchID(sp->list[idx], ID, &foundID); //pass the ID if the age is found
        if(foundID == true)
        {
            printf("Student aged: %d with ID: %d found\n", age, ID);
            return;
        }
        else
        {
                printf("Student aged: %d with ID: %d does not exist\n", age, ID);
                return;
        }
        
    }
    else
        printf("No student aged %d\n", age);
        
}