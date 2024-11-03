CONTRIBUTION :

->PRANAV MADAN(A20453597) - 33.34%
->SRUJITH BORRA(A20562890) - 33.33%
->KOUSHIK CHOUDARY BHUMA(A20561884) - 33.33%

STEPS TO RUN THE CODE :

Step 1: Using Ubuntu WSL or Debian WSL, cd into the right folder.
Step 2: Run the make clean to get rid of unnecessary .o files.
Step 3: Run the make to regenerate .o files.
Step 4: (optional):Use clear to clear the previous output.
Step 5: run commands ./test_expr and ./test_assign3_1. If you want to view a more descriptive depiction of test_assign3_1's mechanics, use valgrind --leak-check=full -s ./test_assign3.



TABLE AND RECORD MANAGER FUNCTIONS :
The record manager is initialized and shut down using the record manager related functions. A table can be create, open, close, and delete using the functions associated to tables. We use a page replacement strategy in Buffer Manager (Assignment 2) to access pages via Buffer Pool. Additionally, actions on page files on disk are indirectly carried out via the Storage Manager (Assignment 1).

1) initRecordManager :
Purpose -> Establishes the environment required to manage records in a database by    
initializing the Record Manager.
Description -> This function sets up any required global structures or memory allocations, initializes the Storage Manager (to handle file operations), and gets the Record Manager ready. Prior to doing any additional Record Manager operations, it must be contacted.   
2) shutdownRecordManager :
Purpose -> Closes the Record Manager and frees up any memory or resources that it may    
have been using.
Description -> This feature makes sure that every resource used while the Record Manager is running is released. It calls the C function free() to release memory space after de-allocating memory and setting the Record Manager's data structure pointer to NULL. To stop memory leaks, this function has to be invoked once the Record Manager is no longer required.
3) createTable :
Purpose -> Creates a table in memory and on disk with the given name and structure.
Description -> This function creates the matching page file on disk and sets the table's characteristics (name, datatype, and size) to initialize it. Additionally, it calls initBufferPool() to initialize the buffer pool using the LRU page replacement policy. It writes the first block containing the table to the page file and closes it after configuring the table metadata.
4) openTable :
Purpose -> Opens and sets up for usage an existing table that is already in memory.
Description -> Using the supplied table name as a guide, this function loads the metadata and schema for a table into memory. It prepares the table for operations like reading, writing, and scanning by initializing the Buffer Pool with the given schema. It loads the table's pages into the buffer pool for later access after initializing.
5) closeTable :
Purpose -> Closes the active table and guarantees that all modifications are saved.
Description -> This function shuts the table that rel is referencing. By designating dirty pages in the buffer, it makes sure that any modifications made to the table are written back to the disk before closure. After then, it calls for shutdown.BufferPool() to safely close the table, free up resources, and save the state to the page file.
6) deleteTable :
Purpose -> To remove a table from the system and release the resources it was using.
Description -> The table indicated by the parameter name is deleted by this function. It uses the Storage Manager's destroyPageFile() function to delete the page file from disk, freeing up any memory or space that was set aside for keeping the table. This procedure guarantees the complete deletion of the table and all of its contents.
7) getNumTuples :
Purpose -> To obtain the total number of records, or tuples, in a given table.
Description -> The function retrieves the quantity of tuples present in the table that is specified by the parameter rel. It makes use of the metadata in the table, particularly the tuplesCount variable, which records the total number of tuples. This value is a component of the unique data structure that stores the metadata for the table.
 
HANDLING RECORD FUNCTIONS :
These functions can be used to insert a new record, update an existing record with new values, delete a record with a certain RID, and retrieve a record with a specific RID.

8) insertRecord :
Purpose -> Updates the record parameter with the new record's Record ID (RID) and inserts it into the table.
Description -> This function creates a new record in a table and gives it a distinct Record ID (RID). It locates the empty slot, pins the page with the empty slot, then inserts a '+' at the data pointer to indicate that the record has been added. In order for the Buffer Manager to write the page back to disk, it is designated as dirty. The memcpy() function is used to copy the record's data into the vacant slot. The page is unpinned after completion.
9) deleteRecord :
Purpose -> To remove a record from a table by using the specified Record ID (RID).
Description -> This function deletes a record from the table that rel references, which is identified by its Record ID (id). By setting freePage to the Page ID of the page containing the record, it modifies the table's metadata and frees up that space for additional insertions in the future. The function navigates to the data pointer, pins the page with the record on it, and then marks the record as destroyed by changing the initial character to '-'. The page is unpinned after the record has been tagged, and soiled to guarantee that the Buffer Manager saves the modifications back to disk.
10) updateRecord :
Purpose -> Updates a record that already exists in a designated table.
Description -> This function finds the page in the buffer pool that has the record that needs to be updated, pins it there, and sets the Record ID. After designating the page as dirty and utilizing memcpy() to copy the updated data from the supplied record argument into the current record, the page is unpinned to be released from the buffer pool.
11) getRecord :
Purpose -> To use the Record ID to retrieve a particular record from a table.
Description -> This function finds the page in the supplied table (rel) that contains the record that is indicated by the given Record ID (id). It copies the associated data into it, sets the Record ID of the supplied record parameter, and pins the pertinent page in the buffer pool. Ultimately, the function releases the page from the buffer pool by unpinning it.

