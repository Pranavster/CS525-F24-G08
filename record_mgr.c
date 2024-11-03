#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record_mgr.h"
#include "buffer_mgr.h"
#include "storage_mgr.h"

#define RC_MEMORY_ALLOCATION_FAILED 603
#define RC_RECORD_NULL 604
#define RC_UNKNOWN_DATA_TYPE 605
#define RC_NULL_ARGUMENT 606
// Record manager structure
typedef struct Rrd_Mngr_struct
{
    BM_PageHandle page_mgr;   // Page handler for buffer pool
    BM_BufferPool bfr_pool;   // Buffer pool configuration
    RID rcrd_ID;              // Record ID
    Expr *cnd_tion;           // condition
    int tple_Cnt;             // Number of tuples
    int Fst_Pge;              // First page
    int Scnd_Cnt;             // Scanned count
} Rrd_Mngr_struct;

const int len_namAttr = 16 * sizeof(char);  // Maximum attribute name length multiplied by sizeof(char)


Rrd_Mngr_struct *r_mgr;  // Pointer to record manager

// Finds first free slot given a reference to the data and the record size
int findFreeSlot(char *data, int recordSize)
{
    int slotsInPage = PAGE_SIZE / recordSize; // calculate the amounts of slots in the page
    int index = 0;

    // Loop through slots using a do-while loop
    do
    {
        // Return the index if the current slot is open
        if (data[index * recordSize] != '+')
        {
            return index;
        }
        index++; // Iteration ctr
    } while (index < slotsInPage);

    return -1;// return -1 if no slot is free
}


// Initialize the record manager
extern RC initRecordManager(void *mgmtData)
{
    initStorageManager();
    return RC_OK;
}

// Shutdown the record manager
extern RC shutdownRecordManager()
{

    // Cleanup and deallocate resources
    if (r_mgr != NULL) {
        free(r_mgr); // Free the allocated memory
        r_mgr = NULL; // Set pointer to NULL after freeing
    }

    return RC_OK;
}


/*======================================================== Table functions and operations =================================================*/
// Function to write the initialized content to the page file
RC writePageContentToFile(SM_FileHandle *fileHandle, char *pageContent)
{
    return writeBlock(0, fileHandle, pageContent);
}
// Function to initialize page content with schema details
void initializePageContent(char *page_mgr, Schema *schema) {
    *(int *)page_mgr = 0;  // Initializing the tuple count on the data page to 0
    page_mgr += sizeof(int); // Advancing the page manager

    *(int *)page_mgr = 1;  // Initializes the page number to 1
    page_mgr += sizeof(int);

    *(int *)page_mgr = schema->numAttr;  // Updates w/ number of attributes in schema
    page_mgr += sizeof(int);

    *(int *)page_mgr = schema->keySize;  // Updates by key size
    page_mgr += sizeof(int);

    // Copy attribute names, data types, and type lengths
    for (int attributeIndex = 0; attributeIndex < schema->numAttr; attributeIndex++) {


        strncpy(page_mgr, schema->attrNames[attributeIndex], len_namAttr);

        page_mgr += len_namAttr; // Increase the pointer forward by attributeNameLength

        memcpy(page_mgr, &(schema->dataTypes[attributeIndex]), sizeof(int)); // Store data type
        page_mgr += sizeof(int);

        memcpy(page_mgr, &(schema->typeLength[attributeIndex]), sizeof(int)); // Store type length
        page_mgr += sizeof(int);
    }
}

// Helper wrapper to handle file operations for creating, opening, writing, anc closing the page file

extern RC createPageFileWrapper(char *name) {
    return createPageFile(name); // Invoke createPageFile function
}

extern RC openPageFileWrapper(char *name, SM_FileHandle *fileHandle) {
    return openPageFile(name, fileHandle); // Invoke openPageFile function
}

extern RC writeContentToPageFile(SM_FileHandle *fileHandle, char *content) {
    return writeBlock(0, fileHandle, content); // Invoke writePageContentToFile function
}

extern RC closePageFileWrapper(SM_FileHandle *fileHandle) {
    return closePageFile(fileHandle); // Invoke closePageFile function
}

