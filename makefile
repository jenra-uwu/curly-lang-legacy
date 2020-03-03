##
## Curly
## makefile
##
## jenra
## March 3 2020
##

CC = gcc
CFLAGS = -Wall -O0 -ggdb3
LDFLAGS = 
LIBS = 

CODE = src/

all: *.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o curly $? $(LIBS)

*.o: main

main: $(CODE)main.c
	$(CC) $(CFLAGS) -c $?

clean:
	-rm *.o
