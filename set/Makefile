# Makefile for 'set' module
# CS50 Palmer
# Kevin Lin 
# October 6, 2021

PROG = setTest
OBJS = setTest.o set.o ../lib/file.o ../lib/mem.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

setTest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

setTest.o: set.h ../lib/file.h
set.o: set.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `test.txt` to exist
test: setTest test.txt
	./setTest < test.txt

# expects a file `test.txt` to exist
valgrind: setTest test.txt
	$(VALGRIND) ./setTest < test.txt

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f bagtest
	rm -f core
