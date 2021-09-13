#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <sys/types.h>

// Reference: https://www.geeksforgeeks.org/generating-random-number-range-c/
int getRand(int lower, int upper)
{
	return (rand() % (upper - lower + 1)) + lower;
}

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

	char* logname = "messages.log"; // ARG
	int sleepTime = 1; // ARG
	char *ptr = NULL;

	int bufferLength = 255;
	char buffer[bufferLength];

	while (fgets(buffer, bufferLength, fileptr)) {
		if ((ptr = (char*)malloc(strlen(buffer) * sizeof(buffer))) == NULL) {
			perror("Error: Failed to allocate memory for message");
			return -1;
		}
		ptr = buffer;
		addmsg('I', ptr);
		sleep(getRand(0, 2*sleepTime));
	}

	printf("Finished loading file.\n");

	savelog(logname);
	clearlog();

	fclose(fileptr);
	printf("End of program.");
	return 0;

}