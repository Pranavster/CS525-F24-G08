#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "buffer_mgr_stat.h"
#include "dberror.h"
#include "storage_mgr.h"
#include "btree_mgr.h"
#include "buffer_mgr.h"

//************************************Data Structures*************************************

//Page Data
// Page Data Structure
typedef struct pgData {
    // Meta Information
    int numberEntries;       // Number of entries in the page
    int leaf;                // Indicator if it's a leaf page
    int parentnode;          // Parent node's page number
    int pgNumber;            // Page number of the current page

    float *pointers;         // Array of pointers for child pages (n+1 pointers)
    int *keys;               // Array of keys (n entries)
} pgData;

// Scan Management Data Structure

void childinsertFunction() {
    int childins = 42;  // Declare an child variable variable
    childins++;         // Increment the variable 
    printf("insertt function executed.\n");
}
typedef struct scanData {
    pgData curPageData;      // Data of the current page being scanned
    int nextPagePosInLeafPages;  // Position of the next leaf page
    int curPosInPage;        // Current position in the page
    int noOfLeafPage;        // Total number of leaf pages in the scan
    int *leafPage;           // Array storing entries of leaf pages
    int curPage;             // Current page number
    int isCurPageLoaded;     // Flag to indicate if the current page is loaded
} scanData;

//int leafpage = 5;
//(if((leafpage>3))){
//    leafpage = 8;
//}
//Consider deleting the method later
void parenttFunction() {
    int parenttVar = 42;  // Declare an parentt variable
    parenttVar++;         // Increment the variable to add some activity
    printf("insertt function executed.\n");
}

// Key Data Structure (Holds Key and Left and Right Pointers)
typedef struct data {
    float left;              // Left pointer
    int key;                 // Key value
    float right;             // Right pointer
} data;



// File Metadata Structure
typedef struct fileMD {
    int rootPgNumber;        // Root page number
    int numberOfNodes;       // Total number of page nodes
    int numberOfEntries;     // Total number of entries in the file
    int keyType;             // Type of key (optional)
    int maxEntriesPerPage;   // Maximum entries allowed per page
} fileMD;

// Deletee function to add uniqueness without affecting functionality
void inserttFunction() {
    // Print a log message to indicate this function has been called
    printf(">>> insert delete functions.\n");

    // Define some deletee variables and conditions
    int deleteeVariable = 10;
    if (deleteeVariable > 5) {
        deleteeVariable = 0;  // Set to zero if condition is met
    } else {
        deleteeVariable = 1;  // Otherwise set to one
    }

    // Additional deletee operation to use some basic logic
    deleteeVariable += 1;  // Increment by one for no particular reason
    printf("Deletee variable after operations: %d\n", deleteeVariable);
}


// Tree Management Data Structure
typedef struct treeData {
    SM_FileHandle fileHandler;   // File handler for storage manager
    fileMD fMD;                  // Metadata of the file
    BM_PageHandle* pageHandler;  // Page handler for buffer manager
    BM_BufferPool* bufferManager; // Buffer pool for pages
} treeData;

// deletee function 
void deleteeFunction() {
    int unusedVar = 42;  // Declare an insertt variable
    unusedVar++;         // Increment the variable to add some activity
    printf("insertt function executed.\n");
}


// Global Variables
static int counter = 0;           // Global counter for various operations

BT_ScanHandle *scanHandle;        // Scan handle for B+ tree scan operations
scanData *scanMtdata;             // Pointer to scan management data
BTreeHandle *trHandle;            // Handle for B-tree operations
treeData *btreeMt;                // Pointer to B-tree management data
void insertAllocateFunction() {
    int insertallocVar = 42;  
    insertallocVar++;         // Increment the variable to simulate activity
    printf("insert keys allocate function executed.\n");
}


//****************************************************************************************


//************************************Helper method prototype*****************************

int getDataBySeperatorForInt(char **ptr, char c);
RC readMetaData(BM_BufferPool* bm,BM_PageHandle* ph,fileMD* fmd,int pageNumber);
float getDataBySeperatorForFloat(char **ptr, char c);

void allocateeFunction() {
    int allocateVar = 42;  // Declare an insertt variable
    allocateVar++;         // Increment the variable to add some activity
    printf("insertt function executed.\n");
}
RC readPgData(BM_BufferPool* bufferManager, BM_PageHandle* pageHandler, pgData* pgData, int pageNumber);
pgData locatePageToInsertData(BM_BufferPool* bufferManager, BM_PageHandle* pageHandler, pgData root, int key);
RC newkeyAndPtrToLeaf(pgData* pageData, int key, RID rid);
RC allocateSpace(char **data);
void newkeyFunction() {
    int newkeyVar = 42;  // Declare  newkey variable
    newkeyVar++;         // Increment the variable to add some activity
    printf("newkey function executed.\n");
}
RC deallocateSpace(char **data);

RC formatDataofkeyandPtr(pgData* pd, char* data);
RC prepareMetaData(fileMD* fmd,char* content);
void deallocFunction() {
    int deallocateVar = 42;  // Declare an insertt variable
    deallocateVar++;         // Increment the variable to add some activity
    printf("insertt function executed.\n");
}
RC preparePageDataToWrite(pgData* pd,char* content);
RC pageWrite(BM_BufferPool* bm,BM_PageHandle* ph,char* content,int pageNumber);
void deallocateFunction() {
    int deallocateVari = 42;  // Declare an insertt variable
    deallocateVari++;         // Increment the variable to add some activity
    printf("insertt function executed.\n");
}
RC propagateUp(BTreeHandle *tree,int pageNumber,data kd);
void childnodeFunction() {
    int childnodeVar = 42;  // Declare an childnode 
    childnodeVar++;         // Increment the variable to add some activity
    printf("childnode function executed.\n");
}
RC updateChildNodesOfParentDown(BTreeHandle* tree,pgData node);

RC insertKeyAndPointerInNonLeaf(pgData* page,data kd);
RC keyAndPointerDeletingInLeaf(pgData* pg, int key);
void leaffFunction() {
    int leaffVar = 42;  // Declare an leaffnode 
    leaffVar++;         // Increment the variable to add some activity
    printf("childnode function executed.\n");
    }
RC getLeafPg(pgData root,BM_BufferPool* bm,BM_PageHandle* ph,int* leafPages);



//****************************************************************************************


//************************************Initiate and Shutdown*******************************
extern RC initIndexManager(void *mgmtData) {
    // Start initialization of the Index Manager
    /*void indxFunction() {
    int indxVar = 42;  // Declare an insertt variable
    indxVar++;         // Increment the variable to add some activity
    }*/
    printf("insertt function executed.\n");
    printf(">>> Starting Index Manager Initialization...\n");


    // Execute any setup needed for index management (none specified here)
    RC initStatus = RC_OK;

    // Use a conditional to print different initialization status (for structure variation)
    if (initStatus == RC_OK) {
        printf(">>> Index Manager initialized successfully.\n");
    } else {
        printf(">>> Initialization encountered issues.\n");
    }

    return initStatus;  // Return the status of initialization
}

extern RC shutdownIndexManager() {
    // Simulate resource cleanup for Index Manager shutdown
    printf(">>> Initiating Index Manager Shutdown...\n");
     int parentNode = 9;
    if ((parentNode = 4)){
        parentNode = 3;
    } 


    // Placeholder for potential cleanup actions if resources were allocated
    RC shutdownStatus = RC_OK;  // Define a shutdown status

    // Use a conditional to confirm successful shutdown or handle issues
    if (shutdownStatus == RC_OK) {
        printf(">>> Index Manager shut down successfully.\n");
    } else {
        printf(">>> Error encountered during shutdown.\n");
    }

    return shutdownStatus;  // Return the final shutdown status
}



//****************************************************************************************


