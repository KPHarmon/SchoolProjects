/* Kade Harmon
 * May 5, 2018
 * COEN 12
 * Lab 3
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <assert.h>
#include "set.h"
#define EMPTY 0
#define FILLED 1
#define DELETED 2

static int searchElements(SET *, int *);

//Initialize Structs
typedef struct student{
	int *id;
	int *age;
}STU;

struct set
{
	int count;
	int length;
	int *flags;
	STU **students;
};

//Average: O(n) Worse: O(n)
//Function to create a new set
SET *createSet(int maxElts)
{
	int i;
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->students = malloc(sizeof(STU *) * maxElts);
	assert(sp->students != NULL);
	sp->flags = malloc(sizeof(int) * maxElts);
	assert(sp->flags != NULL);
	//Initialize array flags with 0's
	for(i=0; i<maxElts; i++)
		sp->flags[i] = EMPTY;
	return sp;
}

//Average: O(n) Worse: O(n)
//Free all elements in a given set
void destroySet(SET *sp)
{
	assert(sp != NULL);
	int i;
	//Traverse through array freeing elements
	for(i=0; i<sp->length; i++)
	{
		free(sp->students[i]);
	}
	free(sp->students);
	free(sp->flags);
	free(sp);
}

//Average: O(1) Worse: O(1)
//Function to add an element to the set
void addElement(SET *sp, int *elt, int *elt2)
{
	assert(sp != NULL);
	int idx = *elt;
	//If flags is empty or deleted than allocate memory and make filled
	if(sp->flags[idx] == EMPTY || sp->flags[idx] == DELETED)
	{
		sp->students[idx] = malloc(sizeof(STU));
		sp->students[idx]->id = elt;
		sp->students[idx]->age = elt2;
		sp->flags[idx] = FILLED;
		sp->count++;
	}
}

//Average: O(1) Worse: O(1)
//Function to remove an element in the set
void removeElement(SET *sp, int *elt)
{
	assert(sp != NULL);
	int idx = *elt;	
	//If searchElements found the element in the array, delete it
	if(sp->flags[idx] == FILLED)
	{
		sp->students[idx] = NULL;
		sp->flags[idx] = DELETED;
		sp->count--;
	}
	if(sp->flags[idx] == DELETED)
		printf("Removed!\n\n");
	else
		printf("ID Not Found.\n\n");
}

//Average: O(1) Worse: O(1)
//Search for an element in the set, and return if found
void findElement(SET *sp, int *elt)
{
	assert(sp != NULL);
	int i = *elt;	
	//If searchElement finds the item, return the element
	if(sp->flags[i] == FILLED)
		printf("Found!\n\n");
	else
		printf("ID Not Found.\n\n");
}
