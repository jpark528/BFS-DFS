/*********************************************************************************
*Juyeon Park, jpark528
* 2019 Summer CMPS101 PA2
* List.c
* List ADT file
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Private struct NodeObj
typedef struct NodeObj{
	void* data;
	struct NodeObj* prev;
	struct NodeObj* next;
}NodeObj;

// Private Node
typedef NodeObj* Node;

// Private struct ListObj
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int index;
	int length;
}ListObj;

// Constructors-Destructors ---------------------------------------------------

// Private constructors that return to the Node and initialize the data,prev,and next.
Node newNode(void* data){
	Node N = NULL;
	N = malloc(sizeof(NodeObj));
	N->data = data;
	N->prev = NULL;
	N->next = NULL;
	return N;
}

void freeNode(Node* pN){
   if(pN!=NULL && *pN!=NULL){
      free(*pN);
      *pN = NULL;
   }
}
// Creates and returns a new empty List.
List newList(void){
	List L = NULL;
	L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return L;
}



// Frees all heap memory associated with *pL, and sets
      	  	  	  	  	 // *pL to NULL.
void freeList(List* pL){
	if(*pL !=NULL && pL !=NULL){
		while (length(*pL)>0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L){

	if (L == NULL){
		printf("List error: calling length() on NULL Stack reference\n");
		exit(1);
	}

		return L->length;
}
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){


	if(L==NULL){
		printf("List error: calling index() on NULL Stack reference\n");
		exit(1);
	}

	if (length(L)<=0){
		return -1;
	}

		return L->index;

}
// Returns front element of L. Pre: length()>0
void* front(List L){
	if(L==NULL){
		printf("List error: calling front() on NULL stack reference");
		exit(1);
	}
	if(length(L)<=0){
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}

	return L->front->data;

}
// Returns back element of L. Pre: length()>0
void* back(List L)
{
	if(L==NULL)
	{
		printf("List error: calling back() on NULL stack reference");
		exit(1);
	}

	if(!(length(L)>0)){
		printf("List Error: calling back() on an empty List\n");
		exit(1);
	}

	return L->back->data;

}
// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L){

	if (L==NULL){
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
	}
    if (length(L)<=0)
    {
        printf("List Error: calling get() on an empty List\n");
        exit(1);
    }
    if(index(L)<0){
    	printf("List Error: calling get() on an empty list\n");
    	exit(1);
    }

    	return L->cursor->data;
}

// Returns true (1) iff Lists A and B are in same
/*int equals(List A, List B){
	int eq = 0;
	   Node N = NULL;
	   Node M = NULL;

	   if(A==NULL || B==NULL){
	      printf("Queue Error: calling equals() on NULL List reference\n");
	      exit(1);
	   }

	   eq = (A->length == B->length);
	   N = A->front;
	   M = B->front;
	   while(eq && N!=NULL)
	   {
	      eq = (N->data==M->data);
	      N = N->next;
	      M = M->next;
	   }
	   return eq;
}*/

// Resets L to its original empty state.
void clear(List L){

	if(L==NULL){
		printf("List Error: calling clear() on NULL List references\n");
		exit(1);
	}
	else if(L!=NULL)
	{
		L->front = NULL;
		L->back = NULL;
		L->cursor = NULL;
		L->length = 0;
		L->index = -1;
	}

}
// If L is non-empty, sets cursor under the front element, // otherwise does nothing.
void moveFront(List L){

	if(L==NULL){
		printf("List Error: calling moveFront() on NULL List references\n");
		exit(1);
	}

	if(length(L) > 0){
		L->cursor = L->front;
		L->index = 0;
	}


}
// If L is non-empty, sets cursor under the back element, // otherwise does nothing.
void moveBack(List L){

	if(L==NULL){
		printf("L is empty");
		exit(1);
	}

	if(length(L) >0){
		L->cursor = L->back;
		L->index = L->length-1;
	}


}
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){

	if(L->cursor!=NULL){

		if(L->cursor != L->front){
			L->cursor = L->cursor->prev;
			L->index--;
		}
		else if (L->cursor == L->front){
			L->cursor = NULL;
			L->index = -1;
		}
	}

	else if (L->cursor == NULL){
		printf("The cursor is undefined");
		exit(1);
	}
	if(L==NULL){
		exit(1);
	}

}
// If cursor is defined and not at back, move cursor one // step toward the back of L;
//if cursor is defined and at // back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){

	if(L!= NULL){

		if(L->cursor != L->back){
			L->cursor = L->cursor->next;
			L->index++;
		}
		else if (L->cursor == L->back){
			L->cursor = NULL;
			L->index = -1;
		}
	}
	else if(L==NULL)
	{
		exit(1);
	}
}