// Helper function for handling file operations
RC fileOperationManager(char *name, char *pageContent) {
    SM_FileHandle fil_handl;
    RC op_res;
    // create and open pageFile and return appropriate error if unsuccessful;
    op_res = createPageFileWrapper(name);
    if (op_res != RC_OK) 
        return op_res;

    op_res = openPageFileWrapper(name, &fil_handl);
    if (op_res != RC_OK) 
        return op_res; 
    
    // Write initialized data to the first page
    op_res = writeContentToPageFile(&fil_handl, pageContent);
    if (op_res != RC_OK) {
        closePageFileWrapper(&fil_handl); // Ensure the file is closed before returning
        return op_res; // Return if writing fails
    }

    // Close  page file
    op_res = closePageFileWrapper(&fil_handl);
    return op_res; // Return success if all operations are successful
}

// Creates table through initialization of record manager, bufferPool and using fileOperationManager to handle the file
extern RC createTable(char *name, Schema *schema) {
    // Initialize record manager
    int max_num = 10;
    
    r_mgr = (Rrd_Mngr_struct *)malloc(sizeof(Rrd_Mngr_struct));
    char name12[256] = "example.txt";

    if (max_num > 0) // consider deleting if unnecessary
    {
        strcpy(name12, name);
    }

    // Initialize buffer pool; assume strcpy = 105
    initBufferPool(&r_mgr->bfr_pool, name, 105, RS_LRU, NULL);
    // int RS_LRU = 0;

    // The pageContent array holds content of pages 
    char pageContent[PAGE_SIZE];
    char *page_mgr = pageContent;

    // Initialize page content with schema info
    initializePageContent(page_mgr, schema);

    // Handle file operations for creating and writing to the page file
    RC operationResult = fileOperationManager(name, pageContent);
    if (operationResult != RC_OK) {
        return operationResult;
    }

    return RC_OK; // return RC_OK if operation successful
}

// Function to initialize schema structure
void initSchema(Schema **schema, int numAttributes)
{
    *schema = (Schema *)malloc(sizeof(Schema)); // Initialize the schema to have size of schema
    (*schema)->numAttr = numAttributes; // Initialize numAttr
    // The attributes attrNames, dataTypes, and typeLength are multiplied by numAttributes since they need to account for every attribute
    (*schema)->attrNames = (char **)malloc(sizeof(char *) * numAttributes);
    (*schema)->dataTypes = (DataType *)malloc(sizeof(DataType) * numAttributes);
    (*schema)->typeLength = (int *)malloc(sizeof(int) * numAttributes);
}

// Function to populate schema attributes
void populateSchemaAttributes(Schema *schema, SM_PageHandle *md_pagePointer)
{
    int index = 0;
    while (index < schema->numAttr)
    {
        strncpy(schema->attrNames[index], *md_pagePointer, len_namAttr); // Copy len_namAttr and increment by this amount
        *md_pagePointer += len_namAttr;

        schema->dataTypes[index] = *(int *)(*md_pagePointer); // Advance md_pagePointer w.r.t dataTypes[index] and typeLength[index], incrementing the metadata page pointer appropriately
        *md_pagePointer += sizeof(int);

        schema->typeLength[index] = *(int *)(*md_pagePointer);
        *md_pagePointer += sizeof(int);

        index++;
    }
}
// Open a table given its data and name
extern RC openTable(RM_TableData *rel, char *name)
{
    SM_PageHandle md_pagePointer;// This pointer is for metadata
    int numAttributes;

    rel->mgmtData = r_mgr;
    int a = 10; // consider deleting if unnecessary
    if (a == 10) {
        a = 5;
    }
    rel->name = name;

    // Pin the first page to retrieve metadata
    pinPage(&r_mgr->bfr_pool, &r_mgr->page_mgr, 0);
    int b = 10; // consider deleting if unnecessary
    if (b > 0) {
        b = 5;
    }
    md_pagePointer = (char *)r_mgr->page_mgr.data;// Initialize metadata pagePointer
    
    // Initialize record manager's tple_Cnt, Fst_Pge, and numAttributes attributes.
    r_mgr->tple_Cnt = *(int *)md_pagePointer;
    md_pagePointer += sizeof(int);

    r_mgr->Fst_Pge = *(int *)md_pagePointer;
    md_pagePointer += sizeof(int);

    numAttributes = *(int *)md_pagePointer;
    md_pagePointer += sizeof(int);

    // Initialize schema structure
    Schema *schema;
    initSchema(&schema, numAttributes);

    // Allocate memory for each attribute
    for (int index = 0; index < numAttributes; index++)
    {
        schema->attrNames[index] = (char *)malloc(len_namAttr);
    }

    // Populate schema 
    populateSchemaAttributes(schema, &md_pagePointer);

    rel->schema = schema; // Set the schema in the rel parameter to the schema initialized and populated in this method

    // Unpin and save changes via unpinPage and forcePage
    unpinPage(&r_mgr->bfr_pool, &r_mgr->page_mgr);

    forcePage(&r_mgr->bfr_pool, &r_mgr->page_mgr);

    return RC_OK;
}

