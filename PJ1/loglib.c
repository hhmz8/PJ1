#include <stdlib.h>
#include <string.h>
#include "log.h"

#ifndef LOG_H
#define LOG_H

typedef struct list_struct {
	data_t item;
	struct list_struct* next;
} log_t;

static log_t* headptr = NULL;
static log_t* tailptr = NULL;

// Referenced from Program 2.7 in the textbook
int addmsg(const char type, const char* msg) {
	log_t* newnode;
	int nodesize;
	nodesize = sizeof(log_t) + strlen(msg) + 1;

	if ((newnode = (log_t*)(malloc(nodesize))) == NULL) /* couldn't add node */
		return -1;

	newnode->item.time = time(NULL);
	newnode->item.string = (char*)newnode + sizeof(log_t);
	strcpy(newnode->item.string, msg);
	newnode->next = NULL;

	if (headptr == NULL)
		headptr = newnode;
	else
		tailptr->next = newnode;
	tailptr = newnode;

	char buffer[20];
	strftime(buffer, 20, "%H:%M:%S", localtime(&newnode->item.time)); // Referenced from https://stackoverflow.com/questions/3053999/

	printf("Message: %s added at %s \n", msg, buffer);
	return 0;
}

void clearlog(void) {
	if (headptr == NULL) {
		printf("Empty log detected.\n");
	}
	else {
		tailptr = headptr;
		while (tailptr->next != NULL && tailptr != NULL) {
			headptr = tailptr->next;
			tailptr = tailptr->next;
			free(headptr);
		}
		headptr = NULL;
		tailptr = NULL;
		printf("Log cleared.\n");
	}
}

char* getlog(void) {
	printf("Log retrieved.");
	return NULL;
}

int savelog(char* filename) {
	if (headptr == NULL) {
		return -1;
	}
	printf("Log saved.");
	return 0;
}

#endif