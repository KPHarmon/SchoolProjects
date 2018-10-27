#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#define WORDLEN 20

void insert(char *, int);

//Write list to encrypted txt file
void write_file(char *filename, int key)
{
	NODE *p;
	FILE *fp;
	int i;
	char *pc, temp[WORDLEN+20];
	if((fp = fopen(filename, "w")) == NULL)
		return;

/*	header - honestly not sure if this is supposed to be encrypted or
	not, if you don't want people to see the table heading its probably
	best just to delete it.
*/	fprintf(fp, "GROUP NAME\tGROUP SIZE\n____________________________\n");

	p = head;
	//Loop through linked list
	while(p != NULL)
	{
		//put information into a long string
		sprintf(temp, "%s\t\t%d", p->name, p->size);
		pc = temp;
		//encrypt letter by letter
		while(*pc != '\0')
		{
			*pc ^= key;
			pc++;
		}
		//print out results to file
		fprintf(fp, "%s\n", temp);
		p = p->next;
	}

	//Close text file
	fclose(fp);
	return;
}

//Function to read and decrypt info from text file
void read_file(char *filename, int key)
{
	FILE *fp;
	int size;
	char name[WORDLEN], *pc, temp[WORDLEN+10];
	//If file cannot open, output an error
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("Cannot open file\n");
		return;
	}

	//Fseek to skip buffer
	fseek(fp, 51, SEEK_CUR);

	//Scan all information from text file into insert function
	while((fgets(temp, 100, fp)) != NULL)
	{
		pc = temp;
		//decrypt string letter by letter
		while(*pc != '\0')
		{
			*pc ^= key;
			pc++;
		}
		//scan then name and size from the string
		sscanf(temp, "%s\t\t%d\n", name, &size);
		//insert it into list to be manipulated
		insert(name, size);
	}

	//close file
	fclose(fp);
	return;
}
