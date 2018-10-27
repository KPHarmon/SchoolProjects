#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "set.h"

int main(){
	srand(time(NULL));
	int i, id = 0, age, max_elts = 3000;

	//Generate table and populate with data
	SET *table = createSet(max_elts);
	assert(table != NULL);
	for(i=0; i<1000; i++){
		age = (rand()%13) + 18;
		id += ((rand()%2)+1);
		addElement(table, &id, &age);
	}

	//Search for a record
	int searchId = (rand()%2000)+1;
	printf("\nSearching for ID %d ...\n", searchId);
	findElement(table, &searchId);

	//Delete a record
	searchId = (rand()%2000)+1;
	printf("Deleting ID %d ...\n", searchId);
	removeElement(table, &searchId);
	
	destroySet(table);
	return 0;
}
