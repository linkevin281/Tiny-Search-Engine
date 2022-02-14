/* 
 * crawler.c - CS50 tse part 1
 *
 * see crawler.h for more information.
 *
 * Kevin Lin
 * October 16, 2021
 */

#include </thayerfs/home/f004h3t/cs50-dev/tse-linkevin281/libcs50/hashtable.h>
#include </thayerfs/home/f004h3t/cs50-dev/tse-linkevin281/libcs50/bag.h>
#include </thayerfs/home/f004h3t/cs50-dev/tse-linkevin281/libcs50/webpage.h>
#include </thayerfs/home/f004h3t/cs50-dev/tse-linkevin281/common/pagedir.h>
#include <string.h>


/* Function declarations */
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

/* *********** main() *********** */
/* See crawler.h for description */
int
main(const int argc, char* argv[])
{
    
    int maxDepth = atoi(argv[3]);
    int *depth = &maxDepth;
    parseArgs(argc, argv, &argv[1], &argv[2], depth);
    crawl(argv[1], argv[2], atoi(argv[3]));
    return 0;
}
/* *********** parseArgs() *********** */
/* See crawler.h for description */
static void
parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth)
{
    if (argc != 4) {                                               // argument count checl
        fprintf(stderr, "Incorrect number of arguments\n");      
        exit(1);
    }
    char* normalizedSeed = argv[1];

    if ((normalizedSeed = normalizeURL(*seedURL)) == NULL) {       // if normalization failed
        fprintf(stderr, "normalization failed\n"); 
        exit(1); 
    }
    if (!(isInternalURL(normalizedSeed))) {                        // if not internal 
        fprintf(stderr, "URL is not Internal\n");
        exit(1);
    }
    pagedir_init(*pageDirectory);                                  // initialize the directory for pages
    if (*maxDepth < 0 || *maxDepth > 10) {                         // Ensure maxDepth is in range
        fprintf(stderr, "maxDepth out of range 0 - 10\n");              
        exit(1);
    }
    free(normalizedSeed);                                          // free url malloc 
}

/* *********** crawl() *********** */
/* See crawler.h for description */
static void
crawl(char* seedURL, char* pageDirectory, const int maxDepth)
{
    char* seed = malloc(strlen(seedURL)*sizeof(char)+1);       // make seperate malloced memory for url              
    strcpy(seed, seedURL);  
    webpage_t* page = webpage_new(seed, 0, NULL);                                            
    if (page == NULL) {         // check if page creation worked
        fprintf(stderr, "Webpage creation failed\n");
        exit(1);
    }     
    hashtable_t* ht = hashtable_new(200);
    if (ht == NULL ) {                  // check if hashtable creation worked
        fprintf(stderr, "Hashtable creation failed\n");
        exit(1);
    }
    hashtable_insert(ht, seedURL, "1");                        // insert seedURL as key into ht (no malloc)
    bag_t* bag = bag_new();
    if (bag == NULL) {                           // check if bag creation worked
        fprintf(stderr, "Bag creation failed\n");
        exit(1);
    }                       
    bag_insert(bag, page);                                     // add original seedPage into bag
    int docID = 1;

    while ((page = bag_extract(bag)) != NULL) {                // while bag not empty extract a page
        if (webpage_fetch(page)) {                             // if html fetch sucessful
            printf("%d   Fetched: %s\n", webpage_getDepth(page), webpage_getURL(page));
            pagedir_save(page, pageDirectory, docID);          // save the page
            docID++;                                           // change docid
            if (webpage_getDepth(page) < maxDepth) {           // if depth hasnt been reached
                pageScan(page, bag, ht);                       // pageScan HTML
                printf("%d   Scanning: %s\n", webpage_getDepth(page), webpage_getURL(page));
            }
        }
        webpage_delete(page);
    }
    hashtable_delete(ht, NULL);
    bag_delete(bag, NULL);
}

/* *********** pageScan() *********** */
/* See crawler.h for description */
static void
pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen)
{
    int pos = 0;
    char* nextURL;
    int depth = webpage_getDepth(page);
    while ((nextURL = webpage_getNextURL(page, &pos)) != NULL) {                             // While another url still exists in bag
        printf("%d     Found: %s\n", depth, nextURL);
        if (isInternalURL(nextURL)) {
            if (hashtable_insert(pagesSeen, nextURL, " ")) {                                 // if its internal insert into seen 
                webpage_t* newPage = webpage_new(nextURL, webpage_getDepth(page)+1, NULL);   // make a new webpage for it
                if (newPage != NULL) {
                    bag_insert(pagesToCrawl, newPage);                                       // if it worked then set it to be crawled
                    printf("%d     Added: %s\n", depth + 1, nextURL);
                }
            }
            else {
                printf("%d    IgnDupl: %s\n", depth + 1, nextURL);
                free(nextURL);
            } 
        }
        else {
            printf("%d   IgnExtrn: %s\n", depth + 1, nextURL);
            free(nextURL);
        }
    }
    free(nextURL);
}