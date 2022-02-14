/* 
 * set.c - CS50 'set' module
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
#include "mem.h"

/**************** local types ****************/
typedef struct setnode {
    void* item;                       // pointer to data for this item
    struct setnode *next;             // link to next node
    const char* key;                  // pointer to the key for this item
} setnode_t;

/**************** global types ****************/
typedef struct set {
    struct setnode *head;             // head of the list of items in set
} set_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static setnode_t* setnode_new(void* item, const char* key);

/**************** set_new() ****************/
/* see set.h for description */
set_t*
set_new(void)
{
    set_t* set = mem_malloc(sizeof(set_t));

    if (set == NULL) {
        return NULL;                         // return null if malloc fails
    }
    else {
        set->head = NULL;                    // otherwise set the head of set to null and return
        return set;
    }
}

/**************** setnode_new ****************/
/* Allocate and initialize a setnode */
static setnode_t*
setnode_new(void* item, const char* key)
{
    setnode_t* newNode = mem_malloc(sizeof(setnode_t));   // Allocate memory for new node

    if (newNode == NULL) {                                // return null if null
        return NULL;
    }
    else {                                                // else give newNode its values 
        newNode->item = item;
        newNode->next = NULL;
        newNode->key = key;
        return newNode;
    }
}

/**************** set_insert() ****************/
/* see set.h for description */
bool
set_insert(set_t* set, const char* key, void* item)
{
    if (set != NULL && item != NULL && key != NULL) {      // Check to make sure set item and key arent null
        if (set_find(set, key) != NULL) {                  // If the key already exists return false
            return false;
        }
        char* string = mem_malloc(strlen(key)+1);          // Allocate memory according to length of key
        strcpy(string, key);                               // Copy into same byte size of memory allocated
        setnode_t* newNode = setnode_new(item, string);    // Make the newNode store a pointer to the copied string instead of inputted key
        if (newNode != NULL) {
            newNode->next = set->head;                     // Give new node values
            set->head = newNode;
        }
    }
    return NULL;
}

/**************** set_find() ****************/
/* see set.h for description */
void*
set_find(set_t* set, const char* key)
{
    if (set == NULL || key == NULL) {
        return NULL;
    }
    else {
        for (setnode_t* node = set->head; node != NULL; node = node->next) {      // iterate through and look for matching key
            if (strcmp(node->key, key) == 0) {                                    // if found return 
                return node->item;
            }
        }
        return NULL;                                                              // key was not found so return null
    }

}

/**************** set_print() ****************/
/* see set.h for description */
void
set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item))
{
    if (fp != NULL) {
        if (set != NULL) {
            fputc('{', fp);
            for (setnode_t* node = set->head; node != NULL; node = node->next) {            // Iterate through nodes until null
                if (itemprint != NULL) {                                                    // print the node's item 
                    (*itemprint)(fp, node->key, node->item); 
                    fputc(',', fp);
                }
            }
            fputc('}', fp);
        }       
        else {
        fputs("(null)", fp);
        }
    }
}

/**************** set_iterate() ****************/
/* see set.h for description */
void
set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) )
{
    if (set != NULL && itemfunc != NULL) {
        for (setnode_t* node = set->head; node != NULL; node = node->next) {                   // Iterate through nodes and call itemfunc on each
        (*itemfunc)(arg, node->key, node->item); 
        }
    }
}

/**************** set_delete() ****************/
/* see set.h for description */
void
set_delete(set_t* set, void (*itemdelete)(void* item))
{
    if (set != NULL) {
        for (setnode_t* node = set->head; node != NULL; ) {
            if (itemdelete != NULL) {
                (*itemdelete)(node->item);      // delete item
            }
            setnode_t* next = node->next;       
            mem_free((void*)node->key);         // free the key
            mem_free(node);                     // free the node
            node = next;                        // iterate
        }
        mem_free(set);
    }

#ifdef MEMTEST
  mem_report(stdout, "End of set_delete");
#endif
}
