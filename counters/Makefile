# Makefile for 'counters' module
# CS50 Palmer
# Kevin Lin 
# October 6, 2021

PROG = counterTest
OBJS = counterTest.o counters.o ../lib/file.o ../lib/mem.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

counterTest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

counterTest.o: counters.h ../lib/file.h
counters.o: counters.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `test.txt` to exist
test: counterTest test.txt
	./counterTest < test.txt

# expects a file `test.txt` to exist
valgrind: counterTest test.txt
	$(VALGRIND) ./counterTest < test.txt

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f bagtest
	rm -f core
