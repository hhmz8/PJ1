#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <sys/types.h>

// Reference: https://www.geeksforgeeks.org/generating-random-number-range-c/
int getRand(const int lower, const int upper)
{
	return (rand() % (upper - lower + 1)) + lower;
}

int main(int argc, char** argv) {

	int option = 0;                         // getopt
	const char* filename = "texts.txt";     // input messages
	static char* logname = "messages.log";  // argv
	static int sleepTime = 1;               // argv

	// Reference: https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
	while ((option = getopt(argc, argv, "ht:")) != -1) {
		switch (option) {

		case 'h':
			printf("-----------------------------------\n");
			printf("Usage:\n");
			printf("%s [-h] [-t sec] [logfile]\n", argv[0]);
			printf("-----------------------------------\n");
			printf("Default: Logs messages to a new or existing messages.log file.\n");
			printf("[-h]: Prints usage of this program.\n");
			printf("[-t sec]: Logs messages on an average of <sec> seconds.\n");
			printf("[logfile]: Logs messages to the specified <logfile>.\n");
			printf("-----------------------------------\n");
			return 0;
			break;

		case 't':
			sleepTime = atoi(optarg);
			if (sleepTime == NULL || sleepTime > 10 || sleepTime < 0) {
				perror("Invalid or large sleep duration");
				return -1;
			}
			break;

		case '?':
			if (optopt == 't')
				perror("Option requires an argument");
			else if (isprint(optopt))
				perror("Unknown option");
			else
				perror("Unknown option character");
			return -1;
			break;
		}

	}

	if (optind < argc) {
		logname = argv[optind];
	}

	// TODO: Parse filename
	// TODO: Remove newline char


	// Default
	FILE* fileptr;
	fileptr = fopen(filename, "r");

	if (fileptr == NULL) {
		perror("Failed to open message file");
		return -1;
	}

	char *ptr = NULL;
	int bufferLength = 255;
	char buffer[bufferLength];

	while (fgets(buffer, bufferLength, fileptr)) {
		if ((ptr = (char*)malloc(strlen(buffer) * sizeof(buffer))) == NULL) {
			perror("Failed to allocate memory for message");
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
	printf("End of program.\n");
	return 0;

}