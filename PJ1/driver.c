#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
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

	int strlen = 11;
	int sleepTime = 0;
	char *ptr = NULL;
	if ((ptr = (char*)malloc(strlen * sizeof(char))) == NULL) {
		return -1;
	}
	ptr = "Hello World";
	addmsg('I', ptr);
	sleep(sleepTime);
	addmsg('I', ptr);
	sleep(sleepTime);
	addmsg('I', ptr);
	sleep(sleepTime);
	addmsg('I', ptr);
	clearlog();

	printf("End of program.");
	return 0;

}