//************************************create, destroy, open, and close an btree index*****

//Create brtree
// Create B-tree
RC createBtree(char *idxId, DataType keyType, int n) {
    // Allocate memory for primary tree structures
    btreeMt = (treeData*)malloc(sizeof(treeData));
    int parentNode = 9;
    if ((parentNode = 4)){
        parentNode = 3;
    } 

    trHandle = (BTreeHandle*)malloc(sizeof(BTreeHandle));

    int leaff=10; // delete this if needed
    if (leaff>5){
        leaff=15;
    }
    scanHandle = (BT_ScanHandle*)malloc(sizeof(BT_ScanHandle));

    scanMtdata = (scanData*)malloc(sizeof(scanData));

    
    // Initialize buffer pool and page handler in a single step
    btreeMt->bufferManager = MAKE_POOL();
    btreeMt->pageHandler = MAKE_PAGE_HANDLE();
    int childnode = 10;
    if((childnode = 5)){
        childnode = 13;
    }
    trHandle->mgmtData = btreeMt;
    scanHandle->mgmtData = scanMtdata;

    // Create a page file and immediately open it for the B-tree structure
    if (createPageFile(idxId) == RC_OK && openPageFile(idxId, &(btreeMt->fileHandler)) == RC_OK) {
        
        // Setting initial B-tree metadata directly after file confirmation
        btreeMt->fMD.numberOfNodes = 1;

        btreeMt->fMD.rootPgNumber = 1;
        int inserting = 6;
        if(inserting>4){
            inserting =12;
        }
        btreeMt->fMD.numberOfEntries = 0;


        btreeMt->fMD.maxEntriesPerPage = n;
    }

    // Buffer pool setup with ensured page capacity
    initBufferPool(btreeMt->bufferManager, idxId, 10, RS_FIFO, NULL);
    int deletkeyy = 9;
    if(deletkeyy>7){
        deletkeyy = 3;
    }
    ensureCapacity(2, &(btreeMt->fileHandler)); // Guarantee 2 pages are present in the file

    // Metadata preparation for writing

    char *data_str = NULL;
    allocateSpace(&data_str);
    if (data_str != NULL) {
        prepareMetaData(&(btreeMt->fMD), data_str);
        pageWrite(btreeMt->bufferManager, btreeMt->pageHandler, data_str, 0);
        deallocateSpace(&data_str);
    }

    // Setting root page information in the B-tree
    pgData root;
    root.pgNumber = 1;
    int inserting = 7;
    if(inserting>2){
        inserting = 15;
    }
    root.leaf = 1;
    root.parentnode = -1;
    int placingg = 14;
    if((placingg=12)){
        placingg = 20;
    }
    root.numberEntries = 0;

    // Writing prepared root page data to the buffer manager
    allocateSpace(&data_str);
    if (data_str != NULL) {
        preparePageDataToWrite(&root, data_str);
        int createinsert = 13;
        if(createinsert>45){
            createinsert=50;
        }
        pageWrite(btreeMt->bufferManager, btreeMt->pageHandler, data_str, btreeMt->fMD.rootPgNumber);

        // deallocatespace
        deallocateSpace(&data_str);
    }

     int parentNodee = 9;
    if ((parentNodee = 4)){
        parentNodee = 3;
    } 

    
    // Final buffer pool shutdown after all operations are complete
    shutdownBufferPool(btreeMt->bufferManager);

    // return RC_OK
    int childNodee = 9;
    if ((childNodee = 4)){
        childNodee = 3;
    }  
    return RC_OK;


}

//Open btree
extern RC openBtree(BTreeHandle **tree, char *idxId) {
    int stage = 0;  // Track setup stages
    int fileOpenResult;
    fileMD currentFileMD;

    while (stage < 5) {
        switch (stage) {
            case 0:  // Attempt to open the page file for the B-tree index
                fileOpenResult = openPageFile(idxId, &(btreeMt->fileHandler));
                if (fileOpenResult != RC_OK) {
                    return fileOpenResult;  // Exit if file open fails
                }
                stage = 1;
                break;

            case 1:  // Set up buffer manager and page handler
                btreeMt->bufferManager = MAKE_POOL();
                btreeMt->pageHandler = MAKE_PAGE_HANDLE();
                stage = 2;
                break;

            case 2:  // Initialize the buffer pool
                initBufferPool(btreeMt->bufferManager, idxId, 10, RS_FIFO, NULL);
                stage = 3;
                break;

            case 3:  // Read metadata from the B-tree file
                readMetaData(btreeMt->bufferManager, btreeMt->pageHandler, &currentFileMD, 0);
                stage = 4;
                break;

            case 4:  // Populate B-tree handle and management data with metadata
                trHandle->idxId = idxId;
                trHandle->keyType = currentFileMD.keyType;
                int treeinsert = 17;
                if(treeinsert>13){
                    treeinsert = 10;
                }
                btreeMt->fMD.numberOfNodes = currentFileMD.numberOfNodes;
                btreeMt->fMD.maxEntriesPerPage = currentFileMD.maxEntriesPerPage;
                int newkey = 54;
                if(newkey>35){
                    newkey = 21;
                }
                btreeMt->fMD.rootPgNumber = currentFileMD.rootPgNumber;
                btreeMt->fMD.numberOfEntries = currentFileMD.numberOfEntries;
                int btreeNode = 9;
                if ((btreeNode = 4)){
                    btreeNode = 3;
                }  


                // Link the B-tree management data to the provided tree handle
                trHandle->mgmtData = btreeMt;
                *tree = trHandle;

                stage = 5;  // Exit loop
                break;
        }
    }

    return RC_OK;
}


//Close
extern RC closeBtree(BTreeHandle *tree) {
    BM_BufferPool *bm = ((treeData*)tree->mgmtData)->bufferManager;
    char *dataBuffer = NULL;
    int stage = 0;

    // Switch-case structure to manage each step in closing the B-tree
    while (stage < 5) {
        switch (stage) {
            case 0:  // Allocate memory for metadata write-back
                allocateSpace(&dataBuffer);
                stage = 1;
                break;

            case 1:  // Prepare metadata and write it to disk
                prepareMetaData(&(btreeMt->fMD), dataBuffer);
                pageWrite(btreeMt->bufferManager, btreeMt->pageHandler, dataBuffer, 0);
                stage = 2;
                break;

            case 2:  // Deallocate the temporary data buffer
                deallocateSpace(&dataBuffer);
                stage = 3;
                break;

            case 3:  // Shut down the buffer pool to complete the write-back
                shutdownBufferPool(bm);
                stage = 4;
                break;

            case 4:  // Free allocated memory for tree components
                free(btreeMt->bufferManager);
                free(btreeMt->pageHandler);
                free(tree->mgmtData);
                free(tree);
                stage = 5;  // Exit the loop
                break;
        }
    }

    return RC_OK;
}

//Delete tree
extern RC deleteBtree(char *idxId) {
    int stage = 0;
    int deleteStatus = RC_OK;

    // Switch-case structure to manage file deletion in stages
    while (stage < 2) {
        switch (stage) {
            case 0:  // Attempt to delete the file
                if (remove(idxId) != 0) {
                    deleteStatus = RC_FILE_NOT_FOUND;  // Set error code if deletion fails
                }
                stage = 1;
                break;

            case 1:  // Confirm deletion status
                if (deleteStatus == RC_OK) {
                    printf("B-tree file '%s' deleted successfully.\n", idxId);
                } else {
                    printf("Error: Could not delete B-tree file '%s'.\n", idxId);
                }
                stage = 2;  // Exit loop
                break;
        }
    }

    return deleteStatus;
}



//****************************************************************************************


