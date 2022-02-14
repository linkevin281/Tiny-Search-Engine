# Makefile for indexer.c
# CS50 Palmer
# Kevin Lin 
# October 22, 2021

PROG1 = indexer
PROG2 = indextest
OBJS1 = indexer.o ../common/index.o ../common/word.o 
OBJS2 = indextest.o ../common/index.o ../common/word.o 
LIBS = ../libcs50/libcs50-given.a -lm

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

L = ../libcs50
C = ../common

all: indexer indextest

$(PROG1): $(OBJS1)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(PROG2): $(OBJS2)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	
.PHONY: test valgrind clean

test: 
	./testing.sh

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f core
