# CS50 TSE Querier
## Design Spec

In this document we reference the [Requirements Specification](REQUIREMENTS.md) and focus on the implementation-independent design decisions.
Here we focus on the core subset:

- User interface
- Inputs and outputs
- Functional decomposition into modules
- Pseudo code for logic/algorithmic flow
- Major data structures
- Testing plan

## User interface

As described in the [Requirements Spec](REQUIREMENTS.md), the querier's only interface with the user is on the command-line; it must always have two arguments.

```bash
$ querier pageDirectory indexFilename
```

## Inputs and outputs

*Input:*
 * pageDirectory - Is a directory produced by the crawler
 * indexFilename - Is the filepath to an .index file produced by the indexer

*Output:* Per the requirements spec, querier outputs an ordered list containing score, docID, and URL that is sorted by highest score at the top. 

 * Output Pattern : Score: ## || docID: ## || URL: ----------------------

## Functional decomposition into modules

We use the following modules or functions:

 1. *main*, Reads lines from stdin and initializes other modules
 2. *runQuery*, Runs the query and deals with the and/or operators 
 3. *tokenize*, Builds an array of words using isspace to separate words by spaces
 4. *queryOperation*, Runs an "and" or "or" operation between two queries
 5. *outputQuery*, Removes IDs one by one based on which hash the largest score and prints them out with score, docID, and URL

And some helper modules that provide data structures:

  1. *loadIndex*, Function used to load and .index file into an index internal structure
  2. *verifyInput*, Verifies char* input is a string of just uppercase and lowercase letters with space charaters
  3. *iterateFunc*, Function used to iterate through the index
  4. *checkArgs*, Checks main() caller provided args 
  5. *makeQuery*, Creates a query from a single word and index

## Pseudo code for logic/algorithmic flow

The querier will run as follows:

    validate parameters, initialize other modules
    if verify input
      if tokenize stdin
      build 2d char array of words 
        print current query
        create internal and external query
          for each word
            perform or operation between internal and external query if word is or and reset internal
            otherwise combine current word and internal query
            if and operation
              check if docID is in both queries and pick the lower count
            if or operation
              add docID if it is in at least 1 query and add counts
          print final query
          
## Major data structures

Helper modules provide all the data structures we need:

- *index*, word,counters(docID, count)
- *query*, containing an array of (int), counters(docID,count), int totalDocIDs made specifically for querier. Enables simple and/or operations between queries. 
