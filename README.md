	The goal of this assignment is to implement a storage manager. It does so creating, opening, closing and deleting page files. In addition, this program also is capable of reading and writing blocks, obtaining the block position, appending an empty block, and ensuring the capacity by increasing the size of the pages to numberOfPages. 
	The storage manager creates files in createPage by allocating PAGE_SIZE(4096) bytes of memory, opening the file, and allocating memory for it, while page files are opened in the openPageFile method, which uses the fopen method to open the file, and initializes the attributes of fHandle. The closePageFile method works by checking for the existence of the file and closing it if it exists, while the destroyPageFile method opens the file, closes it, and removes it. The readBlock method reads blocks by checking if the amount of pages is file, creating a file pointer, calculating the offset and using them to find the right position, read the page into the buffer, and change the amount of pages accordingly, while the getBlockPos method returns the current page position. The readFirstBlock and readLastBlock methods perform error checking and utilize the readBlock method to read the block at the initial and final positions, respectively. The readPreviousBlock, readCurrentBlock, and readNextBlock check if the file handle is null or if there is no file associated and if not, the block is read and position is changed accordingly. The helper method isPageNumberValid returns 0 if the pageNum over the total number of pages or negative and 1 otherwise, and it is used in writeBlock; after this, it proceeds to open the file and check if it is null and if not, a buffer pointer which checks every index in the page is used to check if the writing fails. If the writing succeeds, then the contents are written to the file. WriteCurrentBlock performs most of these actions; however, it does not check the validity of the pageNumber, and it increases the total amount of pages. The appendEmptyBlock allocates and sets 4096 null bytes, creates a block pointer to check write failures, opens the file, and checks the write failures, increasing the total amount of pages and freeing the block afterwords. The ensureCapacity checks if the necessary number of pages is over the entire amount of pages and if so, it opens the file, checks if it is null, and appends empty blocks until the total amount of pages is not less than the numberOfPages parameter. Error checking has been used wherever relevant.