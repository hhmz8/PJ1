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

// Returns one of the four types based on the char
char* getTypeString(const char type) {
	switch (type) {
	case 'I':
		return "INFO";
		break;
	case 'W':
		return "WARN";
		break;
	case 'E':
		return "ERROR";
		break;
	case 'F':
		return "FATAL";
		break;
	case '?':
		perror("Error: Unrecognized message type");
		addmsg('F', "Unrecognized message type");
		exit(-1);
		break;
	}
	return NULL;
}

// Reference: Program 2.7 in the textbook by Robbins & Robbins
// Adds a message to the virtual log
int addmsg(const char type, const char* msg) {
	log_t* newnode;
	int nodesize;
	nodesize = sizeof(log_t) + strlen(msg) + 1;

	if ((newnode = (log_t*)(malloc(nodesize))) == NULL) {
		perror("Error: Failed to allocate memory for node");
		addmsg('F', "Failed to allocate memory for node");
		return -1;
	}

	newnode->item.time = time(NULL);
	newnode->item.type = type;
	newnode->item.string = (char*)newnode + sizeof(log_t);
	strcpy(newnode->item.string, msg);
	newnode->next = NULL;

	if (headptr == NULL)
		headptr = newnode;
	else
		tailptr->next = newnode;
	tailptr = newnode;

	return 0;
}

// Resets the virtual log
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

// Returns a pointer to a string containing the log
char* getlog(void) {
	char* logstr;
	int loglen;

	if (headptr == NULL) {
		perror("Error: Failed to parse log or log is empty");
		addmsg('F', "Failed to parse log or log is empty");
		exit(-1);
	}

	log_t* navptr = headptr;
	while (navptr != NULL) {
		char buffer[40];
		strftime(buffer, 40, "%H:%M:%S", localtime(&navptr->item.time)); // Reference: https://stackoverflow.com/questions/3053999/
		loglen += (strlen(buffer) + strlen(getTypeString(navptr->item.type)) + strlen(navptr->item.string) + strlen("[] [] ") + 1);
		navptr = navptr->next;
	}
	if ((logstr = (char*)malloc(loglen)) == NULL) {
		perror("Error: Failed to allocate memory for string");
		addmsg('F', "Failed to allocate memory for string");
		exit(-1);
	}
	else {
		navptr = headptr;
		char temp[255];
		char buffer[40];
		strcpy(logstr, "");
		while (navptr != NULL) 
		{
			strftime(buffer, 40, "%H:%M:%S", localtime(&navptr->item.time));
			sprintf(temp, "[%s] [%s] %s", buffer, getTypeString(navptr->item.type), navptr->item.string);
			strcat(logstr, temp);
			navptr = navptr->next;
		}
	}
	
	return logstr;
}

// Writes the virtual log into a file
int savelog(char* filename) {
	log_t* navptr = headptr;
	FILE* fileptr;
	fileptr = fopen(filename, "w");

	if (headptr == NULL) {
		perror("Error: Failed to parse log or log is empty");
		addmsg('F', "Failed to parse log or log is empty");
		exit(-1);
	}
	if (fileptr == NULL) {
		perror("Error: Failed to create or open log file");
		addmsg('F', "Failed to create or open log file");
		exit(-1);
	}
	
	while (navptr != NULL) {
		char buffer[40];
		strftime(buffer, 40, "%H:%M:%S", localtime(&navptr->item.time));
		fprintf(fileptr, "[%s] [%s] %s", buffer, getTypeString(navptr->item.type), navptr->item.string);
		navptr = navptr->next;
	}

	fclose(fileptr);
	printf("\n");
	printf("Log saved as %s \n", filename);
	return 0;
}

#endif