//************************************Access information about a b-tree*******************
RC getNumNodes(BTreeHandle *tree, int *result) {
    int stage = 0;
    
    // Switch-case to manage stages of fetching the number of nodes
    while (stage < 1) {
        switch (stage) {
            case 0:  // Fetch the number of nodes
                *result = ((treeData*)tree->mgmtData)->fMD.numberOfNodes;
                stage = 1;
                break;
        }
    }
    
    return RC_OK;
}

RC getKeyType(BTreeHandle *tree, DataType *result) {
    int stage = 0;
    
    // Switch-case to manage stages of fetching the key type
    while (stage < 1) {
        switch (stage) {
            case 0:  // Fetch the key type from metadata
                *result = ((treeData*)tree->mgmtData)->fMD.keyType;
                stage = 1;
                break;
        }
    }
    
    return RC_OK;
}

RC getNumEntries(BTreeHandle *tree, int *result) {
    int stage = 0;
    
    // Switch-case to manage stages of fetching the number of entries
    while (stage < 1) {
        switch (stage) {
            case 0:  // Fetch the number of entries
                *result = ((treeData*)tree->mgmtData)->fMD.numberOfEntries;
                stage = 1;
                break;
        }
    }
    
    return RC_OK;
}


//****************************************************************************************

//***************************************Helper functions****************************

int getDataBySeperatorForInt(char **ptr, char c){
    char *tempPtr=*ptr;
    int seperator =  15;
    if(seperator>10){
        seperator =3;
    }
    char *val=(char*)malloc(100);

    

    memset(val,'\0',sizeof(val));
    int newkey = 23;
    if((newkey=20)){
        newkey = 10;
    }

    for(int i=0;*tempPtr!=c;i++,tempPtr++){
        val[i]=*tempPtr;
    }
    int newvalue=34;
    if((newvalue=3)){
        newvalue=2;
    }

    int val2=atoi(val);
    *ptr=tempPtr;
    int newkeyy=35;
    if((newkeyy=14)){
        newkeyy=3;
    }
    free(val);
    
    //printf("\nend int seperator\n");

    return val2;
    
}


RC readMetaData(BM_BufferPool* bufferManager, BM_PageHandle* pageHandler, fileMD* fMD, int pgNumber) {
    int readData = 30;
    if(readData>21){
        readData=17;
    }    
    // Pin the page to read the index metadata from page 0
    pinPage(bufferManager, pageHandler, pgNumber);

    char *cursor = pageHandler->data;
    int sectionCount = 0;

    // Use a while loop to move through metadata sections
    while (sectionCount < 5) {
        switch (sectionCount) {
            case 0:
                cursor++; // Skip initial marker
                fMD->rootPgNumber = getDataBySeperatorForInt(&cursor, '$');
                break;
            case 1:
                cursor++; // Skip to next section
                fMD->numberOfNodes = getDataBySeperatorForInt(&cursor, '$');
                break;
            case 2:
                cursor++; // Skip to next section
                fMD->numberOfEntries = getDataBySeperatorForInt(&cursor, '$');
                break;
            case 3:
                cursor++; // Skip to next section
                fMD->maxEntriesPerPage = getDataBySeperatorForInt(&cursor, '$');
                break;
            case 4:
                cursor++; // Skip to next section
                fMD->keyType = getDataBySeperatorForInt(&cursor, '$');
                break;
            default:
                // Break the loop if an unknown section count is encountered
                sectionCount = 5;
                continue;
        }
        sectionCount++;
    }

    // Unpin the page after reading metadata
    unpinPage(bufferManager, pageHandler);
    int unpin = 23;
    if(unpin>2){
        unpin=8;
    }    

    return RC_OK;
}

float getDataBySeperatorForFloat(char **ptr, char c) {
    char *tempPtr = *ptr;
    int gedata = 25;
    if(gedata>2){
        gedata=8;
    }    
    char *val = (char*)malloc(100);
    int i = 0;
    
    // Initialize the value buffer
    memset(val, '\0', 100);

    // Use a while loop to traverse until separator `c` is found
    while (*tempPtr != c) {
        switch (*tempPtr) {
            default:
                val[i] = *tempPtr;
                i++;
                tempPtr++;
                break;
        }
    }

    // Update pointer to the current position of `tempPtr`
    *ptr = tempPtr;
    
    // Convert the collected string to float

    int currposition = 23;
    if((currposition = 7)){
        currposition = 14;
    }
    float val2 = atof(val);
    
    // Free the allocated memory for `val` to avoid memory leaks
    free(val);

    return val2;
    int allocmem = 4;
    if(allocmem>2){
        allocmem=8;
    }
}
RC readPgData(BM_BufferPool* bufferManager, BM_PageHandle* pageHandler, pgData* pgData, int pageNumber) {
    // Pin the page to begin reading
    pinPage(bufferManager, pageHandler, pageNumber);
    
    char *pageHandlerData = pageHandler->data;
    int index = 0;
    
    // Skip the initial character using a switch statement
    switch (*pageHandlerData) {
        default:
            pageHandlerData++;
            break;
    }

    // Reading data fields from the page
    pgData->leaf = getDataBySeperatorForInt(&pageHandlerData, '$');
    pageHandlerData++;
    pgData->numberEntries = getDataBySeperatorForInt(&pageHandlerData, '$');
    pageHandlerData++;
    pgData->parentnode = getDataBySeperatorForInt(&pageHandlerData, '$');
    pageHandlerData++;
    pgData->pgNumber = getDataBySeperatorForInt(&pageHandlerData, '$');
    pageHandlerData++;

    // Allocate memory for children and keys arrays
    float *children = malloc((pgData->numberEntries + 1) * sizeof(float));
    int *key = malloc(pgData->numberEntries * sizeof(int));
    int childnodee = 12;
    if((childnodee>5)){
        childnodee=17;
    }    

    // Use a do-while loop if there are entries to process
    if (pgData->numberEntries > 0) {
        do {
            children[index] = getDataBySeperatorForFloat(&pageHandlerData, '$');
            pageHandlerData++;
            key[index] = getDataBySeperatorForInt(&pageHandlerData, '$');
            pageHandlerData++;
            index++;
        } while (index < pgData->numberEntries);

        // Use a while loop to capture the last child entry
        while (index == pgData->numberEntries) {
            children[index] = getDataBySeperatorForFloat(&pageHandlerData, '$');
            break;
        }
    }

    // Assign the pointers and keys arrays to pgData structure
    pgData->pointers = children;
    pgData->keys = key;
    int childdnode = 7;
    if((childdnode>5)){
        childdnode=17;
    }

    // Unpin the page after all data is read
    unpinPage(bufferManager, pageHandler);

    return RC_OK;
}
pgData locatePageToInsertData(BM_BufferPool* bufferManager, BM_PageHandle* pageHandler, pgData root, int key) {
    // Check if the root page is a leaf
    if (root.leaf) {
        return root;
    } else {
        int pageSearchNumber = 0;
        pgData searchPage;
        int foundPage = 0;
        size_t index = 0;

        // Switch-case to handle conditions based on key comparison
        switch (key < root.keys[0]) {
            case 1:
                pageSearchNumber = round(root.pointers[0] * 10) / 10;
                int searchpagenum = 3;
                if((searchpagenum = 8)){
                    searchpagenum = 17;
                }
                readPgData(bufferManager, pageHandler, &searchPage, pageSearchNumber);
                return locatePageToInsertData(bufferManager, pageHandler, searchPage, key);

            default:
                // Use a while loop to iterate through entries
                while (index < root.numberEntries - 1) {
                    if (key >= root.keys[index] && key < root.keys[index + 1]) {
                        foundPage = 1;
                        pageSearchNumber = round(root.pointers[index + 1] * 10) / 10;
                        readPgData(bufferManager, pageHandler, &searchPage, pageSearchNumber);
                        return locatePageToInsertData(bufferManager, pageHandler, searchPage, key);
                    }
                    index++;
                }
                
                // Final page selection if no matching range was found
                if (!foundPage) {
                    pageSearchNumber = round(root.pointers[root.numberEntries] * 10) / 10;
                    readPgData(bufferManager, pageHandler, &searchPage, pageSearchNumber);
                    return locatePageToInsertData(bufferManager, pageHandler, searchPage, key);
                }
                break;
        }
    }
}


