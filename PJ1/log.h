/*
Hanzhe Huang
9/13/2021
log.h
*/

#include <time.h>

typedef struct data_struct {
	time_t time;
	char type;
	char* string;
} data_t;


int addmsg(const char type, const char * msg);
void clearlog(void);
char* getlog(void);
int savelog(char* filename);