#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "mem.h"


typedef struct countersnode {
    int count;                      // counter 
    struct countersnode *next;                 // link to next node
    int key;                        
} countersnode_t;

typedef struct counters {
    struct countersnode *head;                 // head of the list of counters
} counters_t;

counters_t*
counters_new(void)
{
    counters_t* counters = mem_malloc(sizeof(counters_t));

    if (counters == NULL) {
        return NULL;
    }
    else {
        counters->head = NULL;
        return counters;
    }
}

static countersnode_t*
countersnode_new(const int key)
{
    countersnode_t* newNode = mem_malloc(sizeof(countersnode_t));

    if (newNode == NULL) {
        return NULL;
    }
    else {
        newNode->count = 1;                                          // initial value is 1
        newNode->next = NULL;
        newNode->key = key;
        return newNode;
    }
}

static countersnode_t*
counters_find(counters_t* ctrs, const int key)
{
    if (ctrs == NULL || key < 0) {
        return NULL;
    }
    for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
        if (node->key == key) {
            return node;
        }
    }
    return NULL;
}   

int
counters_add(counters_t* ctrs, const int key)
{
    if (ctrs != NULL && key >= 0) {
        countersnode_t* node = counters_find(ctrs, key);
        if (node != NULL) {                                  // if node exists add to count
            node->count++;
            return node->count;
        } 
        else {                                               // otherwise make a new node for it and add it to the counters
            countersnode_t* newNode = countersnode_new(key); 
            if (newNode != NULL) {
                newNode->next = ctrs->head;
                ctrs->head = newNode;
            }
            return newNode->count;
        }
    }
    return 0;
}

int
counters_get(counters_t* ctrs, const int key)
{
    if (ctrs == NULL || key < 0) {                 
        return 0;
    } 
    else {
        countersnode_t* node = counters_find(ctrs, key);
        if (node != NULL) {                                  // if key pair exists then return the count 
            return node->count;   
        }
    }
    return 0;
}

bool
counters_set(counters_t* ctrs, const int key, const int count)
{
    if (ctrs == NULL || key < 0 || count < 0) {
        return false;
    }
    countersnode_t* node = counters_find(ctrs, key);
    if (node != NULL) {
        node->count = count;
        return true;
    }
    else {
        counters_add(ctrs, key);
        counters_find(ctrs, key)->count = count;
        return true;
    }
    return false;
}

void
counters_print(counters_t* ctrs, FILE* fp)
{
    if (fp != NULL) {
        if (ctrs != NULL) {
            fputc('{', fp);
            for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
                printf("%d=%d", node->key, node->count);
                fputc(',', fp);
            }
            fputc('}', fp);
        }       
        else {
        fputs("(null)", fp);
        }
    }
}

void
counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count))
{
    if (ctrs != NULL && itemfunc != NULL) {
        for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
        (*itemfunc)(arg, node->key, node->count); 
        }
    }
}

void
counters_delete(counters_t* ctrs)
{
    if (ctrs != NULL) {
        for (countersnode_t* node = ctrs->head; node != NULL; ) {
            countersnode_t* next = node->next;     // remember what comes next
            mem_free(node);                   // free the node
            node = next;                      // and move on to next
        }
        mem_free(ctrs);
    }

#ifdef MEMTEST
  mem_report(stdout, "End of counters_delete");
#endif
}