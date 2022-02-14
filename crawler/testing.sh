#!/bin/bash

rm -f testing.out

# tests erronous arguments

# invalid internal URL
./crawler https://github.com/CS50Dartmouth21FS1/home/blob/fall21s1/labs/tse/crawler/IMPLEMENTATION.md ../data/letters 2 >> testing.out
# Invalid max depth
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 11 >> testing.out
# Invalid negative depth
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters -5 >> testing.out
# Invalid URL
./crawler http://cs50tse.cuth.edu/tters/index.html ../data/letters 2 >> testing.out
# Invalid depth
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters asef >> testing.out

# valgrind runs
rm -f tests/*
for DEPTH in 0 1
do
	./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../crawler/proper/letters-$DEPTH $DEPTH >> testing.out
done
# all CS50 website runs

# letters
rm -f test/*
for DEPTH in 0 10
do
	./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../crawler/test $DEPTH >> testing.out
	diff -s -q ../crawler/test ../crawler/proper/letters-$DEPTH
done
if [ $? -eq 0 ]
then
  echo "Letters test success"
fi

# toscrape
rm -f test/*
for DEPTH in 0 1
do
	./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../crawler/test $DEPTH >> testing.out
	diff -s -q ../crawler/test ../crawler/proper/toscrape-$DEPTH
done
if [ $? -eq 0 ]
then
  echo "Toscrape test success"
fi

# wikipedia
rm -f test/*
for DEPTH in 0 1
do
	./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html ../crawler/test $DEPTH >> testing.out
	diff -s -q ../crawler/test ../crawler/proper/wikipedia-$DEPTH
done
if [ $? -eq 0 ]
then
  echo "Wiki test success"
fi