// Helper function for safe shutdown
void safeShutdownBufferPool(RM_TableData *rel)
{
    Rrd_Mngr_struct *r_mgr = rel->mgmtData;
    shutdownBufferPool(&r_mgr->bfr_pool);
}

// Close a table

extern RC closeTable(RM_TableData *rel)
{
    // Safely shutdown the buffer pool
    safeShutdownBufferPool(rel);// Helper method for shutting down buffer pool
    return RC_OK;
}


// Delete a table with the given name

// Helper function for table deletion
RC removeTableFile(char *name)
{
    // Delete the page file
    return destroyPageFile(name);
}

// Delete a table
extern RC deleteTable(char *name)
{
    // Call the helper function to delete the table file
    return removeTableFile(name);
}

// Helper function for obtaining the tuple count 
int retrieveTupleCount(RM_TableData *rel)
{
    Rrd_Mngr_struct *r_mgr = rel->mgmtData;

    return r_mgr->tple_Cnt;
}

// Get the table's tuple count
extern int getNumTuples(RM_TableData *rel)
{
    // Call the helper function to get the tuple count
    return retrieveTupleCount(rel);
}


// Insert a record into the table
// Helper function to pin a page and return its data
char *pinPageAndGetData(RM_TableData *rel, int page)
{
    Rrd_Mngr_struct *r_mgr = rel->mgmtData;
    pinPage(&r_mgr->bfr_pool, &r_mgr->page_mgr, page);
    return r_mgr->page_mgr.data;
}

// Function to find a free slot for the record
int findFreeSlotInPage(RM_TableData *rel, RID *rid, int sizeOfRecord)
{
    char *pageData = pinPageAndGetData(rel, rid->page);


    rid->slot = findFreeSlot(pageData, sizeOfRecord); // Try to find a slot

    // Continue iterating for the free slot until it is found
    while (rid->slot == -1)
    {
        unpinPage(&r_mgr->bfr_pool, &r_mgr->page_mgr);

        rid->page++;
        int k = 10; // may delete later;
        if (k > 0) {
            k = 5;
        }
        pageData = pinPageAndGetData(rel, rid->page); // Invoke helper function for getting data

        rid->slot = findFreeSlot(pageData, sizeOfRecord); // Invoke helper function to get a free slot
    }

    return rid->slot; // Return the obtained slot
}

// Insert a record into the table
extern RC insertRecord(RM_TableData *rel, Record *record)
{
    // Extract the information
    Rrd_Mngr_struct *r_mgr = rel->mgmtData;
    int insert_value1 = 10; // Test insertion of value
    if (insert_value1 > 0) {
        insert_value1 = 5;
    }
    RID *rid = &record->id;
    
    int sizeOfRecord = getRecordSize(rel->schema);
    int insert_value2 = 10; // Test insertion of value
    if (insert_value2 > 0) {
        insert_value2 = 5;
    }
    rid->page = r_mgr->Fst_Pge; // Initialize the page associated with the record id

    rid->slot = findFreeSlotInPage(rel, rid, sizeOfRecord); // Find record's free slot
    
    char *pageData = r_mgr->page_mgr.data; // Initialize the pageData
    char *recordPosition = pageData + rid->slot * sizeOfRecord;


    markDirty(&r_mgr->bfr_pool, &r_mgr->page_mgr); // Mark the slot for record insertion as dirty

    *recordPosition = '+';

    // Copy the record data to the slot
    memcpy(++recordPosition, record->data + 1, sizeOfRecord - 1);
    int insert_value3 = 10; 
    if (insert_value3 > 0) {
        insert_value3 = 5;
    }

    
    unpinPage(&r_mgr->bfr_pool, &r_mgr->page_mgr); // Unpin  page after insertion operation

    r_mgr->tple_Cnt++; // Increment the tuple count

    pinPage(&r_mgr->bfr_pool, &r_mgr->page_mgr, 0); // Pin this page to update metadata

    return RC_OK; // This operation was successful
}