SCAN FUNCTIONS :
To retrieve all tuples from a table that satisfy a particular criteria (expressed as an Expr), utilize the Scan-related functions. The RM_ScanHandle data structure that is supplied as an input to startScan is initialized when a scan is started. The next tuple that satisfies the scan criteria is then returned by calling the subsequent procedure. The result is RC_SCAN_CONDITION_NOT_FOUND if NULL is supplied as the scan condition. after the scan is finished, returns RC_RM_NO_MORE_TUPLES; otherwise, returns RC_OK (unless an error occurs).

12) startScan :
Purpose -> Starts a table scan procedure for the purpose.
Description -> This function takes an argument, the RM_ScanHandle data structure, and uses it to initialize a scan. It configures the relevant variables for the scanning procedure. An error code (RC_SCAN_CONDITION_NOT_FOUND) indicating that no scan condition was given is returned if the scan condition is NULL.
13) next :
Purpose -> The next tuple that meets the scan criteria is retrieved for this reason.
Description -> The function looks for the NULL scan condition and returns an error if it is detected. It returns an error code if there are no more tuples. It copies data, pins the matching page, iterates through the tuples, and assesses the condition. It unpins the page and returns RC_OK if a tuple matches; if not, it produces an error stating that there are no more matching tuples.
14) closeScan :
Purpose -> Ends the scanning process.
Description -> This function looks at the scanCount in the table's metadata to see if the scan was complete. The function unpins the connected page and resets any scan-related metadata variables if scanCount is larger than 0, indicating that the scan was not completed. Ultimately, the RAM used for the scan metadata is released.

SCHEMA FUNCTIONS :
These functions are used to generate a new schema and return the number of records in bytes for a given schema. 

15) getRecordSize :
Purpose -> Provides a record's size according on the given schema.
Description -> This function uses an iterative process through the record's attributes in the supplied schema to get the total size of the record. The entire size of the record is represented by the variable size, which is the result of adding the byte sizes of each attribute.
16) createSchema :
Purpose -> To generate a new memory-based schema with the desired properties.
Description -> This function uses the parameters sent in to initialize a new schema object. It accepts four inputs: datatypes (the data types of the attributes), typeLength (the lengths of the attributes, such as for STRING), attrNames (the names of the attributes), and numAttr (the number of attributes). The function sets up memory for the schema object and populates the fields with the supplied data.
17) freeSchema :
Purpose -> Deallocates memory in support of a given schema.
Description -> This function clears the memory of the schema provided by the schema parameter. It keeps track of how many references to the schema are currently in use by using the refNum field in each page frame. The function uses the C function free() to release the memory allocated for the schema and remove it from the system when the reference count is zero.

ATTRIBUTE FUNCTIONS :
These functions are used to generate a new record for a given schema and retrieve or set the attribute values of an existing record. When a new record is created, the data field should be allotted enough memory to store the binary representations for every attribute in the record, as specified by the schema.  

18) createRecord :
Purpose -> Memory is allocated for a new record according to a predetermined structure.
Description -> This function initializes the data with a '-' character to identify it as new, allocates memory for the record and its contents, creates a new record in the specified schema, and assigns the record to the supplied record argument.
19) freeRecord :
Purpose -> Memory for a designated record is released from allocation.
Description -> This function effectively releases resources and stops memory leaks by using the C method free() to empty the memory space allocated for the specified record parameter.
20) getAttr :
Purpose -> To retrieve a certain attribute from a record.
Description -> Using the supplied schema and attribute number, this function pulls an attribute from the given record. To make the attribute data for the record easily accessible, it first locates the attribute's position using the attrOffset() function. It then transfers the relevant datatype and value into the *value parameter.
21) setAttr :
Purpose -> Sets the value of a particular attribute in a record is the purpose.
Description -> This function uses the given schema and attribute number to alter the value of an attribute in a given record. The value parameter is used to filter the newly allocated data. It locates the attribute's position using the attrOffset() function, then puts the supplied data into the attribute, making sure the datatype and value are updated appropriately.

