#ifndef SET_H
#define SET_H
#include <stdbool.h>
typedef struct set SET;
extern SET *createDataSet(int maxStudents);
extern void destroySet(SET *sp);
extern void insertElement(SET *sp, int age, int ID);
extern void deleteElement(SET *sp, int age);
extern int maxAgeGap();
extern void searchStudent(SET *sp, int age, int ID);
extern int searchAge(SET *sp, int age, bool *found);
#endif /* SET_H */