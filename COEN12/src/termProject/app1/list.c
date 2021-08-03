/****************************************/
/* Program: list.c by Dylan Hoover 2019 */
/*                                      */
/* This program creates a doubly linked */
/* list using the given information     */
/*                                      */
/* This program is intended to be used  */
/* in conjunction with dataSet.c        */
/****************************************/



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

/*
Function: createList
Usage: Creates a doubly linked list with both a head and tail pointer
Runtime: O(1)
*/
LIST *createList()
{
    LIST *lp = malloc(sizeof(LIST)); //allocate the list
    assert(lp != NULL);
    lp->count = 0;
    lp->head = malloc(sizeof(NODE)); //allocate the head pointers
    assert(lp->head != NULL);
    //make the dummy node, make the list ciruclar
    lp->head->next = lp->tail;
    lp->head->prev = NULL;
    lp->tail = lp->head;
    lp->tail->next = NULL;
    return lp;
}

void destroy(LIST *lp)
{
    assert(lp != NULL);
    NODE *pDel, *pNext;
    pDel = lp->head;
    do
    {
        pNext = pDel->next;
        free(pDel);
        pDel = pNext;
    } while (pDel != lp->head);
    free(lp);
}


/*
Funtion: addLast
Usage: Adds the passed data to the list, creates a new node and adds it at the end of the list for simplicity and faster Runtime while using the tail pointer
Runtime: O(1)
*/

void addLast(LIST *lp, int *ID)
{
    assert(lp != NULL);
    NODE *new = malloc(sizeof(NODE)); //allocate the new node
    NODE *p;
    //place data into the node
    new->ID = ID;
    if(lp->count == 0) //when the list is empty the head needs to point to the first node and tail as to be set
    {
        lp->head->next = new;
        new->prev = lp->head;
        new->next = lp->tail->next;
        lp->tail = new;
        lp->count++;
        return;
    }
    else
    {
        /*When it is not the first node the tail node is used to insert the node because it is always inserted at the end of the lsit*/
        new->prev = lp->tail->prev;
        new->next = lp->tail->next;
        lp->tail->prev->next = new;
        lp->tail = new;
        lp->count++;
        return;
    }
    
}

/*
Function: removeItem
Usage: removes all the nodes from a given list, freeing all of them in an iterative fashion because the count of the list is known
Runtime: O(n)
*/
void removeItem(LIST *lp)
{
    assert(lp != NULL);
    NODE *pDel = lp->head->next; //set pDel to head to start at the begining
    NODE *qDel;
    int i;
    /*iterative can be used because the count of the list is known*/
    for(i = 0; i < lp->count; i++)
    {
            qDel = pDel;
            pDel = pDel->next;
            free(qDel);
    }
}

/*
Function: numItems
Usage: returns the number of items in the given list
Runtime: O(1)
*/
int numItems(LIST *lp)
{
    assert(lp != NULL);
    return(lp->count);
}

/*
Function: searchID
Usage: searches the list for the given ID number using an iterative search because the length is known
Runtime: O(n)
*/
void searchID(LIST *lp, int ID, bool *found)
{
    assert(lp != NULL);
    NODE *p = lp->head->next;
    printf("Searching for student with ID: %d\n", ID);
    int i;
    /*iterative use is the same as in removeItem*/
    for(i = 0; i< lp->count; i++)
    {
        if(*p->ID == ID)
        {
            *found = true;
            printf("Student with ID: %d found\n", ID);
            return;
        }
        p = p->next;
    }
    printf("Student with ID: %d not found\n", ID);
    *found = false;
}