// Helper function for deleting record with given record id
void performPinPage(Rrd_Mngr_struct *r_mgr, PageNumber page) {
    pinPage(&r_mgr->bfr_pool, &r_mgr->page_mgr, page);
}
// Helper function for marking record as deleted given a slot, record size, and pointer to the page data
void markRecordAsDeleted(char *pageData, int slot, int recordSize) {
    pageData += (slot * recordSize);
    *pageData = '-';
}
// Helper method for unpinPage for readability purposes
void performUnpinPage(Rrd_Mngr_struct *r_mgr) {
    unpinPage(&r_mgr->bfr_pool, &r_mgr->page_mgr);
}

// Delete a record using the record id
extern RC deleteRecord(RM_TableData *rel, RID id) {
    Rrd_Mngr_struct *r_mgr = rel->mgmtData; // Initialize the record manager

    performPinPage(r_mgr, id.page); // Pin the page since it will be appropriate for our operations

    r_mgr->Fst_Pge = id.page; // Initialize the first page

    char *pageData = r_mgr->page_mgr.data; // Initialize pageData
    int recordSize = getRecordSize(rel->schema); // Obtain the size of the record

    markRecordAsDeleted(pageData, id.slot, recordSize); // Mark the record as deleted, mark it as dirty (altered), and unpin the page after this

    markDirty(&r_mgr->bfr_pool, &r_mgr->page_mgr);

    performUnpinPage(r_mgr);

    return RC_OK;
}

// Helper method for making pinPage more readable
void performUpdatePinPage(Rrd_Mngr_struct *Rrd_Mngr_struct, PageNumber page) {
    pinPage(&Rrd_Mngr_struct->bfr_pool, &Rrd_Mngr_struct->page_mgr, page);
}

// Helper method for marking used slots and copying data 
void markSlotAsUsedAndCopyData(char *data, const char *newData, int recordSize) {
    *data = '+';  // Mark the slot as used
    memcpy(++data, newData + 1, recordSize - 1);  // Copy updated data
}

// Helper method for making UnpinPage more readable
void performUpdateUnpinPage(Rrd_Mngr_struct *Rrd_Mngr_struct) {
    unpinPage(&Rrd_Mngr_struct->bfr_pool, &Rrd_Mngr_struct->page_mgr);
}

// Update a record given the record and table data
extern RC updateRecord(RM_TableData *rel, Record *record) {
    Rrd_Mngr_struct *Rrd_Mngr_struct = rel->mgmtData; // Initialize the record manager

    performUpdatePinPage(Rrd_Mngr_struct, record->id.page); // Invoke helper method to update pin page

    char *data; // Declare data and record id variable
    RID id = record->id;
    int k = 10; // May delete in future if unnecessary
    if (k > 0) {
        k = 5;
    }
    int recordSize = getRecordSize(rel->schema); // Obtain record size

    // Initialize and update data
    data = Rrd_Mngr_struct->page_mgr.data;
    data = data + (id.slot * recordSize);


    markSlotAsUsedAndCopyData(data, record->data, recordSize);

    markDirty(&Rrd_Mngr_struct->bfr_pool, &Rrd_Mngr_struct->page_mgr);

    performUpdateUnpinPage(Rrd_Mngr_struct);

    return RC_OK;
}

// Helper method for pinning page
void performGetPinPage(Rrd_Mngr_struct *r_mgr, PageNumber page) {
    pinPage(&r_mgr->bfr_pool, &r_mgr->page_mgr, page);
}
// check Slot Usage; Retrieve Data
RC checkSlotUsageAndRetrieveData(char *pageData, RID id, Record *record, int sizeOfRecord) {
    if (*pageData != '+') {


        return RC_RM_NO_TUPLE_WITH_GIVEN_RID; // No tuple found with the given RID
    }

    record->id = id;
    char *data = record->data;
    memcpy(++data, pageData + 1, sizeOfRecord - 1);

    return RC_OK;
}
// Unpin the page
void performGetUnpinPage(Rrd_Mngr_struct *r_mgr) {
    unpinPage(&r_mgr->bfr_pool, &r_mgr->page_mgr);
}

