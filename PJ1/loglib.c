#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "log.h"

#ifndef LOG_H
#define LOG_H

typedef struct list_struct {
	data_t item;
	struct list_struct* next;
} log_t;

static log_t* headptr = NULL;
static log_t* tailptr = NULL;

// Reference: Program 2.7 in the textbook by Robbins & Robbins
// Adds a message to the virtual log
int addmsg(const char type, const char* msg) {
	log_t* newnode;
	int nodesize;
	nodesize = sizeof(log_t) + strlen(msg) + 1;

	if ((newnode = (log_t*)(malloc(nodesize))) == NULL) {
		perror("Error: Failed to allocate memory for node");
		return -1;
	}
	newnode->item.time = time(NULL);
	newnode->item.string = (char*)newnode + sizeof(log_t);
	strcpy(newnode->item.string, msg);
	newnode->next = NULL;

	if (headptr == NULL)
		headptr = newnode;
	else
		tailptr->next = newnode;
	tailptr = newnode;

	char buffer[40];
	strftime(buffer, 40, "%H:%M:%S", localtime(&newnode->item.time)); // Reference: https://stackoverflow.com/questions/3053999/

	printf("Message: %s added at %s \n", msg, buffer);
	return 0;
}

// Resets the virtual log, requires a savelog() to empty the physical log file
void clearlog(void) {
	if (headptr == NULL && tailptr == NULL) {
		printf("Empty log detected.\n");
	}
	else {
		tailptr = headptr;
		while (tailptr != NULL) {
			headptr = tailptr->next;
			tailptr = tailptr->next;
			free(headptr);
		}
		free(tailptr);
		headptr = NULL;
		tailptr = NULL;
		printf("Log cleared.\n");
	}
}

char* getlog(void) {
	printf("Log retrieved.");
	return NULL;
}

// Writes the virtual log into a file
int savelog(char* filename) {
	log_t* navptr = headptr;
	FILE* fileptr;
	fileptr = fopen(filename, "w");

	if (headptr == NULL) {
		perror("Error: Failed to parse log");
		return -1;
	}
	if (fileptr == NULL) {
		perror("Error: Failed to create or open log file");
		return -1;
	}

	while (navptr != NULL) {
		char buffer[40];
		strftime(buffer, 40, "%H:%M:%S", localtime(&navptr->item.time));
		fprintf(fileptr, "%s%s%s\n", navptr->item.string, " ", buffer);
		printf("%s %s\n", navptr->item.string, buffer);
		navptr = navptr->next;
	}

	fclose(fileptr);
	printf("Log saved as %s \n", filename);
	return 0;
}

#endif