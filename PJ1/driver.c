#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc, char** argv) {

	int option = 0;
	int temp = 1;
	while ((option = getopt(argc, argv, ":th")) != -1) {
		switch (option) {

		case 't':
			printf("No errors detected!");
			temp = 0;
			break;

		case 'h':
			printf("Usage:\n");
			printf("driver [-h] [-t sec] [logfile]\n");
			temp = 0;
			break;

		case ':':
			break;

		case '?':
			break;
		}

	}

	if (temp == 1) {
		temp = 1;
	}

	char* filename = "texts.txt";
	FILE* fileptr;
	fileptr = fopen(filename, "r");

	if (fileptr == NULL) {
		perror("Error: Failed to open message file");
		return -1;
	}
	char* logname = "messages.log";
	char* msg = "Hello World";
	int msglen = strlen(msg);
	int sleepTime = 0;
	char *ptr = NULL;
	if ((ptr = (char*)malloc(msglen * sizeof(char))) == NULL) {
		perror("Error: Failed to allocate memory for message");
		return -1;
	}
	ptr = msg;

	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	while ((read = getline(&line, &len, fileptr)) != -1) {
		printf("Retrieved line of length %zu:\n", read);
		printf("%s", line);
	}

	int bufferLength = 255;
	char buffer[bufferLength];

	while (fgets(buffer, bufferLength, fileptr)) {
		printf("%s\n", buffer);
	}
	fscanf(fileptr, "%s", buffer);
	printf("Data from the file:\n%s", buffer);

	printf("Finished loading file.\n");

	addmsg('I', ptr);
	sleep(sleepTime);
	addmsg('I', ptr);
	sleep(sleepTime);

	savelog(logname);
	clearlog();

	fclose(fileptr);
	printf("End of program.");
	return 0;

}