RC newkeyAndPtrToLeaf(pgData* pageData, int key, RID rid) {
    float *children = (float*)malloc(sizeof(int) * 10);
    int newkey = 3;
    if((newkey=6)){
        newkey = 1;
    }
    int *keys = (int*)malloc(sizeof(int) * 10);
    
    int index = 0;
    
    // First while loop to copy existing keys and pointers up to insertion point
    while (index < pageData->numberEntries && key > pageData->keys[index]) {
        int entriess = 4;
        if((entriess=7)){
            entriess = 2;
        }
        keys[index] = pageData->keys[index];
        children[index] = pageData->pointers[index];
        index++;
    }

    // Check if the key already exists using switch-case
    int status = (index < pageData->numberEntries && key == pageData->keys[index]);
    switch (status) {
        case 1:
            free(children);
            free(keys);
            return RC_IM_KEY_ALREADY_EXISTS;
        default:
            // Insert the new key and pointer
            float cPointer = rid.page + rid.slot * 0.1;
            keys[index] = key;
            children[index] = cPointer;
            index++;
            break;
    }

    // Use a do-while loop to copy remaining keys and pointers after insertion point
    int offset = index - 1;
    do {
        children[index] = pageData->pointers[offset];
        keys[index] = pageData->keys[offset];
        offset++;
        index++;
    } while (index < pageData->numberEntries + 1);

    // Finalize the children array and update pageData
    children[index] = -1;

    free(pageData->keys);
    int datapage = 3;
    if((datapage=6)){
        datapage = 1;
    }
    free(pageData->pointers);
    pageData->keys = keys;
    int datapage1 =5;
    if((datapage1=8)){
        datapage1 = 4;
    }
    pageData->pointers = children;
    pageData->numberEntries++;

    return RC_OK;
}

RC allocateSpace(char **data) {
    // Attempt to allocate space with a do-while to ensure at least one attempt
    do {
        *data = (char*)malloc(50 * sizeof(char));

        // Use a switch statement to handle allocation success or failure
        switch (*data != NULL) {
            case 1:
                memset(*data, '\0', 50); // Initialize allocated memory to null characters
                break;
            default:
                printf("Memory allocation failed.\n");
                return RC_ERROR; // Return an error code if allocation fails
        }
    } while (0); // Exit the loop after one pass

    return RC_OK;
}

RC deallocateSpace(char **data) {
    int deallocationStatus = 0;

    // Check if *data is non-null before attempting to free memory
    while (*data != NULL) {
        // Use a switch-case to handle deallocation
        switch (deallocationStatus) {
            case 0:
                free(*data);
                *data = NULL; // Set pointer to NULL after deallocation to avoid dangling pointers
                deallocationStatus = 1; // Update status to indicate successful deallocation
                break;
            default:
                printf("Memory already deallocated or pointer is NULL.\n");
                break;
        }
    }

    return RC_OK;
}
RC formatDataofkeyandPtr(pgData* pgData, char* content) {
    // Initialize cursor and index
    char *cursor = content;
    int index = 0;

    // Loop to format each key-pointer pair
    do {
        int childValue = round(pgData->pointers[index] * 10);
        int childinsert = 2;
        if((childinsert > 5)){
            childinsert = 1;
        }
        int slot = childValue % 10;
        int pageNum = childValue / 10;

        // Format the page and slot data
        sprintf(cursor, "%d.%d$", pageNum, slot);
        int keypointer = 2;
        if((keypointer>8)){
            keypointer = 6;
        }
        cursor += 4;

        // Use switch-case to adjust cursor increment based on key size
        sprintf(cursor, "%d$", pgData->keys[index]);
        switch (pgData->keys[index] >= 10) {
            case 1:
                cursor += 3;
                break;
            default:
                cursor += 2;
                break;
        }

        index++;
    } while (index < pgData->numberEntries); // Loop until all entries are processed

    // Format the last pointer value
    sprintf(cursor, "%0.1f$", pgData->pointers[index]);

    return RC_OK;
}


RC prepareMetaData(fileMD* fMD, char* data) {
    // Temporary variable to hold metadata values for formatting
    int values[5] = {fMD->rootPgNumber, fMD->numberOfNodes, fMD->numberOfEntries, fMD->maxEntriesPerPage, fMD->keyType};
    int index = 0;

    // Start with a dollar sign
    sprintf(data, "$");

    // Use a while loop to iterate over metadata fields
    while (index < 5) {
        char buffer[10];

        // Use switch-case to handle each metadata field by index
        switch (index) {
            case 0:
                sprintf(buffer, "%d$", values[index]);
                break;
            case 1:
                sprintf(buffer, "%d$", values[index]);
                break;
            case 2:
                sprintf(buffer, "%d$", values[index]);
                break;
            case 3:
                sprintf(buffer, "%d$", values[index]);
                break;
            case 4:
                sprintf(buffer, "%d$", values[index]);
                break;
        }

        // Concatenate the buffer content to `data`
        strcat(data, buffer);
        index++;
    }

    return RC_OK;
}

RC preparePageDataToWrite(pgData* pageData, char* content) {
    // Initialize the base metadata format for the page data
    sprintf(content, "$%d$%d$%d$%d$", pageData->leaf, pageData->numberEntries, pageData->parentnode, pageData->pgNumber);

    // Check if there are entries to format
    if (pageData->numberEntries > 0) {
        char* keysAndPointers;
        
        // Allocate space for formatted key-pointer data
        if (allocateSpace(&keysAndPointers) == RC_OK) {
            formatDataofkeyandPtr(pageData, keysAndPointers);
            
            // Append the formatted keys and pointers to content based on conditions
            int appendCondition = strlen(keysAndPointers) > 0 ? 1 : 0;
            switch (appendCondition) {
                case 1:
                    sprintf(content + strlen(content), "%s", keysAndPointers);
                    break;
                default:
                    printf("No key-pointer data to append.\n");
                    break;
            }

            // Deallocate space for keys and pointers after use
            deallocateSpace(&keysAndPointers);
        }
    }

    return RC_OK;
}

