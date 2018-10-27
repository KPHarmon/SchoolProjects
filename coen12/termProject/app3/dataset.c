/* Kade Harmon
 * June 8, 2018
 * Term Project
 * App 3
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <assert.h>
#include "list.h"

typedef struct node NODE;

//Node Structure
struct node{
	NODE *next;
	NODE *prev;
	int age;
	int id;
};

//List Structure
struct list{
	int count;
	int max;	
	int min;
	NODE *head;
};

//Worst Case: O(1)  Average Case: O(1)
//Function to create list
LIST *createList(){
	LIST *lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->max = 0;
	lp->min = 2000;
	lp->count = 0;
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
//Function to add a node right before head
void addFirst(LIST *lp, int eltId, int eltAge){
	assert(lp != NULL);
	NODE *temp = malloc(sizeof(NODE));
	assert(temp != NULL);
	//Update Max and Min
	if(lp->max < eltAge)
		lp->max = eltAge;
	if(lp->min > eltAge)
		lp->min = eltAge;
	//Set variables
	temp->id = eltId;
	temp->age = eltAge;
	//Reroute the pointers
	temp->next = lp->head->next;
	lp->head->next->prev = temp;
	temp->prev = lp->head;
	lp->head->next = temp;
	lp->count++;
}

//Function to return the age gap
int maxAgeGap(LIST *lp){
	assert(lp != NULL);
	return lp->max - lp->min;
}

//Worst Case: O(n)  Average Case: O(n)
//Function to remove an item from the list
void removeItem (LIST *lp, int eltId){
	assert(lp != NULL && lp->count != 0);
	NODE *pLoc = lp->head;
	//Traverse linked list until you reach the beginning again or you find the matching node
	while(pLoc->next != lp->head){
		pLoc = pLoc->next;
		if(pLoc->id == eltId){
			pLoc->prev->next = pLoc->next;
			pLoc->next->prev = pLoc->prev;
			lp->count--;
			free(pLoc);
			printf("Removed!\n");
			return;
		}
	}
	printf("ID Not Found.\n");
}

//Worst Case: O(n)  Average Case: O(n)
//Function to find a node with given information
void findItem(LIST *lp, int eltId){
	int flag = 0;
	assert(lp != NULL);	
	NODE *pLoc = lp->head->next;
	//Traverse the linked list until we reach the beginning or we find the matching node
	while(pLoc != lp->head){
		if(pLoc->id == eltId){
			printf("Found!\n");
			return;
		}
		pLoc = pLoc->next;
	}
	printf("ID Not Found\n");
}

//Worst Case: O(n)  Average Case: O(n)
//Function to print out all ids of certain age
void getItems(LIST *lp, int eltAge){
	int flag = 0; // aesthetics for reading ids
	assert(lp != NULL);
	NODE *pLoc = lp->head->prev;
	while(pLoc != lp->head){
		if(pLoc->age == eltAge){
			if(flag == 1){
				printf("ID: %d\n", pLoc->id);
				flag = 0;
			}else{
				if(pLoc->id < 1000)
					printf("ID: %d   \t", pLoc->id);
				else
					printf("ID: %d\t", pLoc->id);
				flag = 1;
			}
		}
		pLoc = pLoc->prev;
	}
}
