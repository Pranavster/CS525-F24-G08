Ill CS 525 - ADVANCED DATABASE ORGANIZATION

ASSIGNMENT 4 

GROUP : 08 (Contributions) : Pranav Madan(A20453597) - 33.33%
                             Srujith Borra(A20562890) - 33.33%
                             Koushik Choudary Bhuma(A20561884) - 33.33%

Steps To Run The Code :


Step 1: Using Ubuntu WSL or Debian WSL, cd into the right folder.
Step 2: Run the make clean to get rid of unnecessary .o files.
Step 3: Run the make to regenerate .o files.
Step 4: (optional):Use clear to clear the previous output.
Step 5: run commands ./test_expr and ./test_assign4_1.            

//init and shutdown index manager :

The index manager is initialized and terminated using these functions, which release all of the resources that have been acquired.

1) initIndexManager() :
   purpose : The index manager is initialized by the initIndexManager function in order 
             to prepare the environment for B-tree index operations.
   Description : ->sets up the index manager for B-tree index management. 
2) shutdownIndexManager() : 
   purpose : The shutdownIndexManager function indicates the index manager is shut down.
   Description : ->indicates the index manager is being shut down by returning RC_OK.

//create, destroy, open, and close an btree index :

A b-tree index can be created or deleted using these functions.

3) createBtree() :
   purpose : By initializing the required elements for controlling the tree topology, the 
             createBtree function generates a new B+ Tree.
   Description : ->Memory Allocation: Assigns heap space to global variables, such as a 
                   page handler, buffer pool, trHandle, scanHandle, scanMtdata, and 
                   treeData, and connects them to the appropriate pointers in treeData.
                 ->File Creation: Initializes the first page, creates a new file with the 
                   given idxId, and saves metadata in the file handler of treeData.
                 ->B+ Tree information is initialized by setting numNodes to 1, 
                   rootPageNum to 1, numEntries to 0, and the maximum number of entries 
                   per page to n.
                 ->In order to initialize the root node data (page number 1, tagged as 
                   leaf, no parent, zero entries), a second page is created as the root 
                   node, and metadata is formatted into a string and written into the 
                   file.
4) openBtree() :
   purpose : The openBtree function opens an existing B+ Tree file, loads its metadata, 
             and initializes necessary data structures for managing the tree.
   Description : ->File and Metadata Loading: Opens the file that the name specifies, 
                   loads its metadata into the fileHandler of treeData, then configures 
                   the pageHandler using the heap space that has been allotted.
                 ->Metadata reformatting involves copying the B+ Tree metadata to the 
                   global BTreeHandle after loading it from the file's first page and 
                   reformatting it into a fileMD structure.
                 ->Handle Assignment: Makes the global BTreeHandle accessible for 
                   additional tree operations by setting the supplied address to 
                   reference it.
5) closeBtree() :
   purpose : The closeBtree function closes an open B+ Tree, saves any changes, and 
             releases all allocated resources.
   Description : ->Metadata Update: Writes the B+ Tree metadata to the file's first page 
                   after reformatting it into a char pointer (string).
                 ->Buffer Pool Flush: Closes the buffer pool after writing all of its 
                   soiled pages back to disk.
                 ->Resource Deallocation: Makes available heap space for the page 
                   handler, tree handler, and buffer manager.
                 ->Final Cleanup: Makes sure that all memory and resources linked to the 
                   open B+ Tree are appropriately relinquished, preparing it for use in 
                   the future.
6) deleteBtree() :
   purpose : The B+ Tree file linked to the given filename is permanently erased by the 
             deleteBtree function.
   Description : ->File Deletion: Completely removes the B+ Tree data from the file 
                   system by using the Storage Manager to delete the file with the 
                   supplied filename.
                 ->Resource Cleanup: Verifies that no longer referenced resources, 
                   including buffer data or metadata, are connected to the file.
                 ->Validation: Verifies if the file deletion process was successful and, 
                   if not, provides the relevant error code.
// access information about a b-tree :

These functions assist us in obtaining details about our B+ Tree, such as the quantity of nodes and keys within it.

7) getNumNodes() :
   purpose : The B+ Tree's total node count is obtained using the getNumNodes function.
   Description : ->Retrieve Node Count: This function retrieves the number of nodes that 
                   are stored in the numNodes field by accessing the B+ Tree information.
                 ->Copy to Address: Transfers the number of nodes to the memory address 
                   that is provided.
                 ->Efficient Access: Without having to navigate the tree structure, this 
                   method retrieves the node count straight from metadata.
                 ->Verification: Makes sure the value is copied and retrieved 
                   successfully, returning an error code in the event that something goes 
                   wrong.
8) getNumEntries() :
   purpose : The B+ Tree's total number of entries is obtained using the getNumEntries 
             function.
   Description : ->Retrieve Entry Count: This method retrieves the numEntries value, 
                   which is the total number of entries, by accessing the B+ Tree 
                   metadata.