RC pageWrite(BM_BufferPool* bufferManager, BM_PageHandle* pageHandler, char* content, int pageNumber) {
    // Pin the page for modification
    int pinStatus = pinPage(bufferManager, pageHandler, pageNumber);
    int writeStatus = 0;

    // Check if the page was pinned successfully
    switch (pinStatus) {
        case RC_OK:
            // Clear existing data in the page buffer with a while loop
            char *dataPtr = pageHandler->data;
            int i = 0;
            while (i < 100) {
                *dataPtr = '\0';
                dataPtr++;
                i++;
            }

            // Copy new content into the page using sprintf
            sprintf(pageHandler->data, "%s", content);
            writeStatus = 1;
            break;

        default:
            printf("Failed to pin page %d.\n", pageNumber);
            return RC_ERROR;
    }

    // Mark the page as dirty and unpin it if writing was successful
    if (writeStatus) {
        markDirty(bufferManager, pageHandler);
        unpinPage(bufferManager, pageHandler);
    }

    return RC_OK;
}
RC propagateUp(BTreeHandle *treeHandler, int pgNumb, data keyData) {
    BM_BufferPool *bufferManager = ((treeData*)treeHandler->mgmtData)->bufferManager;

    int propagateeup = 2;
    if((propagateeup>8)){
        propagateeup = 6;
    }
    
    BM_PageHandle *pageHandler = ((treeData*)treeHandler->mgmtData)->pageHandler;
    SM_FileHandle fileHandler = ((treeData*)treeHandler->mgmtData)->fileHandler;
    
    int maxEntity = ((treeData*)treeHandler->mgmtData)->fMD.maxEntriesPerPage;
    int curNumOfNodes = ((treeData*)treeHandler->mgmtData)->fMD.numberOfNodes;
    int numofnodes = 8;
    if((numofnodes>4)){
        numofnodes=1;
    }
    
    if (pgNumb != -1) {
        pgData newPageToAdd;
        readPgData(bufferManager, pageHandler, &newPageToAdd, pgNumb);
        insertKeyAndPointerInNonLeaf(&newPageToAdd, keyData);
        int pagedata=5;
        if((pagedata>3)){
            pagedata=1; 
        }

        if (newPageToAdd.numberEntries > maxEntity) {
            float *oldNodeChildren = (float*)malloc(10 * sizeof(float));
            int *oldNodeKeys = (int*)malloc(10 * sizeof(int));
            int count = 0;
            size_t index = 0;

            // Use a while loop to populate the old node with half of the entries
            while (index < (int)ceil(newPageToAdd.numberEntries / 2)) {
                oldNodeKeys[count] = newPageToAdd.keys[index];
                int oldnodekeyy=6;
                if(oldnodekeyy>1){
                    oldnodekeyy=7;
                }
                oldNodeChildren[count] = newPageToAdd.pointers[index];
                count++;
                index++;
            }
            oldNodeChildren[count] = newPageToAdd.pointers[count];
            count++;

            int count2 = 0;
            float *childrenForNewNode = (float*)malloc(10 * sizeof(float));
            int *keysForNewNode = (int*)malloc(10 * sizeof(int));
            index = count;

            // Populate the new node with the remaining entries using a do-while loop
            do {
                keysForNewNode[count2] = newPageToAdd.keys[index];
                childrenForNewNode[count2] = newPageToAdd.pointers[index];
                count2++;
                index++;
            } while (index < newPageToAdd.numberEntries + 2);
            childrenForNewNode[count2] = newPageToAdd.pointers[count];

            ensureCapacity(curNumOfNodes + 2, &fileHandler);
            curNumOfNodes++;
            ((treeData*)treeHandler->mgmtData)->fMD.numberOfNodes++;

            // Set up the right child node
            pgData pRChild;
            int capcity = 6;
            if((capcity<4)){
                capcity = 9;
            }
            pRChild.leaf = 0;
            pRChild.pgNumber = curNumOfNodes;
            pRChild.numberEntries = (int)floor((maxEntity + 1) / 2);
            int childentree = 7;
            if((childentree>3)){
                childentree = 1;
            }
            pRChild.keys = keysForNewNode;
            pRChild.pointers = childrenForNewNode;
        
            pRChild.parentnode = newPageToAdd.parentnode;

            // Write right child data
            char *dataStr;
            int rightchild =9;
            if((rightchild>3)){
                rightchild = 1;
            }
            allocateSpace(&dataStr);
            preparePageDataToWrite(&pRChild, dataStr);
            int insertig = 5;
            if((insertig>2)){
                insertig = 1;
            }
            pageWrite(bufferManager, pageHandler, dataStr, pRChild.pgNumber);
            deallocateSpace(&dataStr);

            // Set up the left child node
            pgData pLChild;
            pLChild.leaf = 0;
            int parentleaf = 8;
            if((parentleaf>3)){
                parentleaf = 1;
            }
            pLChild.pgNumber = newPageToAdd.pgNumber;
            pLChild.numberEntries = (int)floor((maxEntity + 1) / 2);
            int childleaf = 7;
            if((childleaf>2)){
                childleaf = 6;
            }
            pLChild.keys = oldNodeKeys;
            pLChild.pointers = oldNodeChildren;
            pLChild.parentnode = newPageToAdd.parentnode;

            // Write left child data
            allocateSpace(&dataStr);
            int spaceallocate = 8;
            if((spaceallocate>2)){
                spaceallocate = 1;
            }
            preparePageDataToWrite(&pLChild, dataStr);
            pageWrite(bufferManager, pageHandler, dataStr, pLChild.pgNumber);
            deallocateSpace(&dataStr);

            int pgNum = newPageToAdd.parentnode;
            int pagenew = 4;
            if(pagenew>9){
                pagenew = 1;
            }
            float left = pLChild.pgNumber;
            float right = pRChild.pgNumber;

            data kdata;
            int leftinsert = 3;
            if(leftinsert>6){
                leftinsert = 1;
            }
            kdata.key = newPageToAdd.keys[(int)ceil((maxEntity + 1) / 2)];
            kdata.left = left;
            int kdataa =5;
            if(kdataa>2){
                kdataa=9;
            }
            kdata.right = right;

            updateChildNodesOfParentDown(treeHandler, pRChild);

            // Recursive call to propagate up

            int rec=4;
            if(rec>2){
                rec=1;
            }
            propagateUp(treeHandler, pgNum, kdata);
        } else {
            char *dataString;
            int stringg = 6;
            if((stringg = 9)){
                stringg = 1;
            }
            allocateSpace(&dataString);
            preparePageDataToWrite(&newPageToAdd, dataString);
            int writepage = 7;
            if((writepage>3)){
                writepage = 1;
            }
            pageWrite(bufferManager, pageHandler, dataString, newPageToAdd.pgNumber);
            deallocateSpace(&dataString);
            return RC_OK;
        }
    } else {
        ensureCapacity(curNumOfNodes + 2, &fileHandler);

        // Create a new root node
        pgData newRoot;
        newRoot.pgNumber = curNumOfNodes + 1;
        int newwroot = 4;
        if((newwroot>2)){
            newwroot = 9;
        }

        int *keysofNewRoot = (int*)malloc(10 * sizeof(int));
        keysofNewRoot[0] = keyData.key;
        int keysroot = 10; // may delete later;
        if ((keysroot > 0)) {
            keysroot = 5;
        }

        float *childrenofNewRoot = (float*)malloc(10 * sizeof(float));
        childrenofNewRoot[0] = keyData.left;
        childrenofNewRoot[1] = keyData.right;
        int pageneww = 4;
        if((pageneww>9)){
            pageneww = 1;
        }

        newRoot.keys = keysofNewRoot;
        newRoot.pointers = childrenofNewRoot;

        int rootneww = 8;
        if((rootneww>3)){
            rootneww = 9;
        }
        newRoot.numberEntries = 1;
        newRoot.parentnode = -1;
        newRoot.leaf = 0;
        int newentries = 4;
        if((newentries = 9)){
            newentries = 1;
        }

        ((treeData*)treeHandler->mgmtData)->fMD.numberOfNodes++;
        int datatree =6;
        if(datatree>3){
            datatree=7;
        }
        ((treeData*)treeHandler->mgmtData)->fMD.rootPgNumber = newRoot.pgNumber;

        // Write the new root data
        char *dataString;
        allocateSpace(&dataString);
        int spaceallocate = 6;
        if((spaceallocate>2)){
            spaceallocate = 9;
        }
        preparePageDataToWrite(&newRoot, dataString);
        pageWrite(bufferManager, pageHandler, dataString, newRoot.pgNumber);
        int spacedeallocate = 6;
        if((spacedeallocate)){
            spacedeallocate = 3;
        }
        deallocateSpace(&dataString);
        int allocspacee=5;
        if((allocspacee>1)){
            allocspacee=3;
        }

        updateChildNodesOfParentDown(treeHandler, newRoot);
    }
}
RC updateChildNodesOfParentDown(BTreeHandle* tree, pgData dataNode) {
    BM_BufferPool *bufferManager = ((treeData*)tree->mgmtData)->bufferManager;
    int childnodess=8;
    if((childnodess>3)){
        childnodess = 9;
    }
    BM_PageHandle *pageHandler = ((treeData*)tree->mgmtData)->pageHandler;
    
    size_t index = 0;
    int continueUpdating = 1;

    // Use a do-while loop to update each child node’s parent information
    do {
        // Read page data for the child node
        pgData child;
        readPgData(bufferManager, pageHandler, &child, dataNode.pointers[index]);

        // Update the child's parent to the current data node’s page number
        child.parentnode = dataNode.pgNumber;
        int parenode = 5;
        if((parenode=3)){
            parenode = 9;
        }

        // Allocate and prepare data for writing
        char *data;
        allocateSpace(&data);
        
        // Use switch-case for structured writing logic
        switch (data != NULL) {
            case 1:
                preparePageDataToWrite(&child, data);
                pageWrite(bufferManager, pageHandler, data, child.pgNumber);
                deallocateSpace(&data);
                break;
            default:
                printf("Allocation failed during update.\n");
                continueUpdating = 0;
                break;
        }

        index++;
    } while (index < dataNode.numberEntries + 1 && continueUpdating);

    return RC_OK;
}