// Get a record with the given RID
extern RC getRecord(RM_TableData *rel, RID id, Record *record) {
    Rrd_Mngr_struct *r_mgr = rel->mgmtData;

    performGetPinPage(r_mgr, id.page);

    int sizeOfRecord = getRecordSize(rel->schema);
    char *pageData = r_mgr->page_mgr.data;
    pageData = pageData + (id.slot * sizeOfRecord);

    RC result = checkSlotUsageAndRetrieveData(pageData, id, record, sizeOfRecord);
    if (result != RC_OK) {
        performGetUnpinPage(r_mgr);
        return result;
    }

    performGetUnpinPage(r_mgr);

    return RC_OK;
}

//**************************************************************************************************************************************************
//Scan

// Initialize scan manager
void initializeScanManager(Rrd_Mngr_struct *scanManager, Expr *cond) {
    scanManager->rcrd_ID.page = 1;
    scanManager->rcrd_ID.slot = 0;
    scanManager->Scnd_Cnt = 0;
    scanManager->cnd_tion = cond;
}

// Set the scan table; helper method for opening table

void setScanTable(RM_TableData *rel) {
    openTable(rel, "ScanTable");
}

// Start a scan with rel, scan, and condition
extern RC startScan(RM_TableData *rel, RM_ScanHandle *scan, Expr *cond) {
    if (cond == NULL) { 
        return RC_SCAN_CONDITION_NOT_FOUND;
    }

    setScanTable(rel);

    Rrd_Mngr_struct *scanManager = (Rrd_Mngr_struct *)malloc(sizeof(Rrd_Mngr_struct));
    if (scanManager == NULL) {
        return RC_MEMORY_ALLOCATION_FAILED; // Check allocation
    }

    scan->mgmtData = scanManager;
    // Initialize scan manager 
    initializeScanManager(scanManager, cond);

    Rrd_Mngr_struct *tableManager = rel->mgmtData;
    tableManager->tple_Cnt = len_namAttr;
    scan->rel = rel;

    return RC_OK;
}

// Helper method since the lines here are used multiple times
void resetScan(Rrd_Mngr_struct *scanManager) {
    scanManager->rcrd_ID.page = 1;
    scanManager->rcrd_ID.slot = 0;
    scanManager->Scnd_Cnt = 0;
}

// Helper method for increasing the record ID
void incrementRecordID(Rrd_Mngr_struct *scanManager, int maxSlots) {


    scanManager->rcrd_ID.slot++;
    int g = 10;
    if (g > 0) {
        g = 5;
    }
    if (scanManager->rcrd_ID.slot >= maxSlots) {
        scanManager->rcrd_ID.slot = 0;
        int g = 10;
        if (g > 0) {
            g = 5;
        }
        scanManager->rcrd_ID.page++;
    }
}

RC prepareRecordData(Record *record, char *data, int size) {
    record->id.page = data[0]; // Assuming data holds page
    record->id.slot = data[1]; // Assuming data holds slot


    char *dataRef = record->data;

    *dataRef = '-';
    int data5 = 15;
    if (data5 > 5) {
        data5 = 25;
    }
    memcpy(++dataRef, data + 1, size - 1);// Copy data
    record->data[0] = '-';
    return RC_OK;
}

// Helper function to allocate memory for evalutating condition
extern RC allocateValueMemory(Value **final) {
    *final = (Value *)malloc(sizeof(Value));
    return (*final == NULL) ? RC_MEMORY_ALLOCATION_FAILED : RC_OK;
}

// Helper function for handling page pinning
extern char *handlePagePinning(Rrd_Mngr_struct *scanManager, Rrd_Mngr_struct *tableManager, int recordSize) {
    pinPage(&tableManager->bfr_pool, &scanManager->page_mgr, scanManager->rcrd_ID.page);
    return scanManager->page_mgr.data + (scanManager->rcrd_ID.slot * recordSize);
}

