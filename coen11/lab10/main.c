/*Kade Harmon
 *Angela Musurlian
 *COEN 11
 *LAB 10
*/
#include "headers.h"

pthread_mutex_t mutex;

int flag = 0;

//Initialize head and tail pointers
NODE *head = (NODE *)NULL;
NODE *tail = (NODE *)NULL;

//Main Menu
int main(int argc, char *argv[])
{
	NODE *p;
	FILE *fp;
	int inputSize;
	char filename[WORDLEN], inputName[WORDLEN];

	//Make sure user input a filename
	if(argc != 4)
	{
		printf("You did not input the correct number of arguments!\n");
		return 0;
	}
	
	read_file(argv[1], atoi(argv[3]));
	
	pthread_t thr;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thr, NULL, save_thread, (void *)argv[2]);
	
	//Menu
	while(1)
	{
		flag = 0;
		int menuInput;
		char *str;
		printf("\nMENU\n");
		printf("Type '1' to schedule a session\n");
		printf("Type '2' to remove a session\n");
		printf("Type '3' to list all sessions\n");
		printf("Type '4' to find sessions of a given size\n");
		printf("Type '5' to list all sessions backwards\n");
		printf("Type '6' to list each name backwards\n");
		printf("Type '7' to list each node from the binary file\n");
		printf("Type '0' to exit the program\n");
		scanf("%d", &menuInput);
		switch(menuInput)
		{
			case 1:
				printf("Please input your name\n");
				scanf("%s", inputName);
				printf("Please input the group size\n");
				scanf("%d", &inputSize);
				char *ptc = inputName;

				//Check Schedule to see if the name already exists
				if(check_duplicate(ptc) == 1)
				{
					printf("There is already an appointment under this name.\n");
					break;
				}
				insert(inputName, inputSize);
				break;
			case 2:
				delete();
				break;
			case 3:
				list();
				break;
			case 4:
				size_func();
				break;
			case 5:
				printf("\nREVERSE LIST\n");
				p = head;
				list_back(p);
				break;
			case 6:
				printf("\nREVERSE NAMES\n");
				p = head;
				//while loop to traverse through linked list
				while(p != NULL)
				{
					printf("\n");
					str = p->name;
					name_back(str);
					printf("\n");
					p = p->next;
				}
				break;
			case 7:
				read_thread(argv[2]);
				break;
			case 0:
				printf("Program will now exit\n");
				write_file(argv[1], atoi(argv[3]));
				p = head;
				release_nodes(p);
				pthread_cancel(thr);
				return 0;
				break;
		}
	}
	return 0;
}

//Function to insert a node to the list
void insert(char *inputName, int inputSize)
{
	NODE *p;
	char *ptc = inputName;

	//Check for malloc failure	
	if((p = (NODE *)malloc(sizeof(NODE))) == (NODE *)NULL)
	{
		printf("Malloc Error\n");
		return;
	}

	//Input values into new node	
	strcpy(p->name, inputName);
	p->size = inputSize;


	//If list is empty, make the new session the head and tail
	if(head == (NODE *)NULL)
	{
		head = p;
		tail = p;
		tail->next = (NODE *)NULL;
	}
	//If list is not empty, find the tail and add to the end
	else
	{
		tail->next = p;
		tail = p;
		tail->next = (NODE *)NULL;
	}
	return;
}

//Function to delete a session
void delete()
{
	NODE *p, *q;
	int counter = 0, inputSize, flag = 0;
	printf("Input the Amount of Space to Remove\n");
	scanf("%d", &inputSize);
	printf("\nSessions Removed:\n");

	p = q = head;
	//While loop to continue to search through list until NULL
	while(p != (NODE *)NULL)
	{
		//if list is empty, tell user and return 
		if(head == (NODE *)NULL)
		{
			printf("The schedule is empty\n");
			return;
		}
		//If the value of a nodes size added to a running total is less than or equal to the input, delete it
		if((p->size + counter) <= inputSize)
		{
			counter += p->size;
			printf("Name: %s\nSize: %d\n\n", p->name, p->size);
			
			if(p == head && p == tail)
			{
				free(p);
				head = (NODE *)NULL;
				tail = (NODE *)NULL;
				flag = 1;
				break;
			}
			else if(p == head)
			{
				head = p->next;
				free(p);
				p = head;
				q = head;
				flag = 1;
			}
			else if(p == tail)
			{
				free(tail);
				tail = q;
				flag = 1;
				break;
			}
			//reassign *next pointers around a given node to delete the node
			else
			{
				q->next = p->next;
				free(p);
				p = p->next;
			}
			flag = 1;
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	//If no size fits under the condition, tell user
	if(flag == 0)
	{
		printf("No sessions found under that size\n");
	}
	return;
}

//Function to print appointments less than or equal to a given size
void size_func()
{
	NODE *p;
	int inputSize, flag = 0;
	p = head;
	printf("Input a size to search for.\n");
	scanf("%d", &inputSize);
	printf("\nAppointments of %d or less -\n", inputSize);
	//Traverse linked list in search of node that has a size less than or equal to given size
	while(p != (NODE *)NULL)
	{
		//If node is found, print
		if(p->size <= inputSize)
		{
			flag = 1;
			printf("Name: %s\nSize: %d\n\n", p->name, p->size);
		}
		p = p->next;
	}
	if(flag == 0)
	{
		printf("No appointment found with that size\n");
	}
	return;
}

//function to check of a name already exists in the list
int check_duplicate(char *ptc)
{
	NODE *p;
	p = head;
	//String compare input to names in list, return 1 if a match is found
	while (p != (NODE*)NULL)
	{
		if(strcmp(p->name, ptc) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}

//Function to release nodes recursively
void release_nodes(NODE *p)
{
	//return function at end of linked list
	if(p == NULL)
		return;
	release_nodes(p->next);
	//free nodes
	free(p);
}

//Thread to autosave file
void *save_thread (void *filename)
{
	NODE *p;
	FILE *fp;
	pthread_mutex_init(&mutex, NULL);
	while(1)
	{
		pthread_mutex_lock(&mutex);
		fp = fopen(filename, "wb");
		p = head;
		//Print information into text file
		while(p != NULL)
		{
			fwrite(&p, sizeof(NODE), 1, fp);
			p = p->next;
		}
		fclose(fp);
		pthread_mutex_unlock(&mutex);
		sleep(15);
	}
}

//Read data from binary file
void read_thread(char *filename)
{
	NODE *temp;
	int count = 1;
	FILE *fp;
	pthread_mutex_t mutex;	
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	if((fp = fopen(filename, "rb")) == NULL)
		return;
	while(fread(&temp, sizeof(NODE), 1, fp) == 1)
	{
		printf("Appointment %d:\nName: %s\nSize: %d\n\n", count, temp->name, temp->size);
		count++;
	}
	fclose(fp);
	pthread_mutex_unlock(&mutex);
	return;
}
