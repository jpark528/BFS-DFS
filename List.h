
/****************************************************************************************
 * *Juyeon Park, jpark528
* 2019 Summer CMPS101 PA3
*  List.h
*  Header file of List ADT
*****************************************************************************************/

#ifndef LIST_H_
#define LIST_H_

typedef struct ListObj* List;

List newList(void);
void freeList(List* pL);

int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);

void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);

void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);




#endif /* LIST_H_ */
