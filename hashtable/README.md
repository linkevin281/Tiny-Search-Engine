# CS50 Lab 3
## CS50 Fall 2021

### hashtable

A hashtable is a set of (key,item) pairs. It acts just like a set, but is far more efficient for large collections.

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, implements a hashtable of `void*`, and exports the following functions:

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
```

### Implementation

We implement this as a list of sets.
The *hashtable* itself is represented as a `struct hashtable` containing a pointer to the head of the list; the head pointer is NULL when the hashtable is empty.

At each location in the list is initially contains an empty set. 

To insert a new item in the hashtable we create obtain an index through a hash by `hash.c` using the key. At that index in the list `set_insert` is used. 

To find an item from the hashtable we generate the correct list index through `hash.c` using the key. 

The `hashtable_print` method prints a little syntax around the list, and between items, but mostly `set_print` using `itemprint` function on each item by scanning the list.

The `hashtable_iterate` method calls `set_iterate` using `itemfunc` function on each item by scanning the list.

The `hashtable_delete` method calls `set_delete` using `itemdelete` function on each item by scanning the list, freeing setnodes as it proceeds.
It concludes by freeing the `struct set`.

### Assumptions

No assumptions beyond those that are clear from the `hashtable.h`

### Files

* `Makefile` - compilation procedure
* `hashtable.h` - the interface
* `hashtable.c` - the implementation
* `hashtableTest.c` - unit test driver
* `test.txt` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make hashtable.o`.

### Testing

The `hashtableTest.c` program reads lines from stdin and stuffs them into a set, then pulls them back out.
It tests a few error and edge cases.

To test, simply `make test`.
See `testing.out` for details of testing and an example test run.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind`.
