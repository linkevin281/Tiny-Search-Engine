/* 
 * pagedir.c - CS50 tse part 1
 *
 * see pagedir.h for more information.
 *
 * Kevin Lin
 * October 16, 2021
 */

#include </thayerfs/home/f004h3t/cs50-dev/tse-linkevin281/libcs50/webpage.h>
#include <string.h>

/* Function declarations */
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

/* *********** pagedir_init() *********** */
/* See pagedir.h for description */
bool
pagedir_init(const char* pageDirectory)
{
    FILE* file;
    char* crawlerPath = malloc((strlen(pageDirectory)+10)); 
    if (crawlerPath == NULL) {
        return false; 
    }
    sprintf(crawlerPath, "%s/.crawler", pageDirectory);        // construct crawler file pathname
    if ((file = fopen(crawlerPath, "w")) != NULL) {            // construct file and open   
        fclose(file);
        free(crawlerPath);
        return true;
    }      
    free(crawlerPath);
    return false;
}

/* *********** pagedir_save() *********** */
/* See pagedir.h for description */
void
pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID)
{
    int temp = docID;                                            // modify malloc size depending on number of docID digits
    int digits = 0;
    while (temp != 0) {
        temp /= 10;
        digits++;
    }
    FILE* file;
    char* filePath = malloc((strlen(pageDirectory)+digits+2));   
    sprintf(filePath, "%s/%d", pageDirectory, docID);           // constructfilePath  for page
    if ((file = fopen(filePath, "w")) != NULL) {
        fprintf(file, "%s\n", webpage_getURL(page));            // print URL, depth, and HTML
        fprintf(file, "%d\n", webpage_getDepth(page));
        fprintf(file, "%s\n", webpage_getHTML(page));
        fclose(file);
        free(filePath);
    }
    else {
       free(filePath); 
    }
}


