# Makefile for crawler.c
# CS50 Palmer
# Kevin Lin 
# October 15, 2021

PROG = crawler
OBJS = crawler.o ../common/pagedir.o
LIBS = ../libcs50/libcs50-given.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

L = ../libcs50
C = ../common

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o: $L/webpage.h $L/file.h

.PHONY: test valgrind clean

# # expects a file `test.txt` to exist
# test: hashtableTest test.txt
# 	./hashtableTest < test.txt

# expects a file `test.txt` to exist
valgrind: crawler
	$(VALGRIND) ./crawler

test:
	./testing.sh

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f bagtest
	rm -f core
