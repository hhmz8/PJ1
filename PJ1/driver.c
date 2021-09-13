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
	static char* logname = "messages.log"; // ARG
	static int sleepTime = 1; // ARG

	// Reference: https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
	while ((option = getopt(argc, argv, "ht:")) != -1) {
		switch (option) {

		case 'h':
			printf("Usage:\n");
			printf("driver [-h] [-t sec] [logfile]\n");
			printf("-----------------------------------\n");
			printf("Default: Logs messages to messages.log.\n");
			printf("[-h]: Prints usage of this program.\n");
			printf("[-t sec]: Logs messages on an average of <sec> seconds.\n");
			printf("[logfile]: Logs messages to the specified <logfile>.\n");
			return 0;
			break;

		case 't':
			sleepTime = optarg;
			break;

		case '?':
			if (optopt == 't')
				perror("Error: Option requires an argument");
			else if (isprint(optopt))
				perror("Error: Unknown option");
			else
				perror("Error: Unknown option character");
			return -1;
			break;
		}

	}

	// TODO: Parse filename
	// TODO: Remove newline char


	// Default
	char* filename = "texts.txt";
	FILE* fileptr;
	fileptr = fopen(filename, "r");

	if (fileptr == NULL) {
		perror("Error: Failed to open message file");
		return -1;
	}

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