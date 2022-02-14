/* 
 * word.c - CS50 Palmer
 *
 * see word.h for more information.
 *
 * Kevin Lin
 * October 21, 2021
 */

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* normalizeWord(char* string);

/**************** normalizeWord() ****************/
/* see word.h for description */
char*
normalizeWord(char* string) 
{
    char* newString = malloc(strlen(string)+1);
    for(int i = 0; string[i]; i++) {
        newString[i] = tolower(string[i]);
    }
    return newString;
}