// Insert new element into L. If L is non-empty, // insertion takes place before front element.
void prepend(List L, void* data){

	Node temp = newNode(data);

	if(L==NULL){
		exit(1);
	}

	else if(L!=NULL){
		if(L->front==NULL){
			L->front = L->back = temp;
			//L->cursor = L->front;
		}

		else if(L->front!=NULL){
			L->front->prev = temp;
			temp->next = L->front;
			L->front = temp;
			L->index++;
		}

		L->length++;
	}
}
// Insert new element into L. If L is non-empty, // insertion takes place after back element.
void append(List L, void* data){
	Node temp = newNode(data);
	if(L==NULL){
		exit(1);
	}

	else if(L!=NULL){
		if(L->front == NULL){
			L->front = temp;
			L->back = temp;
			//L->cursor = L->back;
		}

		else{
			L->back->next = temp;
			temp->prev = L->back;
			L->back = temp;
			temp->next = NULL;
		}
		L->length++;
	}
}
// Insert new element before cursor. // Pre: length()>0, index()>=0
void insertBefore(List L, void* data){
	Node temp = newNode(data);
	if(L==NULL){
		exit(1);
	}
	if(L->cursor == NULL){
		printf("List Error: can't insertBefore() because cursor is not defined.");
	}

	if(length(L)<=0){
		printf("List error: cannot call insertBefore() on an empty list\n");
		exit(1);
	}

	else{
		if(L->cursor == L->front){
			prepend(L,data);
		}
		else{
			temp->prev = L->cursor->prev;
			temp->next = L->cursor;
			L->cursor->prev = temp;
			L->length++;
			L->index++;
		}

	}


}
// Insert new element before cursor. // Pre: length()>0, index()>=0
void insertAfter(List L, void* data){
	Node temp = newNode(data);
	if(L->cursor == NULL){
		printf("List Error: can't insertAfter() because cursor is not defined.");
	}
	if(L==NULL){
		exit(1);
	}
	else if(L!=NULL){
		if(length(L)<=0){
			printf("List error: cannot call insertAfter() on an empty list\n");
			exit(1);
		}
		if(index(L)<0){
			printf("List error: cannot call insertAfter() on an empty list\n");
			exit(1);
		}

		else{
			if(L->cursor == L->back){
				append(L,data);
			}
			else{
				L->cursor->next = temp;
				temp->prev = L->cursor;
				temp->next = L->cursor->next;
				L->length++;
			}

		}
	}

}
// Delete the front element. Pre: length()>0
void deleteFront(List L){
	   Node temp = L->front;

	   if(L==NULL){
	      printf("List Error: calling deleteFront() on NULL List reference\n");
	      exit(1);
	   }

	   if(length(L)<=0){
	      printf("List Error: calling deleteFront() on an empty List\n");

	   }

	   else if(length(L)>0){
		   if(L->length>1){
			   L->front = L->front->next;
		   }
		   else{
			   L->front = NULL;
			   L->back = NULL;
			   L->cursor = NULL;
			   L->index = -1;
		   }
	   }
	   if(L->cursor !=NULL){
		   L->index--;
	   }
	   L->length--;
	   freeNode(temp);
}
// Delete the back element. Pre: length()>0
void deleteBack(List L){
	Node temp = L->back;

   if(L==NULL){
	  printf("List Error: calling deleteBack() on NULL List reference\n");
	  exit(1);
   }
	if(length(L)<=0){
		printf("List Error: calling deleteBack() on an empty List\n");
		exit(1);
	}

	else if(length(L)>0){
		if(L->length>1){
			L->back = L->back->prev;
		}
		else{
			L->back->next = NULL;
			L->front = NULL;
			L->cursor = NULL;
			L->index = -1;
		}
	}
	if(L->index == L->length -1){
		L->index = -1;
	}
	freeNode(temp);
	L->length--;

}

// Delete cursor element, making cursor undefined. // Pre: length()>0, index()>=0
void delete(List L){

	if(L!=NULL){
		if(index(L)<0){
			exit(1);
		}
		if(L->cursor == NULL){
			exit(1);
		}
		else{
			if (L->cursor != L->front){
				L->cursor->prev->next = L->cursor->next;
			}
			else if(L->cursor == L->front){
				deleteFront(L);
			}

			else if (L->cursor != L->back){
				L->cursor->next->prev = L->cursor->prev;
			}
			else if(L->cursor == L->back){
				deleteBack(L);
			}
			else{
				Node temp = L->cursor;
				freeNode(&temp);
				L->length--;
				L->cursor = NULL;
			}
			L->index = -1;

		}

	}


	else if(L==NULL){
		exit(1);
	}
}

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
/*
void printList(FILE* out, List L){
	Node temp = L->front;
	if(L!=NULL){
		for(temp = L->front; temp!=NULL; temp = temp->next){
			fprintf(out, "%d", temp->data);
		}
	}
	else if(L==NULL){
		exit(1);
	}
}
*/
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state // of L is unchanged.
/*
List copyList(List L){
	List copy = newList();

	if(length(L)>0){
		Node temp = L->front;
		while(temp!=NULL){
			append(copy,temp->data);
			temp = temp->next;
		}
	}
	copy->cursor = NULL;
	copy->index = -1;
	return copy;
}
*/
