/* mains */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define WORDLEN 20
#define NODE struct node


//Node structure
struct node {
	char name[WORDLEN];
	int size;
	NODE *next;
};

//Prototype functions
void insert(char *, int);
void delete(void);
void list(void);
void size_func(void);
int check_duplicate(char *);
void read_file(char *, int);
void list_back(NODE *);
void name_back(char *);
void release_nodes(NODE *);
void *save_thread(void *);
void read_thread(char *);
void write_file (char *, int);

extern int flag;
extern pthread_mutex_t mutex;	

extern NODE *p;

//Initialize head and tail pointers
extern NODE *head;
extern NODE *tail;
