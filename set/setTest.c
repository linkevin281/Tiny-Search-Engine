/* 
 * setTest.c - CS50 unit test for 'set' module
 *
 * see set.h for more information.
 *
 * Kevin Lin
 * October 6, 2021
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "file.h"

static void nameKeyPrint(FILE* fp, const char* key, void* item);
static void delete(void* item);
static void itemCount(void* arg, const char* key, void* item);

int main(int argc, char const *argv[])
{
    set_t* set = NULL;
    char* name = NULL;   
    char* key = NULL;
    int setCount = 0;

    printf("Create set...\n");
    set = set_new();
    if (set == NULL) {
        fprintf(stderr, "set_new failed for set\n");
        return 1;
    }
    
    printf("\nTesting set_insert...\n");                            // testing expected fail set_insert

    printf("\nTest with null set good key good item...\n");
    set_insert(NULL, "Dartmouth", "Dartmouth");
    printf("Test with good key null item...\n");
    set_insert(set, "Dartmouth", NULL);
    printf("Test with good set, null key good item...\n");
    set_insert(set, NULL, "Dartmouth");
    printf("Test with null set, null key, null item...\n");
    set_insert(NULL, NULL, NULL);

    printf("\nCount (should be zero): ");                           // testing set_iterate
    setCount = 0; 
    set_iterate(set, &setCount, itemCount);
    printf("%d\n", setCount);

                                                                    // read lines from stdin / test.txt
    printf("\nTesting set_insert...\n");                           
    int keyValue = 0; 
    while (!feof(stdin)) {                                           
        if (keyValue == 0) {
            printf("Insert name: \n");
            name = file_readLine(stdin);
            if (name != NULL) {
                keyValue++;
            }
        }
        else {
            printf("Insert key: \n");
            key = file_readLine(stdin);
            if (key != NULL) {
                set_insert(set, key, name);
                keyValue = 0;
            }
            free(key);                                              // Unsure of the cause but there's always a memory leak 
                                                                    // here when testing with a duplicate key 
        }                                                           // mem leak is found because of file_readLine and not because of the set

    }
    if (keyValue == 1) {printf("Last input not taken\n");}
 
    printf("\nIf from make test: \n");                              // testing set_insert
    printf("Inserted one,one\n");
    printf("Inserted two,two\n");
    printf("Inserted three,three\n");
    // duplicate key test
    printf("Inserted one,existing (should succeed with duplicate value)\n");
    // duplicate value test
    printf("Inserted existing,one (should fail with duplicate key)");

    printf("Testing set_print\n");                                                                              //testing set_print
    printf("\nIf from make test, set should be: {(existing, one),(three, three),(two, two),(one, one),} \n");
    printf("The set:\n");
    set_print(set, stdout, nameKeyPrint);
    printf("\n");
                                                                                       // testing set_find
    printf("\nTesting set_find...\n");                                               
    printf("For key [three]: three = %s\n", (char*) set_find(set, "three"));           // Existing key
    printf("For key [existing]: one = %s\n", (char*) set_find(set, "existing"));       // Existing key
    printf("For key [dne]: (null) = %s\n", (char*) set_find(set, "dne"));              // Nonexisting key
    printf("Null set: (null) = %s\n", (char*) set_find(NULL, "key"));                  // NULL key 
    printf("Null key: (null) = %s\n", (char*) set_find(set, NULL));                    // NULL set

    clearerr(stdin);
    // read lines from stdin (not used in Make test but can be used if run manually)
    while (!feof(stdin)) {                                                
        printf("Input key: \n");
        key = file_readLine(stdin);
        printf("Key is: %s, Item is: %s\n", key, (char*)set_find(set, key));
        free(key);
    }

    printf("\ndelete the set...\n");
    set_delete(set, delete);
    return 0;
}

// counts the items
static void itemCount(void* arg, const char* key, void* item)
{
  int* nitems = arg;

  if (nitems != NULL && item != NULL) {
      (*nitems)++;    
  }
}

// prints name and key
void nameKeyPrint(FILE* fp, const char* key, void* item)
{
    char* name = item; 
    if (name == NULL) {
    fprintf(fp, "item: (null)");
    }
    if (key == NULL) {
        fprintf(fp, "Key: (null)");
    }
    if (name != NULL && key != NULL) {
        fprintf(fp, "(%s, %s)", key, name); 
    }
}

// deletes and frees the item 
void delete(void* item)
{
    if (item != NULL) {
        free(item);   
    }
}