/*************************************************/
/*     Program: dataSet.c by Dylan Hoover 2019   */
/*        Term project Application 3             */
/* This program takes in integers and creates a  */
/* sorted doubly linked list, sorting based on   */
/* one of the values given                       */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dataSet.h"

typedef struct node
{
    struct node *next;
    struct node *prev;
    int age;
    int ID;
}NODE;

struct set
{
    NODE *head;
    int count;
};

/*
Function: createSet        
Usage: creates the linked list,     
allocating the head dummy node and  
pointing the node to itself to      
initizlize ciruclar                                                      
Runtime: O(1)   
*/
SET *createSet()
{
    printf("creating set\n");
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->head = malloc(sizeof(NODE));
    assert(sp->head != NULL);
    sp->head->next = sp->head;
    sp->head->prev = sp->head;
  
    return sp;
}

/*
Function: destroy    
Usage: Destroys the list   
Runtime: O(n)               
*/
void destroy(SET *sp)
{
    assert(sp != NULL);
    NODE *pDel, *pNext;
    pDel = sp->head;
    do
    {
        pNext = pDel->next;
        free(pDel);
        pDel = pNext;
    } while (pDel != sp->head);
    printf("Set destroyed, goodbye\n");
    free(sp);
}

/*
Function: searchA             
Usage: searches through the list 
for the given age incrementally  
because the length is known                                   
Runtime: O(n)                   
*/
static void *searchA(SET *sp, int age,  bool *found)
{
    assert(sp != NULL);
    printf("Searching for student aged %d\n", age);
    NODE *pSearch = sp->head->next;
    int i;
        for(i = 0; i < sp->count; i++)
        {
            if(pSearch->age == age)
            {
                
                *found = true;
                printf("Student found\n");
                return(pSearch);
            }
            pSearch = pSearch->next;
        }
        printf("Student not found\n");
        *found = false;
        return NULL;
}

/*
Function: searchB             
Usage: searches through the list 
for the given ID                                 
Runtime: O(n)                   
*/
static void *searchB(SET *sp, int ID, bool *found)
{
    assert(sp != NULL);
    
    NODE *pSearch = sp->head->next;
    do
    {
        if(pSearch->ID == ID)
            {
                *found = true;
                return(pSearch);
            }
            pSearch = pSearch->next;

    } while (pSearch != sp->head);

    *found = false;
}

/*
Function: searchAge
Usage: Used to pass the information to searchA to keep the specific search fucntions local fucntions
Runtime: O(n)
*/

void *searchAge(SET *sp, int age)
{
    assert(sp != NULL);
    bool found;
    NODE *fAge = searchA(sp, age, &found);
    return(fAge);
}

/*
Function: searchID
Usage: Used to pass the information to searchB to keep the specific search fucntions local fucntions
Runtime: O(n)
*/
void *searchID(SET *sp, int ID)
{
    assert(sp != NULL);
    bool found;
    printf("Searching for student with ID: %d\n", ID);
    NODE *fID = searchB(sp, ID, &found);
    if(found == true)
        printf("Student with ID: %d found\n", ID);
    if(found == false)
        printf("Student with ID %d does not exist\n", ID);
    return(fID);
}

/*
Function: insertElement
Usage: inserts the given information into the list by allocating a new node and searching for the correct position in the list
Runtime: O(n^2)
*/
void insertElement(SET *sp, int age, int ID)
{
    assert(sp != NULL);
    bool found;
    NODE *new = malloc(sizeof(NODE));
    new->age = age;
    new->ID = ID;
    //printf("starting search\n");
    NODE *p = searchA(sp, age, &found);
    NODE *q;
    if(found == true)
    {
        new->next = p->next;
        new->prev = p;
        p->next = new;
        sp->count++;
        return;
    }
    else
    {
        q = sp->head->next;
        
        if(sp->count == 0)
        {
            sp->head->next = new;
            new->prev = sp->head;
            new->next = sp->head;
	    sp->head->prev = new;
            sp->count++;
            return;
        }
        do
        {
            if(new->age <= q->age)
            {
                new->next = q;
                new->prev = q->prev;
                q->prev->next = new;
                q->prev = new;
                sp->count++;
                return;
            }
            q = q->next;
        } while (q->next != sp->head);
	new->next = sp->head;
	new->prev = sp->head->prev;
	sp->head->prev->next = new;
	sp->head->prev = new;
	sp->count++;
	return;
    }
   
}

/*
Function: deleteElement
Usage: takes in a given ID and deletes the NODE containing the ID
Runtime: O(n)
*/
void deleteElement(SET *sp, int ID)
{
    assert(sp != NULL);
    bool found;
    NODE *pDel = searchB(sp, ID, &found);
    if(found == true)
    {
        pDel->prev->next = pDel->next;
        pDel->next->prev = pDel->prev;
        free(pDel);
        printf("Searching for student with ID: %d\n", ID);
    }
    elseprintf("Searching for student with ID: %d\n", ID);
    {
        printf("no student with that ID\n");
    }
}

/*
Function: maxAgeGap
Usage: calculates the max age gap within the given list
Runtime: O(1)
*/

int maxAgeGap(SET *sp)
{
    assert(sp != NULL);
    int minAge = sp->head->next->age;
    int maxAge = sp->head->prev->age;
    int gap = (maxAge - minAge);
    printf("The max age gap is %d\n", gap);
    return(0);
}

/*
Function: studentSearch
Usage: searches for a student based on both age and ID, because there are multiple students of the same age ID has to be searched first then age can be compared
Runtime: O(n^2)
*/ 
void studentSearch(SET *sp, int age, int ID)
{
    assert(sp != NULL);
    bool found1;
    bool found2;
    printf("Searching for student aged: %d with ID: %d\n", age ,ID);
    searchB(sp, ID, &found1);
    if(found1 == true)
    {
        NODE *p = searchID(sp, ID);
        if(p->age != age)
            printf("Student with ID: %d and Age: %d does not exist\n", ID, age);
        else
            printf("Student found\n");
    }
    else
        printf("Student does not exist\n");
    
}