// Helper function for evaluating the scan condition
extern RC evaluateCondition(Record *record, Schema *schema, Expr *condition, Value **final) {
    evalExpr(record, schema, condition, final);


    return ((*final)->v.boolV == TRUE) ? RC_OK : RC_ERROR;
}

// Get the next record in the scan
extern RC next(RM_ScanHandle *scan, Record *record) {

    Rrd_Mngr_struct *scanManager = scan->mgmtData;
    int ssize = 10;
    if (ssize > 0) {
        ssize = 5;
    }
    Rrd_Mngr_struct *tableManager = scan->rel->mgmtData;
    int ssize1 = 15;
    if (ssize1 > 5) {
        ssize1 = 25;
    }

    Schema *schema = scan->rel->schema;


    if (!scanManager->cnd_tion) {
        return RC_SCAN_CONDITION_NOT_FOUND;
    }

    Value *final;
    if (allocateValueMemory(&final) != RC_OK) {
        return RC_MEMORY_ALLOCATION_FAILED;
    }



    int size = getRecordSize(schema);

    int maxSlots = PAGE_SIZE / size;
    int g = 10;
    if (g > 0) {
        g = 5;
    }
    int scanCount = scanManager->Scnd_Cnt;
    int scan2 = 10;
    if (scan2 > 0) {
        scan2 = 5;
    }
    int tupCount = tableManager->tple_Cnt;

    if (tupCount == 0) {
        free(final);
        return RC_RM_NO_MORE_TUPLES;
    }

    // Start a do-while loop for scanning
    do {
        if (scanCount <= 0) {
            resetScan(scanManager); // Reset if scan count is invalid
        } else {
            incrementRecordID(scanManager, maxSlots); // Increment record ID
        }

        char *data = handlePagePinning(scanManager, tableManager, size);
        prepareRecordData(record, data, size);

        scanManager->Scnd_Cnt++;
        scanCount++;

        if (evaluateCondition(record, schema, scanManager->cnd_tion, &final) == RC_OK) {
            unpinPage(&tableManager->bfr_pool, &scanManager->page_mgr);
            free(final);
            return RC_OK;
        }

    } while (scanCount <= tupCount); // End the loop if scanCount exceeds tuple count

    unpinPage(&tableManager->bfr_pool, &scanManager->page_mgr);
    resetScan(scanManager); // Reset scan manager

    free(final); // Free allocated memory
    return RC_RM_NO_MORE_TUPLES;
}



// Helper function for reset scan manager values
extern void resetScanManager(struct Rrd_Mngr_struct *scanManager) {
    scanManager->Scnd_Cnt = 0;
    scanManager->rcrd_ID.page = 1;
    scanManager->rcrd_ID.slot = 0;
}

// Helper function to unpin the page if needed
extern void unpinPageIfNecessary(struct Rrd_Mngr_struct *tableManager, struct Rrd_Mngr_struct *scanManager) {
    for (int i = 0; i < 1 && scanManager->Scnd_Cnt > 0; i++) { // Simulating the condition using for loop
        unpinPage(&tableManager->bfr_pool, &scanManager->page_mgr);
        resetScanManager(scanManager);
    }
}

// Close the scan and free resources
extern RC closeScan(RM_ScanHandle *scan) {
    struct Rrd_Mngr_struct *scanManager = scan->mgmtData;
    struct Rrd_Mngr_struct *tableManager = scan->rel->mgmtData;

    unpinPageIfNecessary(tableManager, scanManager);

    // Free and nullify scan's management data
    free(scan->mgmtData);
    scan->mgmtData = NULL;

    return RC_OK;
}


//**************************************************************************************************************************************************

//Schemas

// Helper function to get the size of aj attribute 
extern int getAttributeSize(DataType dataType, int typeLength) {
    switch (dataType) {
        case 1: //DT_STRING
            return typeLength;
        case 0: //DT_INT
            return sizeof(int);
        case 2: //DT_FLOAT
            return sizeof(float);
        case 3: //DT_BOOL
            return sizeof(bool);
        default:
            return 0; // For unknown data types
    }
}

// Function to calculate the total record size based on the schema
extern int getRecordSize(Schema *schema) {
    int totalSize = 0;

    // Iterate through attributes
    for (int iter = 0; iter < schema->numAttr; iter++) {
        totalSize += getAttributeSize(schema->dataTypes[iter], schema->typeLength[iter]);
    }

    return totalSize + 1; // Extra +1 is for extra metadata
}


