# Makefile for 'hashtable' module
# CS50 Palmer
# Kevin Lin 
# October 6, 2021

PROG = hashtableTest
OBJS = hashtableTest.o hashtable.o set.o hash.o ../lib/file.o ../lib/mem.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

hashtableTest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtableTest.o: hashtable.h ../lib/file.h
hashtable.o: hashtable.h 
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `test.txt` to exist
test: hashtableTest test.txt
	./hashtableTest < test.txt

# expects a file `test.txt` to exist
valgrind: hashtableTest test.txt
	$(VALGRIND) ./hashtableTest < test.txt

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f bagtest
	rm -f core
