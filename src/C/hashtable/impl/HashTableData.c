/**
 * Constants and variables.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include "../HashTableConfig.h"

#ifndef __HashTableData_C__
#define __HashTableData_C__

/** Current load factor as of current number of elements and current table size. */
static float currentLoadFactor = 0;

/** Hash table data structure. */
struct hashTable {
    // To keep number of elements in the table.
    unsigned int *numberOfElements;

    // To keep deleted number of elements in the table.
    // This is needed as delete won't hard delete but adds a delete marker.
    unsigned int *delNumOfElements;

    // To keep current hash table size in the table.
    unsigned int *hashTableSize;

    /**
     * Hash table meta data array for elements.
     * 
     * Possible values:
     * Full: 0xxxxxxx - hash bucket is filled with a value, 7x's are last 7 bits of hash code
     * Empty: 10000000 (-128) - hash bucket is empty
     * Deleted: 11111110 (-2) - hash bucket value is deleted (acts as real Sentinel)
     * Sentinel: 11111111 (-1) - the marker to show end of hash table or value cluster on the hash table
     */
    signed char *metaArray;

    // Hash table value array for elements.
    signed int *elementArray;
};

#endif