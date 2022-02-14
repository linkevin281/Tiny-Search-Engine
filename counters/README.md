# CS50 Lab 3
## CS50 Fall 2021

### counters

A counter set is a set of counters, each distinguished by an integer key. It's a set - each key can only occur once in the set - and it tracks a counter for each key. It starts empty. Each time counters_add is called on a given key, the corresponding counter is incremented. The current counter value can be retrieved by asking for the relevant key.

### Usage

The *counters* module, defined in `counters.h` and implemented in `counters.c`, implements a counters of `void*`, and exports the following functions:

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count);
void counters_delete(counters_t* ctrs);
```

### Implementation

We implement counters as a linked list similar to a set
The *counters* itself is represented as a `struct counters` containing a pointer to the head of the list; the head pointer is NULL when the set is empty.

Each node in the list is a `struct countersnode`, a type defined internally to the module.
Each setnode includes a pointer to the `int count`, a count of the number of times the key appears, and a pointer to a `const char* key`.

To insert a new key count in the set we create a new setnode to hold the `count`, and insert it at the head of the list.

To find an item from counters we iterate through the linked list until finding the correct key. 

The `counters_print` method prints a little syntax around the list, and between items, and prints it to a FILE*

The `counters_iterate` method calls the `itemfunc` function on each item by scanning the linked list.

The `counters_delete` method frees setnodes as it proceeds through the linked list.
It concludes by freeing the `struct counters`.

### Assumptions

No assumptions beyond those that are clear from the `counters.h`

### Files

* `Makefile` - compilation procedure
* `counters.h` - the interface
* `counters.c` - the implementation
* `counterTest.c` - unit test driver
* `test.txt` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make counters.o`.

### Testing

The `counterTest.c` program reads lines from stdin and stuffs them into a set, then pulls them back out.
It tests a few error and edge cases.

To test, simply `make test`.
See `testing.out` for details of testing and an example test run.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind`.