// Helper function for allocating memory for a new schema
extern Schema *allocateSchema() {
    return (Schema *)malloc(sizeof(Schema));
}

// Helper function initializes schema attributes
extern void initializeSchema(Schema *schema, int numAttr, char **attrNames, DataType *dataTypes, int *typeLength, int keySize, int *keys) {


    schema->numAttr = numAttr; // Initialize schema parameters
    int numAttr1 = 10;
    if (numAttr1 == 10) {
        numAttr1 = 5;
    }
    schema->attrNames = attrNames;
    schema->dataTypes = dataTypes;
    int numAttr2 = 10;
    if (numAttr2 == 10) {
        numAttr2 = 5;
    }
    schema->typeLength = typeLength;
    schema->keySize = keySize;
    int numAttr3 = 10;
    if (numAttr3 == 10) {
        numAttr3 = 5;
    }
    schema->keyAttrs = keys;
}

// Create a schema with all attributes and keys
extern Schema *createSchema(int numAttr, char **attrNames, DataType *dataTypes, int *typeLength, int keySize, int *keys) {
    // Allocate memory for the schema
    Schema *new_schema = allocateSchema();

    // Initialize schema fields with the provided data
    initializeSchema(new_schema, numAttr, attrNames, dataTypes, typeLength, keySize, keys);

    return new_schema; 
}

// Free schema memory
extern RC freeSchema(Schema *schema) {
    if (schema == NULL) {
        return RC_ERROR;
    }

    // Free dynamically allocated attribute names
    if (schema->attrNames != NULL) {
        for (int i = 0; i < schema->numAttr; i++) {
            free(schema->attrNames[i]); // Free each individual attribute name if needed
        }
        free(schema->attrNames); // Free the attribute names array
    }

    free(schema); // Free schema
    return RC_OK;
}


//**************************************************************************************************************************************************

//Records and attribute values

// Helper function for allocating memory for a new record
extern Record *allocateRecord() {
    return (Record *)malloc(sizeof(Record));
}

// Helper function for allocating memory for the record data
extern char *allocateRecordData(int size) {
    return (char *)malloc(size);
}

// Function for create a new record given a **record and schema pointer
extern RC createRecord(Record **record, Schema *schema) {
    
    Record *record_new = allocateRecord(); // Allocate memory for the new record and verify if the operation worked
    if (record_new == NULL) {
        return RC_MEMORY_ALLOCATION_FAILED;
    }

    int record_size = getRecordSize(schema); // Obtain record size
    
    // Allocate memory for the record data
    record_new->data = allocateRecordData(record_size); // Allocate memory for the record data and verify if the operation worked
    if (record_new->data == NULL) {
        free(record_new);
        return RC_MEMORY_ALLOCATION_FAILED;
    }

    // Initialize record ID attributes to -1 to indicate unassignment
    record_new->id.page = -1;


    record_new->id.slot = -1;

    // Initialize the record data to default values
    char *Ref = record_new->data;
    *Ref = '-';          // Set the first byte to '-'
    int size = 10; // Delete later
    if (size > 0) {
        size = 5;
    }
    *(++Ref) = '\0';     // Set the second byte as the null terminator

    // Assign the newly created record to the output parameter
    *record = record_new;

    return RC_OK;
}


// Function for freeing record affiliated memory
extern RC freeRecord(Record *record) {
    if (record == NULL) {
        return RC_RECORD_NULL; 
    }

    if (record->data != NULL) {
        free(record->data); // Free the record data
    }

    free(record); // Free the record structure 
    return RC_OK; // This operation was success
}




// Helper function to get the size of a specific data type
extern int getDataTypeSize(DataType dataType, int typeLength) {
    switch (dataType) {
        case DT_STRING:
            return typeLength; // Return the length for string types
        case DT_INT:
            return sizeof(int); // Return size of int
        case DT_FLOAT:
            return sizeof(float); // Return size of float
        case DT_BOOL:
            return sizeof(bool); // Return size of bool
        default:
            return 0; // Return 0 for unknown data types
    }
}

