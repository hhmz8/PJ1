CC = gcc
CFLAGS = -Wall
DEPS = log.h loglib.c driver.c
OBJ = loglib.o driver.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	
driver: $(OBJ)
	gcc $(CFLAGS) -o $@ $^