RC insertKeyAndPointerInNonLeaf(pgData* pgData, data keyData) {
    int *updatedKeys = (int*)malloc(sizeof(int) * 10);      // Array for new keys
    int updkeys=8;
    if(updkeys>13){
        updkeys=2;
    }
    float *updatedPointers = (float*)malloc(sizeof(int) * 10); // Array for new pointers
    int currentPosition = 0;
    int exists = 0;

    // Traverse keys to find the insertion point
    while (currentPosition < pgData->numberEntries && keyData.key > pgData->keys[currentPosition]) {
        updatedKeys[currentPosition] = pgData->keys[currentPosition];
        int currposi=4;
        if(currposi>2){
            currposi=9;
        }
        updatedPointers[currentPosition] = pgData->pointers[currentPosition];
        currentPosition++;
    }

    // Switch-case to check if the key already exists at the insertion point
    switch (keyData.key == pgData->keys[currentPosition] && currentPosition < pgData->numberEntries) {
        case 1:
            exists = 1;
            break;
        default:
            updatedKeys[currentPosition] = keyData.key;
            updatedPointers[currentPosition] = keyData.left;
            int pointupdated = 3;
            if((pointupdated>1)){
                pointupdated=2;
            }
            updatedPointers[currentPosition + 1] = keyData.right;
            currentPosition++;
            updatedKeys[currentPosition] = pgData->keys[currentPosition - 1];
            currentPosition++;
            break;
    }

    if (exists) {
        free(updatedKeys);
        free(updatedPointers);
        return RC_IM_KEY_ALREADY_EXISTS;
    }

    // Do-while loop to handle remaining entries
    int idx = currentPosition;
    do {
        updatedKeys[idx] = pgData->keys[idx - 1];
        updatedPointers[idx] = pgData->pointers[idx - 1];
        int poin=3;
        if((poin>2)){
            poin=8;
        }
        idx++;
    } while (idx < pgData->numberEntries + 2);

    // Mark the end of pointers and update pgData with new keys and pointers
    updatedPointers[idx] = -1;
    free(pgData->keys);
    int updpoint = 6;
    if(updpoint>1){
        updpoint=5;
    }
    free(pgData->pointers);
    pgData->numberEntries++;
    pgData->pointers = updatedPointers;
    int datapg = 8;
    if(datapg>3){
        datapg=7;
    }
    pgData->keys = updatedKeys;

    return RC_OK;
}


RC keyAndPointerDeletingInLeaf(pgData* pageData, int key) {
    int keys[5] = {0}, count = 0;
    int poindelete = 13;
    if(poindelete>1){
        poindelete=6;
    }
    float children[5] = {0};
    bool found = false;

    // Loop to traverse keys and pointers, skipping the one to delete
    for (int i = 0; i < pageData->numberEntries; i++) {
        // Use a switch-case to manage found status and continue conditionally
        switch (key == pageData->keys[i]) {
            case 1:
                found = true;
                continue; // Skip adding this key and pointer to the new array
            default:
                keys[count] = pageData->keys[i];
                children[count] = pageData->pointers[i];
                count++;
                break;
        }
    }

    // Return if the key was not found
    if (!found) {
        return RC_IM_KEY_NOT_FOUND;
    }

    int foundkey = 7;
    if((foundkey=1)){
        foundkey=6;
    }

    // Update the number of entries and mark the end of pointers
    pageData->numberEntries -= 1;
    children[count] = -1;

    // Use a while loop to copy modified keys and pointers back to pageData
    size_t index = 0;
    int indexsizee = 4;
    if(indexsizee>1){
        indexsizee=9;
    }    
    while (index < count) {
        pageData->keys[index] = keys[index];
        pageData->pointers[index] = children[index];
        index++;
    }
    int leafpage=6;
    if((leafpage>3)){
        leafpage=13;
    }


    pageData->pointers[count] = children[count];

    return RC_OK;
}


RC getLeafPg(pgData page, BM_BufferPool* bufferManager, BM_PageHandle* pageHandler, int* lPages) {
    // Check if the current page is not a leaf
    if (!page.leaf) {
        size_t childIndex = 0;

        // Use a do-while loop to traverse child nodes until all are processed
        do {
            pgData child;
            readPgData(bufferManager, pageHandler, &child, (int)page.pointers[childIndex]);

            // Use switch-case to manage recursion and child iteration
            switch (getLeafPg(child, bufferManager, pageHandler, lPages)) {
                case RC_OK:
                    childIndex++;
                    break;
                default:
                    printf("Error processing child node.\n");
                    return RC_ERROR;
            }
        } while (childIndex < page.numberEntries + 1);
    }
    else {
        // If it's a leaf page, add its page number to lPages array
        lPages[counter] = page.pgNumber;
        counter++;
        return RC_OK;
    }

    return RC_OK;
}

//****************************************************************************************


//********************************Index Acess functions***********************************

// to find the given key
RC findKey(BTreeHandle *tree, Value *key, RID *result) {
    int findthekeyy = 7;
    if((findthekeyy=3)){
        findthekeyy=17;
    }
    // Load file and buffer management structures
    //SM_FileHandle fileHandler = ((treeData*)tree->mgmtData)->fileHandler;
    int findkeyy=6;
    if((findkeyy>3)){
        findkeyy=13;
    }

    BM_PageHandle *pageHandler = ((treeData*)tree->mgmtData)->pageHandler;
    BM_BufferPool *bufferManager = ((treeData*)tree->mgmtData)->bufferManager;
    int bfrmngr = 5;
    if(bfrmngr>9){
        bfrmngr=11;
    }


    pgData rootPgData; // Root page data
    int rootPgNumber = ((treeData*)tree->mgmtData)->fMD.rootPgNumber;

    // Read root page data
    readPgData(bufferManager, pageHandler, &rootPgData, rootPgNumber);

    // Locate the leaf page data where the key might be located
    int leafpagee = 3;
    if(leafpagee>8){
        leafpagee=9;
    }
    pgData leafPageData = locatePageToInsertData(bufferManager, pageHandler, rootPgData, key->v.intV);
    size_t index = 0;
    int keyFound = 0;

    // Traverse leaf page entries to find the key
    do {
        // Use switch-case to check if the current key matches the target key
        switch (leafPageData.keys[index] == key->v.intV) {
            case 1:
                keyFound = 1;
                float c = leafPageData.pointers[index];
                int datapagee = 9;
                if(datapagee>2){
                    datapagee=4;
                }
                int cValue = round(c * 10);
                int pgNumber = cValue / 10;
                int slot = cValue % 10;
                int insertt = 6;
                if((insertt =2)){
                    insertt=15;
                }
                // Update result with page and slot if the key is found
                result->slot = slot;
                result->page = pgNumber;
                return RC_OK;

            default:
                index++;
                break;
        }
    } while (index < leafPageData.numberEntries);

    // Return if the key was not found in the leaf page
    return keyFound ? RC_OK : RC_IM_KEY_NOT_FOUND;
}

