#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#define WORDLEN 20
#define NODE struct node

//Display the linked list
void list()
{
	int count = 1;
	printf("\nLIST\n");
	NODE *p;
	//If the ehad is null, the list is empty
	if(head == (NODE *)NULL)
	{
		printf("There are no lessons scheduled\n");
		return;
	}
	//traverse through list until NULL, displaying contents of each node
	p = head;
	while(p != (NODE *)NULL)
	{
		printf("Appointment %d:\nName: %s\nSize: %d\n\n", count, p->name, p->size);
		p = p->next;
		count++;
	}
	return;
}

//Function to list names backwards
void list_back(NODE *p)
{
	//If linked list is at null, traverse backwards
	if(p == NULL)
		return;
		
	list_back(p->next);
	printf("\nName: %s\nSize: %d\n", p->name, p->size);
}

//Function to reverse names
void name_back(char *str)
{
	//If pointer is at end of string, reverse and print characters
	if(*str == '\0')
		return;
	name_back(str+1);
	printf("%c", *str);
}
