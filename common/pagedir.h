/* 
 * pagedir.c - CS50 tse part 1
 *
 * We create a re-usable module pagedir.c to handles the pagesaver mentioned in the design 
 * (writing a page to the pageDirectory), and marking it as a Crawler-produced pageDirectory 
 * (as required in the spec). We chose to write this as a separate module, in ../common, 
 * to encapsulate all the knowledge about how to initialize and validate a pageDirectory, 
 * and how to write and read page files, in one place... anticipating future use by the 
 * Indexer and Querier.
 *
 * Kevin Lin
 * October 16, 2021
 */

#include </thayerfs/home/f004h3t/cs50-dev/tse-linkevin281/libcs50/webpage.h>

/* *********** pagedir_init() *********** */
/* Initializes pagedir and constructs .crawler file in directory, opens file for writing, closes file
 *
 * We return:
 *   false on failure, true on success
 * Caller provides:
 *   const char* pageDirectory that is a directory
 */
bool pagedir_init(const char* pageDirectory);

/* *********** pagedir_init() *********** */
/* Constructs pathname in page file in pageDirectory, opens the file and prints URL, depth, and HTML 
 * We return:
 *   nothing
 * Caller provides:
 *   Valid webpage pointer, valid directory char*, unique docID
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
