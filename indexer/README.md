# CS50 TSE part 2
## CS50 Fall 2021

### indexer 

the TSE indexer is a standalone program that reads the document files produced by the TSE crawler, builds an index, and writes that index to a file. Its companion, the index tester, loads an index file produced by the indexer and saves it to another file.

### Usage

$ indexer pageDirectory indexFilename

Implements the following functions

```c
void indexBuild(char* pageDirectory, char* indexFilename);
void indexPage(index_t* index, webpage_t* page, int docID);
bool isCrawler(char* pageDirectory);
```

### Implementation

The key data structure is the index, mapping from word to (docID, #occurrences) pairs. The index is a hashtable keyed by word and storing counters as items. The counters is keyed by docID and stores a count of the number of occurrences of that word in the document with that ID. 

Follows pseudocode. 

### Assumptions

No assumptions beyond those that are clear from the `indexer.h`

### Files

* `Makefile` - compilation procedure
* `indexer.h` - the interface
* `indexer.c` - the implementation
* `testing.out` - testing output
* `testing.sh` - test script
* `indextest.c` - test program
* `indextest.c` test interface
* `testDir` - test Directory containing crawler produced Dirs

### Compilation

To compile, simply `make`

### Testing

$ make test

### Unit testing

A program indextest will serve as a unit test for the index module; it reads an index file into the internal index data structure, then writes the index out to a new index file.

### Integration/system testing

The indexer, as a complete program, will be tested by building an index from a pageDirectory, and then the resulting index will be validated by running it through the indextest to ensure it can be loaded.

Script `testing.sh` is used for: the following tests
1. Unit test 
2. no argument
3. one argument
4. three or more arguments 
5. invalid pageDirectory (non-existent path)
6. invalid pageDirectory (not a crawler directory)
7. invalid indexFile (non-existent path)
8. invalid iSndexFile (read-only directory)
9. invalid indexFile (existing, read-only file)
10. Run indexer and indextest with valgrind on a variety of pageDirectories