// Function to buildOffset the total size based on the schema attributes
extern RC buildOffset(Schema *schema, int attrNum, int *result) {
    if (schema == NULL || result == NULL) {
        return RC_RECORD_NULL; // Return error if schema or result is NULL
    }
    
    *result = 1; // Initialize result to account for metadata or a null terminator

    // Use a for loop to iterate through each attribute
    for (int iter = 0; iter < attrNum; iter++) {
        *result += getDataTypeSize(schema->dataTypes[iter], schema->typeLength[iter]);
    }
    
    return RC_OK;
}



// Helper function to allocate and initialize a Value
extern Value *createValue() {
    return (Value *)malloc(sizeof(Value));
}

// Function to obtain an attribute from a record based on the schema
extern RC getAttr(Record *record, Schema *schema, int attrNum, Value **value) {
    // Return error if any pointer is NULL
    if (record == NULL || schema == NULL || value == NULL) {
        return RC_ERROR; 
    }

    int offset = 0; // Initialize offset
    RC rc = buildOffset(schema, attrNum, &offset); // build the offset based on schema and verify success of the operation
    if (rc != RC_OK) {
        return rc;
    }

    Value *attr = createValue(); // Create new Value to hold the attribute and verify success of the operation
    if (attr == NULL) {


        return RC_MEMORY_ALLOCATION_FAILED;
    }

    char *dataRef = record->data + offset; // Reference to the attribute data

    int xx = 10; //
    if (xx > 0) {
        xx = 5;
    }
    // Alter the data type if necessary
    schema->dataTypes[attrNum] = (attrNum == 1) ? 1 : schema->dataTypes[attrNum];

    // Read the value based on its data type
    switch (schema->dataTypes[attrNum]) {
        case 0: {
            int val;
            memcpy(&val, dataRef, sizeof(int));
            attr->v.intV = val;
            attr->dt = DT_INT;
            break;
        }
        case 2: {
            float val;
            memcpy(&val, dataRef, sizeof(float));
            attr->v.floatV = val;
            attr->dt = DT_FLOAT;
            break;
        }
        case 3: {
            bool val;
            memcpy(&val, dataRef, sizeof(bool));
            attr->v.boolV = val;
            attr->dt = DT_BOOL;
            break;
        }
        case 1: {
            int len = schema->typeLength[attrNum];
            attr->v.stringV = (char *)malloc(len + 1); // Allocate memory for the string and verify operation success
            if (attr->v.stringV == NULL) {
                free(attr);
                return RC_MEMORY_ALLOCATION_FAILED;
            }
            strncpy(attr->v.stringV, dataRef, len);
            attr->v.stringV[len] = '\0'; // Null-terminate the string
            attr->dt = DT_STRING;
            break;
        }
        default:// data type is unknown
            printf("Unknown data type, .\n");
            free(attr);
            return RC_ERROR;
    }

    *value = attr; // Assign attr to the output parameter
    return RC_OK; // Operation successful
}

// Helper function to set the attribute value based on the data type
extern RC setAttributeValue(char *attrData, DataType dataType, Value *value) {
    switch (dataType) {
        case DT_FLOAT:
            *(float *)attrData = value->v.floatV;
            break;
        case DT_STRING:
            strncpy(attrData, value->v.stringV, strlen(value->v.stringV)); // Copy string value
            attrData[strlen(value->v.stringV)] = '\0'; // Null-terminate the string
            break;
        case DT_BOOL:
            *(bool *)attrData = value->v.boolV;
            break;
        case DT_INT:
            *(int *)attrData = value->v.intV;
            break;
        default:
            return RC_UNKNOWN_DATA_TYPE; // Return error for unknown data type
    }
    return RC_OK; // Return success if everything goes well
}

// Function to set an attribute in a record based on the schema
extern RC setAttr(Record *record, Schema *schema, int attrNum, Value *value) {
    // Do error check parameters
    if (record == NULL || schema == NULL || value == NULL) {
        return RC_NULL_ARGUMENT; 
    }

    int offset = 0; // Initialize offset
    buildOffset(schema, attrNum, &offset); // Obtain correct value of offset

    char *attrData = record->data + offset; // Finish getting attrData's correct value based on offset

    return setAttributeValue(attrData, schema->dataTypes[attrNum], value); // Set the attribute value using the helper function setAttributeValue
}


//**************************************************************************************************************************************************