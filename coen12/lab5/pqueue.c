/* Kade Harmon
 * June 3, 2018 
 * Project 5 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"
#define p(x) ((x-1)/2)
#define l(x) ((x*2)+1)
#define r(x) ((x*2)+2)

//Pqueue struct
struct pqueue{
	void **data;
	int length;
	int count;
	int (*compare)();
};

//Big O - Worst Case: O(1) Average Case: O(1)
//Function to create set
PQ *createQueue(int(*compare)()){
	PQ *pq = malloc(sizeof(PQ));
	assert(pq != NULL);
	pq->data = malloc(sizeof(void *)*10);
	assert(pq->data != NULL);
	pq->length = 10;
	pq->count = 0;
	pq->compare = compare;
	return pq;
}

//Big O - Worst Case: O(1) Average Case: O(1)
//Function to destroy set
void destroyQueue(PQ *pq){
	assert(pq != NULL);
	free(pq->data);
	free(pq);
}

//Big O - Worst Case: O(1) Average Case: O(1)
//Function to return number of entries
int numEntries(PQ *pq){
	assert(pq != NULL);
	return pq->count;
}

//Big O - Worst Case: O(1) Average Case: O(1)
//Function to swap values
void swap(PQ *pq, int index1, int index2){
	void *temp = pq->data[index1];
	pq->data[index1] = pq->data[index2];
	pq->data[index2] = temp;	
}

//Big O - Worst Case: O(logn) Average Case: O(logn)
//Function to add a value to the pqueue
void addEntry(PQ *pq, void *entry){
	assert(pq != NULL);
	//double the size of the array if full
	if(pq->count == pq->length){
		pq->length*=2;
		pq->data = realloc(pq->data, sizeof(void*)*(pq->length));
	}
	pq->data[pq->count] = entry;
	int i = pq->count;
	//swap if parent is larger than the child
	while((*pq->compare)(pq->data[p(i)], pq->data[i]) > 0){
		swap(pq, p(i), i);
		i = p(i);
	}
	pq->count++;
}

//Big O - Worst Case: O(logn) Average Case: O(logn)
//Function to remove a calue from the pqueue
void *removeEntry(PQ *pq){
	assert(pq != NULL && pq->count > 0);
	int i = 0;
	void *rmvd = pq->data[0];
	pq->data[0] = pq->data[(pq->count)-1];
	pq->count--;
	//while you have a children run this loop
	while(l(i) < pq->count || r(i) < pq->count){
		//swap left if smaller or equal to the right child
		if((*pq->compare)(pq->data[l(i)], pq->data[r(i)]) <= 0 ){
			if(l(i) <= pq->count){
				swap(pq, i, l(i));
				i = l(i);
			}else
				break;
		}
		//swap right if its smaller
		else if((*pq->compare)(pq->data[l(i)], pq->data[r(i)]) > 0){
			if(r(i) <= pq->count){
				swap(pq, i, r(i));
				i = r(i);
			}else
				break;
		}
	}
	return rmvd;
}
