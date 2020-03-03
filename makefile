##
## Curly
## makefile
##
## jenra
## March 3 2020
##

CC = gcc
CFLAGS = -Wall -O0 -ggdb3 -I'curly-comb/src/parse'
LDFLAGS = 
LIBS = -Lcurly-comb -lcomb

CODE = src/

all: *.o libcomb.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o curly *.o $(LIBS)

*.o: main

libcomb.a:
	cd curly-comb && make -f makefile && cd ..

main: $(CODE)main.c
	$(CC) $(CFLAGS) -c $?

clean:
	-rm *.o
