#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "file.h"

static void countersCount(void* arg, const int key, const int count);

int main(int argc, char const *argv[])
{
    counters_t* ctrs = NULL;
    int key;
    int count = 0;
    int input;
    int keyValue = 0;

    printf("Create counters...\n");
    ctrs = counters_new();
    if (ctrs == NULL) {
    fprintf(stderr, "counters_new failed\n");
    return 1;
    }

    printf("\nTest with null counters good key...\n");
    counters_add(NULL, 1);
    printf("Test with good counters and bad key\n");
    counters_add(ctrs, -1);
    printf("Test with null counters and bad key\n");
    counters_add(NULL, -1);

    printf("\nCount (should be zero): ");
    count = 0;
    counters_iterate(ctrs, &count, countersCount);
    printf("%d\n", count);

    // read lines from stdin
    printf("\nTesting counters_add...\n");
    printf("Input key integers: \n");
    while(scanf( "%d", &key) != EOF) {
        if (counters_add(ctrs, key) == 1) {
        }
        printf("The key's counter is: %d\n", counters_get(ctrs, key));
    }


    printf("\nTesting counters_print, The counters:\n");                          // testing counters_print
    counters_print(ctrs, stdout);
    printf("\nShould Print: {4=4,3=3,2=2,1=1,}");
    printf("\n");

    clearerr(stdin);
    printf("\nTesting counters_get...\n");                                        // testing counters_get
    printf("Input key integer: \n");
    printf("Key is: %d, Count is: %d\n", 1, counters_get(ctrs, 1));
    printf("Key is: %d, Count is: %d\n", 2, counters_get(ctrs, 2));
    printf("Key is: %d, Count is: %d\n", 3, counters_get(ctrs, 3));
    printf("Key is: %d, Count is: %d\n", 4, counters_get(ctrs, 4));
    printf("Testing nonexisting key, expected = 0\n");
    printf("Key is: %d, Count is: %d\n", 5, counters_get(ctrs, 5));
    printf("Testing negative key, expected = 0\n");
    printf("Key is: %d, Count is: %d\n", -5, counters_get(ctrs, -5));


    while (scanf( "%d", &key) != EOF) {                                           // used when testing without test.txt
        printf("Key is: %d, Count is: %d\n", key, counters_get(ctrs, key));
    }

    clearerr(stdin);
    printf("\nTesting counters_set...\n");                                        // testing counters_set
    printf("Input key integer: \n");         

    printf("Testing basic set \n");
    printf("Key is: %d, Count is: %d\n", 1, counters_set(ctrs, 1, 10));
    printf("Testing negative (fail) set \n");
    printf("Key is: %d, Count is: %d\n", 2, counters_set(ctrs, 2, -2));
    printf("Testing 0 set \n");
    printf("Key is: %d, Count is: %d\n", 3, counters_set(ctrs, 3, 0));
    printf("Testing new key set \n");
    printf("Key is: %d, Count is: %d\n", 5, counters_set(ctrs, 5, 5));
    printf("Testing negative key (fail)\n");
    printf("Key is: %d, Count is: %d\n", -5, counters_set(ctrs, -5, 5));

    while (scanf( "%d", &input) != EOF) {                                         // used when testing without test.txt
        if (keyValue == 0) {
            printf("Input updated count: \n");
            keyValue++;
            key = input;
        }
        else {
            printf("Input key integer: \n");
            keyValue = 0;
            count = input;
            counters_set(ctrs, key, count);
        }
    }
    if (keyValue == 1) {printf("Last key not set\n");}

    printf("\nThe counters: (key=counter)\n");
    counters_print(ctrs, stdout);
    printf("\nShould be: {5=5,4=4,3=0,2=2,1=10,}");
    printf("\n");

    
    printf("\ndelete the counters...\n");
    counters_delete(ctrs);
    return 0;
}

// counts the items
static void countersCount(void* arg, const int key, const int count)
{
  int* ncounters = arg;

  if (ncounters != NULL)
    (*ncounters)++;
}