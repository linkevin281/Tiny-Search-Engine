/* 
 * hashtableTest.c - CS50 unit test for 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * Kevin Lin
 * October 6, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "file.h"

static void nameKeyPrint(FILE* fp, const char* key, void* item);
static void delete(void* item);
static void itemCount(void* arg, const char* key, void* item);

int main(int argc, char const *argv[])
{
    hashtable_t *ht = NULL;
    char *name = NULL;
    char *key = NULL;
    int htCount = 0;

    printf("Create hashtable...\n");
    ht = hashtable_new(20);
    if (ht == NULL)
    {
        fprintf(stderr, "hashtable_new failed for ht\n");
        return 1;
    }

    printf("\nTesting hashtable_insert...\n");                                            // testing all failed hashtable_inserts
    printf("\nTest with null ht good key good item...\n");
    hashtable_insert(NULL, "Dartmouth", "Dartmouth");
    printf("Test with good key null item...\n");
    hashtable_insert(ht, "Dartmouth", NULL);
    printf("Test with good ht, null key good item...\n");
    hashtable_insert(ht, NULL, "Dartmouth");
    printf("Test with null ht, null key, null item...\n");
    hashtable_insert(NULL, NULL, NULL);

    printf("\nCount (should be zero): ");                                                 // testing hashtable_iterate
    htCount = 0;
    hashtable_iterate(ht, &htCount, itemCount);
    printf("%d\n", htCount);

    int keyValue = 0; 
    while (!feof(stdin)) {                                           
        if (keyValue == 0) {
            printf("Insert name: \n");
            name = file_readLine(stdin);
            keyValue++;
        }
        else {
            printf("Insert key: \n");
            key = file_readLine(stdin);
            if (key != NULL) {
                hashtable_insert(ht, key, name);
            }
            keyValue = 0;
            free(key);                                              // Unsure of the cause but there's always a memory leak 
                                                                    // here only when testing with a duplicate key 
                                                                    // mem leak is found because of file_readLine and not because of the hashtable
        }
    }
    if (keyValue == 1) {printf("Last input not taken\n");}

    printf("\nTesting hashtable_insert...\n");  
    printf("Inserted one,one\n");
    printf("Inserted two,two\n");
    printf("Inserted three,three\n");
    // duplicate key test
    printf("Inserted one,existing (should fail because key is duplicate)\n");
    // duplicate value test
    printf("Inserted existing,one (should succeed with duplicate value)\n");

    printf("Testing hashtable_print\n");                                               // testing hashtable_print
    printf("The hashtable:\n");
    hashtable_print(ht, stdout, nameKeyPrint);
    printf("\nExpected: \n{}{}{(two, two),}{}{}{}{}{}{}{}{}{}{}{(three, three),}{(existing, one),}{}{}{}{(one, one),}{}");
    printf("\n");

    printf("\nTesting hashtable_iterate\n");                                             // testing hashtable_iterate
    hashtable_iterate(ht, &htCount, itemCount);
    printf("These two values should be equal: 4 = %d\n", htCount);

    printf("\nTesting hashtable_find...\n");

    printf("For key [three]: three = %s\n", (char*) hashtable_find(ht, "three"));
    printf("For key [existing]: one = %s\n", (char*) hashtable_find(ht, "existing"));
    printf("For key [dne]: (null) = %s\n", (char*) hashtable_find(ht, "dne"));
    printf("Null hashtable: (null) = %s\n", (char*) hashtable_find(NULL, "key"));
    printf("Null key: (null) = %s\n", (char*) hashtable_find(ht, NULL));

    clearerr(stdin);      
    // read lines from stdin (not used in Make test but can be used if run manually)
    while (!feof(stdin)) {                                                
        printf("Input key: \n");
        key = file_readLine(stdin);
        printf("Key is: %s, Item is: %s\n", key, (char*)hashtable_find(ht, key));
        free(key);
    }

    printf("\ndelete the hashtable...\n");
    hashtable_delete(ht, delete);
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