#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "list.h"

int main(){
	srand(time(NULL));
	int i, id = 0, age;

	//Generate table and populate with data
	LIST *list = createList();
	assert(list != NULL);
	for(i=0; i<1000; i++){
		age = (rand()%13) + 18;
		id += ((rand()%2)+1);
		addFirst(list, id, age);
	}

	//Search for random Id
	int searchId = (rand()%2000)+1;
	printf("\nSearching for ID %d ...\n", searchId);
	findItem(list, searchId);

	//Delete a record
	searchId = (rand()%2000)+1;
	printf("\nDeleting ID %d ...\n", searchId);
	removeItem(list, searchId);
	
	//Max Age Gap
	printf("\nMax Age Gap: %d\n", maxAgeGap(list));
 
	//Search for random Age
	int randAge = (rand()%13)+18;
	printf("\nAll Students of Age %d:\n", randAge);
	getItems(list, randAge);

	destroyList(list);
	return 0;
}
