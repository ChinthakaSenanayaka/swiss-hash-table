/**
 * Inserts a given value to the hash table.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include <stdio.h>

#include "../headers/InsertElement.h"

#include "HashTableData.c"
#include "util/HashUtil.c"
#include "util/LoadFactorUtil.c"
#include "util/ResizeTableUtil.c"

#ifndef __InsertElement_C__
#define __InsertElement_C__

/** 
 * Insert value/s (given number of elements) to the given hash table.
 * 
 * Input:
 *  *hashTableToInsert - pointer to the hash table to insert values.
 *  valueToInsert - value to be inserted.
 * 
 * Output:
 */
void insert(HashTable *hashTableToInsert, int valueToInsert) {

    signed int *elementArrayPtr = hashTableToInsert->elementArray;
    unsigned int numOfElements = 1;

    // In case, hash table internal arrays are not initialized
    if(elementArrayPtr == NULL) {
        hashTableToInsert = createHashTable(numOfElements);
    }

    updateCurrentLoadFactor(numOfElements, *hashTableToInsert->hashTableSize);
    // Expand the table
    if(currentLoadFactor > MAX_LOAD_FACTOR) {
        *hashTableToInsert = *resizeAndTransferElements(hashTableToInsert, numOfElements);
    }
    
    insertHashTableValues(hashTableToInsert, &valueToInsert, numOfElements);
}

#endif