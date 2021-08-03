# ifndef LIST_H
# define LIST_H

typedef struct list LIST;

typedef struct node
{
    struct node *next;
    struct node *prev;
    int *ID;
}NODE;

struct list
{
    int count;
    NODE *head;
    NODE *tail;
};

extern LIST *createList();
extern void destroyList(LIST *lp);
extern void addLast(LIST *lp, int *ID);
extern int numItems(LIST *lp);
extern void removeItem(LIST *lp);
extern void searchID(LIST *lp, int ID, bool *found);
extern void destroy(LIST *lp);

# endif /* LIST_H */
