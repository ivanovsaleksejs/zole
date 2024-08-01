# Variables
CC = gcc
CFLAGS = -Wall -g -O3
CFLAGS_NODEBUG = -Wall -O3
LIBFLAGS = -Ilibzole -Itests 
LDFLAGS = -lfcgi -lwebsockets -lpthread -lhiredis -lcjson

# Targets
all: zole

no-opt: CFLAGS = -Wall -g -Ilibzole -Itests
no-opt: zole

asm: zole.asm libzole/libzole.asm

zole: zole.o libzole/libzole.o tests/tests.o network/ajax.o network/websockets.o
	$(CC) $(CFLAGS) $(LIBFLAGS) -o zole zole.o libzole/libzole.o tests/tests.o network/ajax.o network/websockets.o $(LDFLAGS)

zole.o: zole.c libzole/libzole.h tests/tests.h
	$(CC) $(CFLAGS) $(LIBFLAGS) -c zole.c

libzole/libzole.o: libzole/libzole.c libzole/libzole.h
	$(CC) $(CFLAGS) $(LIBFLAGS) -c libzole/libzole.c -o libzole/libzole.o

tests/tests.o: tests/tests.c tests/tests.h
	$(CC) $(CFLAGS) $(LIBFLAGS) -c tests/tests.c -o tests/tests.o

network/ajax.o:
	$(CC) $(CFLAGS) $(LIBFLAGS) -c network/ajax.c -o network/ajax.o

network/websockets.o:
	$(CC) $(CFLAGS) $(LIBFLAGS) -c network/websockets.c -o network/websockets.o

zole.asm: zole.c libzole/libzole.h tests/tests.h
	$(CC) $(CFLAGS_NODEBUG) $(LIBFLAGS) -S zole.c -o zole.asm

libzole/libzole.asm: libzole/libzole.c libzole/libzole.h
	$(CC) $(CFLAGS_NODEBUG) $(LIBFLAGS) -S libzole/libzole.c -o libzole/libzole.asm

run: all
	./zole

test: all
	./zole test

spawn: all
	spawn-fcgi -p 9000 ./zole

clean:
	rm -f *.o *.asm libzole/*.o libzole/*.asm network/*.o zole *.s

.PHONY: all clean run no-opt asm

