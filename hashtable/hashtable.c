/* 
 * hashtable.c - CS50 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * Kevin Lin
 * October 6, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "mem.h"
#include "hashtable.h"
#include "hash.h"

typedef struct hashtable {
    set_t** table;
    int size; 
} hashtable_t;

hashtable_t*
hashtable_new(const int num_slots)
{
    if (num_slots > 0) {
        hashtable_t* ht = malloc(sizeof(hashtable_t));
        if (ht != NULL) {
            ht->size = num_slots;
            ht->table = (set_t**) malloc(num_slots * sizeof(set_t**));

            for (int i = 0; i < num_slots; i++) {                        // fill the array with sets
                ht->table[i] = set_new();           
            }

            return ht;

        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
}

bool
hashtable_insert(hashtable_t* ht, const char* key, void* item) 
{
    if (ht != NULL && key != NULL && item != NULL) {
        unsigned long index = hash_jenkins(key, ht->size);
        return set_insert(ht->table[index], key, item);
    }
    else {
        return false;
    }
}

void*
hashtable_find(hashtable_t* ht, const char* key)
{
    if (ht != NULL && key != NULL) {
        unsigned long index = hash_jenkins(key, ht->size);
        return set_find(ht->table[index], key);
    }
    else {
        return NULL;
    }
}

void
hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item))
{
    if (fp != NULL) {
        if (ht != NULL) {
            for (int i = 0; i < ht->size; i++) {
                if (itemprint != NULL) {
                    set_print(ht->table[i], fp, itemprint);
                }
                else {
                    fputs("\n", fp);
                }
            }
        }
        else {
            fputs("(null)", fp);
        }
    }
}

void
hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item))
{
    if (ht != NULL && itemfunc != NULL) {
        for (int i = 0; i < ht->size; i++) {
            set_iterate(ht->table[i], arg, itemfunc);
        }
    }
}

void
hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item))
{
    if (ht != NULL && itemdelete != NULL) {
        for (int i = 0; i < ht->size; i++) {
            set_delete(ht->table[i], itemdelete);
        }
    }
    free(ht->table);
    free(ht);
}