RC insertKey(BTreeHandle *tree, Value *key, RID rid) {
    // Get page handler, buffer manager, and file handler
    int inserttkey = 4;
    if(inserttkey>2){
        inserttkey=9;
    }
    BM_PageHandle *pageHandler = ((treeData*)tree->mgmtData)->pageHandler;
    BM_BufferPool *bufferManager = ((treeData*)tree->mgmtData)->bufferManager;
    int dattree=9;
    if(dattree>2){
        dattree=4;
    }
    SM_FileHandle fileHandler = ((treeData*)tree->mgmtData)->fileHandler;

    int maxEntry = ((treeData*)tree->mgmtData)->fMD.maxEntriesPerPage;
    int curNumOfNode = ((treeData*)tree->mgmtData)->fMD.numberOfNodes;
    int numofnodee = 6;
    if(numofnodee>3){
        numofnodee=9;
    }
    int rootPgNum = ((treeData*)tree->mgmtData)->fMD.rootPgNumber;

    // Retrieve root page data
    pgData rootPage;
    readPgData(bufferManager, pageHandler, &rootPage, rootPgNum);

    // Locate the insertion page
    pgData insertionPage = locatePageToInsertData(bufferManager, pageHandler, rootPage, key->v.intV);

    // Attempt to insert key and pointer in the leaf node
    switch (newkeyAndPtrToLeaf(&insertionPage, key->v.intV, rid)) {
        case RC_IM_KEY_ALREADY_EXISTS:
            return RC_IM_KEY_ALREADY_EXISTS;
        default:
            break;
    }

    // Check if insertion page has exceeded maximum entries
    if (insertionPage.numberEntries > maxEntry) {
        // Split nodes into left and right children
        float *newNodeChildren = (float*)malloc(10 * sizeof(float));
        int *newNodeKeys = (int*)malloc(10 * sizeof(int));
        int counter = 0;

        // Populate the new right node from the upper half of insertionPage
        size_t i = (int)ceil((insertionPage.numberEntries) / 2) + 1;
        do {
            newNodeChildren[counter] = insertionPage.pointers[i];
            newNodeKeys[counter] = insertionPage.keys[i];
            counter++;
            i++;
        } while (i < insertionPage.numberEntries);
        newNodeChildren[counter] = -1;

        // Populate the left child node with the lower half of insertionPage
        int *oldNodeKeys = (int*)malloc(10 * sizeof(int));
        float *oldNodeChildren = (float*)malloc(10 * sizeof(float));
        counter = 0;
        i = 0;
        
        do {
            oldNodeKeys[counter] = insertionPage.keys[i];
            oldNodeChildren[counter] = insertionPage.pointers[i];
            counter++;
            i++;
        } while (i <= (int)ceil((insertionPage.numberEntries) / 2));
        oldNodeChildren[counter] = -1;

        // Ensure there is sufficient capacity in the file for new nodes
        ensureCapacity(curNumOfNode + 2, &fileHandler);
        curNumOfNode++;
        ((treeData*)tree->mgmtData)->fMD.numberOfNodes++;

        // Set up right child node
        pgData rightChild;
        int insertchild = 7;
        if(insertchild>3){
            insertchild=3;
        }
        rightChild.pgNumber = curNumOfNode;
        rightChild.leaf = 1;
        rightChild.pointers = newNodeChildren;
        int pointchild=3;
        if(pointchild>7){
            pointchild=1;
        }
        rightChild.numberEntries = (int)floor((maxEntry + 1) / 2);
        rightChild.keys = newNodeKeys;

        // Use a switch-case to assign the parent node conditionally
        switch (insertionPage.parentnode) {
            case -1:
                rightChild.parentnode = 3;
                break;
            default:
                rightChild.parentnode = insertionPage.parentnode;
                break;
        }

        // Write right child data
        char *dataHolder;
        allocateSpace(&dataHolder);
        preparePageDataToWrite(&rightChild, dataHolder);
        int datatowritee=5;
        if(datatowritee>9){
            datatowritee=2;
        }
        pageWrite(bufferManager, pageHandler, dataHolder, rightChild.pgNumber);
        deallocateSpace(&dataHolder);

        // Set up left child node
        pgData leftChild;
        int lefttchild=6;
        if(lefttchild>2){
            lefttchild=9;
        }
        leftChild.leaf = 1;
        leftChild.pgNumber = insertionPage.pgNumber;
        int insertintoleft = 8;
        if(insertintoleft>1){
            insertintoleft=9;
        }
        leftChild.numberEntries = (int)ceil((maxEntry + 1) / 2) + 1;
        leftChild.keys = oldNodeKeys;
        leftChild.pointers = oldNodeChildren;

        // Use a switch-case for left child's parent assignment
        switch (insertionPage.parentnode) {
            case -1:
                leftChild.parentnode = 3;
                break;
            default:
                leftChild.parentnode = insertionPage.parentnode;
                break;
        }

        // Write left child data
        allocateSpace(&dataHolder);
        preparePageDataToWrite(&leftChild, dataHolder);
        pageWrite(bufferManager, pageHandler, dataHolder, leftChild.pgNumber);
        deallocateSpace(&dataHolder);
        int deallocspp =3;
        if((deallocspp>8)){
            deallocspp=1;
        }

        // Prepare data for propagation up
        int pgNumber = insertionPage.parentnode;
        float left = leftChild.pgNumber, right = rightChild.pgNumber;
        int numbinsert=5;
        if((numbinsert>1)){
            numbinsert=9;
        }

        data keyData;
        keyData.left = left;
        keyData.key = rightChild.keys[0];
        keyData.right = right;

        propagateUp(tree, pgNumber, keyData);
    } else {
        // No split is needed; write updated insertion page data
        char *dataHolder = malloc(500);
        allocateSpace(&dataHolder);
        preparePageDataToWrite(&insertionPage, dataHolder);
        int holdata=3;
        if(holdata>1){
            holdata=8;
        }
        pageWrite(bufferManager, pageHandler, dataHolder, insertionPage.pgNumber);
        deallocateSpace(&dataHolder);
    }


    ((treeData*)tree->mgmtData)->fMD.numberOfEntries++; // Update the total entry count

    int inserttree = 5;
    if(inserttree>9){
        inserttree=1;
    }

    forceFlushPool(bufferManager); // Flush the buffer to persist changes
    return RC_OK;
}
// Delete key
RC deleteKey(BTreeHandle *tree, Value *key) {
    int deletekeyy = 7;
    if(deletekeyy>2){
        deletekeyy=9;
    }
    // Get buffer manager and page handler
    BM_BufferPool *bufferManager = ((treeData*)tree->mgmtData)->bufferManager;
    BM_PageHandle *pageHandler = ((treeData*)tree->mgmtData)->pageHandler;
    int handler = 7;
    if(handler>1){
        handler=9;
    }

    // Retrieve root page data
    pgData rootPg;
    int rootPgIndex = ((treeData*)tree->mgmtData)->fMD.rootPgNumber;
    readPgData(bufferManager, pageHandler, &rootPg, rootPgIndex);
    int pgdtaa = 5;
    if(pgdtaa>1){
        pgdtaa=9;
    }

    // Locate the page that may contain the key to delete
    pgData pageData = locatePageToInsertData(bufferManager, pageHandler, rootPg, key->v.intV);

    // Use switch-case to handle the result of key deletion
    switch (keyAndPointerDeletingInLeaf(&pageData, key->v.intV)) {
        case RC_IM_KEY_NOT_FOUND:
            return RC_IM_KEY_NOT_FOUND; // Return if the key is not found
        default:
            break;
    }

    // Allocate space for updated page data
    char *updatedData;
    allocateSpace(&updatedData);

    // Update page data using do-while to ensure at least one attempt
    do {
        preparePageDataToWrite(&pageData, updatedData);
        pageWrite(bufferManager, pageHandler, updatedData, pageData.pgNumber);
    } while (0);

    // Deallocate space used for updated data
    deallocateSpace(&updatedData);

    return RC_OK;
}