9) getKeyType() :
   purpose : The getKeyType function's goal is to obtain the data type of the keys that 
             are kept in the B+ Tree.
   Description : ->Retrieve Key Type: This method retrieves the keyType value, which 
                   represents the data type of the keys, by accessing the B+ Tree 
                   information.
                 ->merely returns keyType's value, which is already saved in the tree's 
                   metadata for quick access.
  => getDataBySeperatorForInt :
    
    ->Retrieve the string that is being referenced by char **ptr.
    ->Set each character to the termination character (\0) and allocate memory space for 
      a temporary string of 100 characters.
    ->Copy every character in the provided string into the temporary string as you go 
      through it until you reach the designated separator.
    ->Transform the ASCII values in the temporary string into an integer.
    ->The memory space used for the temporary string should be released.
    ->Give the generated integer back.

  => readMetaData :
     ->If it isn't already there, load the page with the specified page number into the 
       buffer pool and pin it.
     ->From the loaded page, extract the root page number, then save it in the designated 
       file (B+ tree) metadata structure.
     ->Retrieve the node count from the loaded page and save it in the specified file's 
       metadata structure (B+ tree).
     ->Save the number of entries in the specified file (B+ tree) metadata structure 
       after retrieving it from the loaded page.
     ->Save the key type in the designated file (B+ tree) metadata structure after 
       retrieving it from the loaded page.
     ->Using the specified page number, unpin the recently pinned page.

  => getDataBySeperatorForFloat :
     ->Retrieve the string that is being referenced by char **ptr.
     ->Make room in the heap for a 100-character temporary string.
     ->Assign a terminating character (\0) to each character in the temporary string.
     ->Copy each character as you go through the provided string until you reach the 
       designated dividing character.
     ->Transform the ASCII values in the temporary string into a float.
     ->Release the heap space that the temporary string has occupied.
     ->Give the generated float back.

  => locatePageToInsertData :
     ->If the root is a leaf node, return the data from the root page.
     ->Make a recursive call using the node the first pointer is addressing if the 
       supplied key is less than the first key in the provided node.

// index access :

In a given B+ Tree, these functions are used to locate, add, and remove keys. Additionally, we may use the openTreeScan, nextEntry, and closeTreeScan methods to search through every entry in a B+ Tree in a sorted order.

10) findKey() :
    purpose : The findKey method looks for a given key in a B+ Tree and returns the 
              record ID (RID) that corresponds to it.
    Description : ->Get Metadata: Retrieve the buffer pool, fileHandler, and pageHandler 
                    from the mgmtData of the specified tree handler.
                  ->Load Root Node: Use the tree handler's mgmtData to find the page 
                    number of the B+ Tree's root node, then load the appropriate node.
                  ->Go Through the Keys Again: Until a match is found, go through the 
                    node's key values and compare each one with the provided key.
                  ->Store RID: Copy the record slot and record page numbers to the given 
                    RID structure after you've located the key.
11) insertKey() :
    purpose : The insertKey function's goal is to add a new key to the B+ Tree while 
              making sure it goes in the appropriate leaf node.
    Description : ->Retrieve Metadata: From the provided tree handler's mgmtData, obtain 
                    the pageHandler, buffer pool, and fileHandler.
                  ->Fetch Tree Information: Use the tree handler's mgmtData to get the 
                    number of nodes in the B+ tree as well as the maximum number of 
                    elements that can be in a node.
                  ->Load Root Node: Use the buffer pool to load the root node into memory 
                    after obtaining the page number of the B+ tree.
                  ->Locate the Leaf Node: Find and load the leaf node page from the B+ 
                    tree that matches the specified key value.
12) deleteKey() :
    purpose : The deleteKey function's goal is to eliminate a given key and the record 
              that goes with it from the B+ Tree.
    Description : ->Retrieve Metadata: From the provided tree handler's mgmtData, obtain 
                    the buffer pool and pageHandler.
                  ->Load Root Node: Locate the root node page number of the B+ tree and 
                    load the appropriate page into memory.
                  ->Find the Leaf Node: Locate and load the leaf node that has the key 
                    that corresponds to the given key value.
                  ->Remove Key: Using the received RID slot and page number, remove the 
                    record from the leaf node.
13) openTreeScan() :
    purpose : The openTreeScan function sets up the procedure to look for key-value 
              pairings in a B+ Tree.
    Description : ->Get Metadata: Retrieve the pageHandler and buffer pool from the 
                    mgmtData of the specified tree handler.
                  ->Provide heap space for a scanManager and a scanHandler in order to     
                    allocate scan structures.
                  ->Load Root Node: Locate the page number of the root node of the B+ 
                    tree, then copy its contents into a pgData structure and load them 
                    into memory.
                  ->Set aside money for leaf pages: Set aside room in the heap to hold 
                    the leaf page numbers that will be tracked throughout the scan.
pe
15) closeTreeScan() :
    purpose : The closeTreeScan function's goal is to end the scan process and release 
              all related resources.
    Description : ->Release Scan Data: Release the space that the scan handler's mgmtData 
                    has occupied.
                  ->Release Scan Handler: Release the space that the scan handler has 
                    taken up.
                  ->Nullify Handler Pointer: To finish the cleanup, set the scan handler   
                    pointer to NULL.

// debug and test functions :

16) printTree() :
    purpose : Print the contents of the B+ Tree.
    Description: Iterate through the contents of the Tree: Intended to get all the data in the tree and add it to a char array 




