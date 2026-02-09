/**
 * Create hash table utility functions.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include "../HashTableData.c"

#ifndef __CreateTableUtil_C__
#define __CreateTableUtil_C__

/** 
 * Getter for hash table size. Hash table size is based on the number of elements to be inserted and present in the table
 * and it will be always in power of 2.
 * 
 * Input:
 *  numOfItems - number of items to be inserted to the hash table.
 * 
 * Output:
 *  hashTableSize - hash table size.
 */
int getHashTableSize(unsigned int numOfItems) {

    // load factor should be less than or equal to max load factor and greater than min load factor.
    unsigned int hashTableSize = GROUP_SIZE;

    while (((float) numOfItems / hashTableSize) > MAX_LOAD_FACTOR) {
        hashTableSize *= RESIZING_FACTOR;
    };

    // hashTableSize > GROUP_SIZE check is needed to not to go below default hash table size 16.
    while (hashTableSize > GROUP_SIZE && ((float) numOfItems / hashTableSize) <= MIN_LOAD_FACTOR) {
        hashTableSize /= RESIZING_FACTOR;
    };
    
    return hashTableSize;
}

/** 
 * Getter for meta data element with default values in it.
 * 
 * Input:
 * 
 * Output:
 *  metaElement* - pointer for the meta data element in the memory.
 */
signed char *createEmptyMetaElement() {
    static signed char metaElement = EMPTY; // Assigning default Empty: 10000000 (-128) value
    return &metaElement;
}

/** 
 * Getter for meta data element with default values in it.
 * 
 * Input:
 * 
 * Output:
 *  metaElement* - pointer for the meta data element in the memory.
 */
signed char *createDeletedMetaElement() {
    static signed char metaElement = DELETED; // Assigning Deleted: 11111110 (-2)
    return &metaElement;
}

/** 
 * Getter for value element with default value in it.
 * 
 * Input:
 * 
 * Output:
 *  element* - pointer for the value element in the memory.
 */
signed int *createDefaultElement() {
    static signed int element = 0;
    return &element;
}

#endif