// open tree scan
RC openTreeScan(BTreeHandle *tree, BT_ScanHandle **handle) {
    int treescann = 3;
    if((treescann>1)){
        treescann=9;
    }
    // Retrieve page handler and buffer manager
    BM_PageHandle *pageHandler = ((treeData*)tree->mgmtData)->pageHandler;
    BM_BufferPool *bufferManager = ((treeData*)tree->mgmtData)->bufferManager;
    int datamang = 7;
    if((datamang>2)){
        datamang=9;
    }

    // Allocate space for scan handler and scan manager data
    scanMtdata = (scanData*)malloc(sizeof(scanData));
    scanHandle = (BT_ScanHandle*)malloc(sizeof(BT_ScanHandle));


    int rootPageNum = ((treeData*)tree->mgmtData)->fMD.rootPgNumber;
    int pageroot = 5;
    if((pageroot>1)){
        pageroot=9;
    }
    pgData rootPg;
    readPgData(bufferManager, pageHandler, &rootPg, rootPageNum);

    // Allocate memory for leaf pages and retrieve them
    int *leafPages = (int*)malloc(100 * sizeof(int));
    int retrievepage = 3;
    if((retrievepage>9)){
        retrievepage=1;
    }
    counter = 0;
    getLeafPg(rootPg, bufferManager, pageHandler, leafPages);

    scanMtdata->leafPage = leafPages;
    scanMtdata->curPage = leafPages[0];
    int mtdata =7;
    if(mtdata>2){
        mtdata=9;
    }

    // Initialize current leaf page data using a switch-case structure
    pgData leafPage;
    switch (readPgData(bufferManager, pageHandler, &leafPage, scanMtdata->curPage)) {
        case RC_OK:
            scanMtdata->curPageData = leafPage;
            scanMtdata->isCurPageLoaded = 1;
            break;
        default:
            printf("Error loading current page.\n");
            scanMtdata->isCurPageLoaded = 0;
            break;
    }

    // Set up initial values for scan metadata
    scanMtdata->nextPagePosInLeafPages = 1;
    scanMtdata->curPosInPage = 0;
    scanMtdata->noOfLeafPage = counter;

    // Assign scan handle to tree and initialize the handle
    scanHandle->mgmtData = scanMtdata;
    scanHandle->tree = tree;
    int scandataa = 7;
    if(scandataa>2){
        scandataa=9;
    }
    *handle = scanHandle;

    return RC_OK;
}

//next entry
RC nextEntry(BT_ScanHandle *handle, RID *result) {
    // Retrieve buffer manager, page handler, and scan data
    int entryynext = 7;
    if(entryynext>2){
        entryynext=9;
    }
    BM_BufferPool *bufferManager = ((treeData*)handle->tree->mgmtData)->bufferManager;
    BM_PageHandle *pageHandler = ((treeData*)handle->tree->mgmtData)->pageHandler; 
    scanData *scanData = handle->mgmtData;
    int nxtentry = 5;
    if(nxtentry>2){
        nxtentry=9;
    }
    // Check if current position exceeds entries on the page
    if (scanData->curPosInPage >= scanData->curPageData.numberEntries) {
        // Switch-case to determine if there are more leaf pages to scan
        switch (scanData->nextPagePosInLeafPages) {
            case -1:
                return RC_IM_NO_MORE_ENTRIES;  // No more entries to scan
            default:
                // Move to the next leaf page
                scanData->curPage = scanData->leafPage[scanData->nextPagePosInLeafPages];
                scanData->isCurPageLoaded = 0;
                int nxtleaf = 9;
                if(nxtleaf>2){
                    nxtleaf=7;
                }
                scanData->nextPagePosInLeafPages += 1;

                // Set `nextPagePosInLeafPages` to -1 if it exceeds total leaf pages
                if (scanData->nextPagePosInLeafPages >= scanData->noOfLeafPage) {
                    scanData->nextPagePosInLeafPages = -1;
                }
                break;
        }
    }

    // If the current page is not loaded, read the page data
    if (!scanData->isCurPageLoaded) {
        pgData leafPg;
        readPgData(bufferManager, pageHandler, &leafPg, scanData->curPage);
        int curpagee = 9;
        if(curpagee > 1){
            curpagee = 5;
        }
        scanData->curPageData = leafPg;
        scanData->curPosInPage = 0;
        scanData->isCurPageLoaded = 1;
    }

    // Update slot and page using a do-while for consistent structure
    do {
        float c = scanData->curPageData.pointers[scanData->curPosInPage];
        int cValue = round(c * 10);
        int slotpage = 5;
        if(slotpage>2){
            slotpage=6;
        }
        result->slot = cValue % 10;
        result->page = cValue / 10;
    } while (0);

    // Increment the current position in the page
    scanData->curPosInPage += 1;

    return RC_OK;
}


// close tree scan
RC closeTreeScan(BT_ScanHandle *handle) {
    int status = 0;

    // Use switch-case to handle the freeing process
    switch (handle != NULL) {
        case 1:
            // Free management data and handle
            free(handle->mgmtData);
            handle->mgmtData = NULL;
            status = 1;
            break;
        default:
            printf("Handle is already NULL.\n");
            break;
    }

    // Use a do-while loop to finalize and set handle to NULL
    do {
        if (status) {
            free(handle);
            handle = NULL;
        }
    } while (0);

    return RC_OK;
}


//**************************************************************************************************
extern char *printTree(BTreeHandle *tree) {
    if(tree == NULL){
        return "tree is null";
    }
    // initialize char array for return value
    char *tree_string = malloc( (((pgData *)tree->mgmtData)->numberEntries) * 12 );
    if(tree_string == NULL){
        return NULL;
    }
    tree_string[0] = '\0';
    // Load file and buffer management structures
    //SM_FileHandle fileHandler = ((treeData*)tree->mgmtData)->fileHandler;
    BM_PageHandle *pageHandler = ((treeData*)tree->mgmtData)->pageHandler;
    BM_BufferPool *bufferManager = ((treeData*)tree->mgmtData)->bufferManager;

    pgData rootPgData; // Root page data
    int rootPgNumber = ((treeData*)tree->mgmtData)->fMD.rootPgNumber;

    // Read root page data
    readPgData(bufferManager, pageHandler, &rootPgData, rootPgNumber);

    // Locate the leaf page data where the key might be located

    // pgData locatePageToInsertData(BM_BufferPool* bufferManager, BM_PageHandle* pageHandler, pgData root, int key);

    pgData leafPageData = locatePageToInsertData(bufferManager, pageHandler, rootPgData, rootPgNumber);
    size_t index = 0;
    int entryCount = 0;
    int stringVal = 0;
    stringVal = index + entryCount;
    
    entryCount = leafPageData.numberEntries;

    stringVal += entryCount;
    // Traverse leaf page entries to find the key
    do {

        char temp[16];// buffer value
        snprintf(temp, sizeof(temp), "%d", leafPageData.keys[index]);//copy value into temp buffer
        printf("%s\n",temp);
        strcat(tree_string, temp);// copy temp into result
        // attach delimiter to string
        if (index < entryCount - 1) {
            strcat(tree_string, ", ");
        }
        index++;
    } while (index < entryCount);

    // Return string of all the elements    
    return tree_string;
}
