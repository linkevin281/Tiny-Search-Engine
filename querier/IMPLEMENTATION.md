# CS50 TSE Querier
## Implementation Spec

In this document we reference the [Requirements Specification](REQUIREMENTS.md) and [Design Specification](DESIGN.md) and focus on the implementation-specific decisions.

-  Control flow: pseudo code for each of the functions
-  Testing plan


## Control flow

 1. *main*, Reads lines from stdin and initializes other modules
 2. *runQuery*, Runs the query and deals with the and/or operators 
 3. *tokenize*, Builds an array of words using isspace to separate words by spaces
 4. *queryOperation*, Runs an "and" or "or" operation between two queries
 5. *outputQuery*, Removes IDs one by one based on which hash the largest score and prints them out with score, docID, and URL

### main

The `main` function reads inputs from stdin until EOF. for each line input it calls runQuery() and outputQuery(if non null query). It deletes the query and frees the input. 

### runQuery

Pseudocode:

create internal and external query
create 2d array wordList
if input is verified
    if input is tokenized
        print out current query
        iterate through words in wordList
            if word is or
                or operation between external query and internal
                create new internal query
            otherwise
                and operation between internal query and new query created for given word
        

### tokenize

Build an array of words using (isspace) to separate words by spaces 

Pseudocode: 

create a 2d char array
create buffer char array
for each char in input
    if the char is a space
        copy over current buffer array into 2d array
        reset buffer
    else 
        normalize the char and add to buffer array
if current buffer is not a space
    add buffer array into 2d array 
check if operators start or end the 2d char array
    if so then exit with error
check if two operators are adjacent
    if so then exit with error
return 2d arary

### queryOperation

Comparies two queries with and/or and returns score + docIDs

Pseudocode: 

if query is empty then return just other query all
if operation is and
    for each docID in query1
        for each docID in query2
            if queries are the same
                pick lower docID score and add to queryNew

    return queryNew
if operation is or
    for each docID in query1
        add to query
    for each docID in query2
        add to query - if already exists 
             add two numbers together 


### outputQuery

if query is empty then print no documents matched
otherwise
    remove IDs one at a time from query
        iterate through docIDs to find largest score
        print largest score
        set largest score to 0 to "remove"

## Testing plan

A sampling of tests that are run:

1. Base test with various and and or combinations

2. Spaces in input test

3. Non-char/space in input test

4. Adjacent Operators tests

5. Start/end Operators tests

6. Invalid args tests

7. No matching docID test
> For Lab 4, as noted in the assignment, you may submit a smaller test run.
> Furthermore, we recommend turning off detailed logging output for these tests, as they make `testing.out` rather large!



