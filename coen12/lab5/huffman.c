/* Kade Harmon
 * June 3, 2018 
 * Project 5 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "pack.h"
#include "pqueue.h"

typedef struct node NODE;

//Big O - Worst Case: O(1) Average Case: O(1)
//Function to make nodes on Huffman Tree
NODE *mknode(int data, NODE *left, NODE *right){
	NODE *np = malloc(sizeof(NODE));
	assert(np != NULL);
	np->count = data;
	np->parent = NULL;
	if(left != NULL)
		left->parent = np;
	if(right != NULL)
		right->parent = np;
	return np;
}

//Big O - Worst Case: O(logn) Average Case: O(logn)
//Function to return the depth of a node
int depth(NODE *pq){
	assert(pq != NULL);
	int count = 0;
	while(pq->parent != NULL){
		count++;
		pq = pq->parent;
	}
	return count;
}

//Big O - Worst Case: O(1) Average Case: O(1)
//Function to compare nodes
int nodeCompare(NODE *pq1, NODE *pq2){
    return ((pq1->count < pq2->count) ? -1 : (pq1->count > pq2->count));
}

//Big O - Worst Case: O(nlogn) Average Case: O(nlogn)
//Main Function
int main(int argc, char *argv[]){
	NODE *nodes[257];
	int counts[257], i = 0, c;
	FILE *fp;

	//Check arguments
	if(argc != 3){
		printf("Make sure to include the ouput and input files\n");
		return 0;
	}
	if ((fp = fopen(argv[1], "rb")) == NULL) {
        printf("File cannot be opened\n");
		return 0;
    }

	//Count number of each character in file
	for(i=0; i<257; i++){
		counts[i] = 0;
		nodes[i] = NULL;
	}

	//Read file
	while((c = getc(fp)) != EOF){
		counts[c]++;
	}

	//Close the file
	fclose(fp);

	//Create Queue	
	PQ *pq = createQueue(nodeCompare);

	//Make all leafs and add them to queue
	for(i = 0; i<256; i++){                
		if(counts[i] > 0){
			nodes[i] = mknode(counts[i], NULL, NULL);
			addEntry(pq, nodes[i]);
		}
	}

	//Initialize EOF
	nodes[256] = mknode(0, NULL, NULL);
	addEntry(pq, nodes[256]);

	//Create tree by removing two entries, combine values, then adding them back
	while(numEntries(pq) != 1){
		NODE *l = removeEntry(pq);
		NODE *r = removeEntry(pq);
		NODE *n = mknode(l->count+r->count, l, r);
		addEntry(pq, n);
	}

	//Print out bits
	for(i = 0; i<257; i++){
		if(counts[i] != 0){
			printf(isprint(i) ? "'%c'":"%03o", i);
			printf(" : %d x %d bits = %d bits\n", counts[i], depth(nodes[i]), counts[i] * depth(nodes[i]));
		}
	}
	
	pack(argv[1], argv[2], nodes);
	return 0;
}
