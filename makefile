# Variables
CC = gcc
CFLAGS = -Wall -g -O3 -Ilibzole -Itests

# Targets
all: zole

no-opt: CFLAGS = -Wall -g -Ilibzole -Itests
no-opt: zole

asm: CFLAGS += -S
asm: zole

zole: zole.o libzole/libzole.o tests/tests.o
	$(CC) $(CFLAGS) -o zole zole.o libzole/libzole.o tests/tests.o

zole.o: zole.c libzole/libzole.h tests/tests.h
	$(CC) $(CFLAGS) -c zole.c

libzole/libzole.o: libzole/libzole.c libzole/libzole.h
	$(CC) $(CFLAGS) -c libzole/libzole.c -o libzole/libzole.o

tests/tests.o: tests/tests.c tests/tests.h
	$(CC) $(CFLAGS) -c tests/tests.c -o tests/tests.o

run: all
	./zole

test: all
	./zole test

clean:
	rm -f *.o libzole/*.o zole *.s

.PHONY: all clean run no-opt asm

