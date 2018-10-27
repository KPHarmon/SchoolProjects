/* Kade Harmon
 * May 20, 2018
 * Project 4
 */


#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

typedef struct node NODE;

//Node Structure
struct node{
	NODE *next;
	NODE *prev;
	void *data;
};

//List Structure
struct list{
	int count;
	NODE *head;
	int (*compare)();
};

//Worst Case: O(1)  Average Case: O(1)
//Function to create list
LIST *createList(int (*compare)()){
	LIST *lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(NODE));
	assert(lp->head != NULL);
	lp->head->prev = lp->head;
	lp->head->next = lp->head;
	return lp;
}

//Worst Case: O(n)  Average Case: O(n)
//Function to free all the allocated memory
void destroyList(LIST *lp){
	assert(lp != NULL);
	NODE *pDel = lp->head->next;
	do{
		free(pDel->prev);
		pDel = pDel->next;
	}while(pDel != lp->head);
	free(lp);
}

//Worst Case: O(1)  Average Case: O(1)
//Function to return the number of elements
int numItems(LIST *lp){
	assert(lp != NULL);
	return lp->count;
}

//Worst Case: O(1)  Average Case: O(1)
//Function to add a node right after head
void addFirst(LIST *lp, void *item){
	assert(lp != NULL && item != NULL);
	NODE *temp = malloc(sizeof(NODE));
	assert(temp != NULL);
	temp->data = item;
	//Reroute the pointers
	temp->next = lp->head->next;
	lp->head->next->prev = temp;
	temp->prev = lp->head;
	lp->head->next = temp;
	lp->count++;
}

//Worst Case: O(1)  Average Case: O(1)
//Function to add a node right before head
void addLast(LIST *lp, void *item){
	assert(lp != NULL && item != NULL);
	NODE *temp = malloc(sizeof(NODE));
	assert(temp != NULL);
	temp->data = item;
	//Reroute the pointers
	temp->prev = lp->head->prev;
	lp->head->prev->next = temp;
	temp->next = lp->head;
	lp->head->prev = temp;
	lp->count++;
}

//Worst Case: O(1)  Average Case: O(1)
//Function to remove the node in front of head
void *removeFirst(LIST *lp){
	assert(lp != NULL && lp->count > 0);
	//set pointer to element after what we want to delete
	NODE *dp = lp->head->next->next;
	NODE *pDel = lp->head->next;
	//store data in node to return after freeing
	void *temp = pDel->data;
	lp->head->next = dp;
	dp->prev = lp->head;
	free(pDel);
	lp->count--;
	return temp;
}

//Worst Case: O(1)  Average Case: O(1)
//Function to remove the node before head
void *removeLast(LIST *lp){
	assert(lp != NULL && lp->count > 0);
	//set pointer to the node before what we want to delete
	NODE *dp = lp->head->prev->prev;
	NODE *pDel = lp->head->prev;
	//store data in node to return after freeing
	void *temp = pDel->data;
	lp->head->prev = dp;
	dp->next = lp->head;
	lp->count--;
	free(pDel);
	return temp;
}

//Worst Case: O(1)  Average Case: O(1)
//Return the data of the node in front of head
void *getFirst(LIST *lp)
{
	assert(lp != NULL && lp->count != 0);
	return lp->head->next->data;
}

//Worst Case: O(1)  Average Case: O(1)
//Return the data in behind of head
void *getLast(LIST *lp){
	assert(lp != NULL && lp->count != 0);
	return lp->head->prev->data;
}

//Worst Case: O(n)  Average Case: O(n)
//Function to remove an item from the list
void removeItem (LIST *lp, void *item){
	assert(lp != NULL && item != NULL && lp->count != 0);
	NODE *pLoc = lp->head->next;
	//Traverse linked list until you reach the beginning again or you find the matching node
	while(pLoc != lp->head){
		if((*lp->compare)(pLoc->data, item) == 0){
			pLoc->prev->next = pLoc->next;
			pLoc->next->prev = pLoc->prev;
			lp->count--;
			free(pLoc);
			return;
		}
		pLoc = pLoc->next;
	}
	return;
}

//Worst Case: O(n)  Average Case: O(n)
//Function to find a node with given information
void *findItem(LIST *lp, void *item){
	assert(lp != NULL && item != NULL);
	NODE *pLoc = lp->head->next;
	//Traverse the linked list until we reach the beginning or we find the matching node
	while(pLoc != lp->head){
		if((*lp->compare)(pLoc->data, item) == 0)
			return (pLoc->data);
		pLoc = pLoc->next;
	}
	return NULL;	
}

//Worst Case: O(n)  Average Case: O(n)
//Function to return an array of all values in the linked list
void *getItems(LIST *lp){
	assert(lp != NULL);
	void **array = malloc(sizeof(void*)*lp->count);	
	assert(array != NULL);
	int i=0;
	NODE *pLoc = lp->head->next;
	//Copy data from linked list into an array
	while(pLoc != lp->head){
		array[i] = pLoc->data;
		i++;
		pLoc = pLoc->next;
	}
	return array;
}
