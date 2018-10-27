/* Kade Harmon
 * May 20, 2018
 * Project 4
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <assert.h>
#include "set.h"
#include "list.h"
#define AVG_CHAIN_LENGTH 20 

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

//Set Structure
struct set{
	int count;
	int length;
	struct list **lists;
	int (*compare)();
	unsigned (*hash)();
};

//Worst Case: O(n)   Average Case: O(n)
//Function to create the set
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	int i;
	//Allocate Set and List
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	//Malloc space for array
	sp->length = maxElts/AVG_CHAIN_LENGTH;
	sp->lists = malloc(sizeof(LIST)*sp->length);
	assert(sp->lists != NULL);	
	sp->count = 0;
	sp->compare = compare;
	sp->hash = hash;
	//Initialize the array or linked lists
	for(i = 0; i < sp->length; i++)
		sp->lists[i] = createList(compare);
	return sp;
}

//Worst Case: O(n)   Average Case: O(n)
//Function to free all the allocated memory
void destroySet(SET *sp){
	assert(sp != NULL);
	int i;
	for(i = 0; i < sp->length; i++)
		destroyList(sp->lists[i]);
	free(sp->lists);
	free(sp);
}

//Worst Case: O(1)   Average Case: O(1)
//Function to return the number of elements
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}

//Worst Case: O(1)   Average Case: O(1)
//Function to add an element to a given array
void addElement(SET *sp, void *item){
	assert(sp!= NULL && item != NULL);
	int idx = ((*sp->hash)(item))%sp->length;
	if(!findItem(sp->lists[idx], item)){   //<------
		addFirst(sp->lists[idx], item);
		sp->count++;
	}
}

//Worst Case: O(n)   Average Case: O(n)
//Function to remove an element to a given array
void removeElement(SET *sp, void *item){
	assert(sp!= NULL && item != NULL);
	int idx = ((*sp->hash)(item))%sp->length;
	removeItem(sp->lists[idx], item);
	sp->count--;
}

//Worst Case: O(n)   Average Case: O(n)
void *findElement(SET *sp, void *item){
	assert(sp != NULL && item != NULL);
	int idx = ((*sp->hash)(item)%sp->length);
	return (findItem(sp->lists[idx], item));
}

//Worst Case: O(n)   Best Case: O(n)
//Function to create an array of all of the elements
void *getElements(SET *sp){
	assert(sp != NULL);
	int i, j = 0;
	//Create an array to put elements in
	void **tempArray = malloc(sizeof(void *)*sp->count);
	assert(tempArray != NULL);
	//Memcpy elements from linked lists into an array
	for(i=0; i<sp->length; i++)
	{
		memcpy(tempArray+j, getItems(sp->lists[i]), numItems(sp->lists[i])*sizeof(void*));
		j+=numItems(sp->lists[i]);
	}
	return tempArray;
}
