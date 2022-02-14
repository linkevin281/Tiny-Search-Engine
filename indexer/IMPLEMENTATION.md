# CS50 TSE Indexer
## Implementation Spec

In this document I reference the [Requirements Specification](REQUIREMENTS.md) and [Design Specification](DESIGN.md) and focus on the implementation-specific decisions.

-  Data structures
-  Control flow: pseudo code for overall flow, and for each of the functions
-  Testing plan

## Data structures 

The key data structure is the index, mapping from word to (docID, #occurrences) pairs. The index is a hashtable keyed by word and storing counters as items. The counters is keyed by docID and stores a count of the number of occurrences of that word in the document with that ID.

## Control flow

The indexer is implemented in one file `indexer.c`, with four functions.
Index.c and word.c are used as helper modules

### main

The `main` function parses args are exits if an error is reached before calling `indexBuild'

### indexBuild

Builds an in-memory index from webpage files it finds in the pageDirectory.

Pseudocode:

creates a new 'index' object
loops over document ID numbers, counting from 1
    loads a webpage from the document file 'pageDirectory/id'
    if successful, 
    	passes the webpage and docID to indexPage

### indexPage

Scans a webpage document to add its words to the index.

Pseudocode:

steps through each word of the webpage,
	skips trivial words (less than length 3),
	normalizes the word (converts to lower case),
	looks up the word in the index,
    	adding the word to the index if needed
	increments the count of occurrences of this word in this docID 


### libcs50

We leverage the modules of libcs50, most notably `counter`, `hashtable`, and `file`.
See that directory for module interfaces.

### index

The helper index module uses a hashtable to store an inverted index (words –> documents), and thus the hashtable is keyed by words. 

## Function prototypes

### indexer

```c
void indexBuild(char* pageDirectory, char* indexFilename);
void indexPage(index_t* index, webpage_t* page, int docID);
bool isCrawler(char* pageDirectory);
```

### index

```c 
index_t* index_new();
int index_insert(index_t* index, int docID, const char* word);
int index_get(index_t* index, int docID, const char* word);
bool index_set(index_t* index, int docID, const char* word, int count);
void index_iterate(index_t* index, void* arg, void (*itemfunc)(void* arg, const char* docID, void* item));
bool indexfile_build(index_t* index, char* indexFilename);
void wordPrint(void* arg, const char* word, void* item);
void printCounter(void* arg, const int docID, const int count);
void index_delete(index_t* index);
void ht_delete(void* item);
```

## Testing plan

Here is an implementation-specific testing plan.

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
8. invalid indexFile (read-only directory)
9. invalid indexFile (existing, read-only file)
10. Run indexer and indextest with valgrind on a variety of pageDirectories