# CS50 tae part 1
## CS50 Fall 2021

### crawler 

The crawler crawls a website and retrieves webpages starting with a specified URL. It parses the initial webpage, extracts any embedded URLs and retrieves those pages, and crawls the pages found at those URLs, but limiting itself to some threshold number of hops from the seed URL, and avoiding visiting any given URL more than once. It saves the pages, and the URL and depth for each, in files. When the crawler process is complete, the indexing of the collected documents can begin.

### Usage

$ crawler seedURL pageDirectory maxDepth

Implements the following functions

```c
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
```

### Implementation

We use two data structures: a 'bag' of pages that need to be crawled, and a 'hashtable' of URLs that we have seen during our crawl. Both start empty. The size of the hashtable (slots) is impossible to determine in advance, so we use 200

Follows pseudocode. 

### Assumptions

No assumptions beyond those that are clear from the `crawler.h`

### Files

* `Makefile` - compilation procedure
* `crawler.h` - the interface
* `crawler.c` - the implementation
* `testing.out` - testing output
* `testing.sh` - test script
* `valgrind.sh` - valgrind output
|   |-- .gitignore
|   |-- crawler.c
|   |-- testing.out
|   |-- testing.sh
|   `-- valgrind.sh
### Compilation

To compile, simply `make`.

### Testing

$ make test

Integration/system testing:

First, a sequence of invocations with erroneous arguments.

Second, a run with valgrind over a moderate-sized test case (such as toscrape at depth 1). 

Third, runs over all three CS50 websites (letters at depths 0,1,2,10, toscrape at depths 0,1,2,3, wikipedia at depths 0,1,2).

