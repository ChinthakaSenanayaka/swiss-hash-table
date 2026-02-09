/**
 * Create a hash table.
 * Optional to given hash table size.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include "../headers/CreateHashTable.h"

#include "HashTableData.c"
#include "util/HashUtil.c"
#include "util/LoadFactorUtil.c"
#include "util/CreateTableUtil.c"

#ifndef __CreateHashTable_C__
#define __CreateHashTable_C__

/** 
 * Create the Hash table for scratch.
 * 
 * Input:
 *  numberOfElements - number of elements to be inserted.
 * 
 * Output:
 *  HashTable* - pointer to HashTable data structure.
 */
HashTable *createHashTable(unsigned int numOfElements) {

    HashTable *hashTable = (HashTable*) malloc(sizeof(HashTable));

    if(numOfElements >= 0) {

        static unsigned int hashTableSize;
        hashTableSize = getHashTableSize(numOfElements);
        hashTable->hashTableSize = &hashTableSize;

        static unsigned int numberOfElements;
        numberOfElements = 0;
        hashTable->numberOfElements = &numberOfElements;

        static unsigned int delNumOfElements;
        delNumOfElements = 0;
        hashTable->delNumOfElements = &delNumOfElements;
        
        signed int *elementArrayPtr = (signed int*) malloc(hashTableSize * sizeof(signed int));
        signed char *metaArrayPtr = (signed char*) malloc(hashTableSize * sizeof(signed char));
        
        // default value init to remove garbage values
        for(int initCounter = 0; initCounter < hashTableSize; initCounter++) {
            *(elementArrayPtr + initCounter) = *createDefaultElement();
            *(metaArrayPtr + initCounter) = *createEmptyMetaElement();
        }
        hashTable->metaArray = metaArrayPtr;
        hashTable->elementArray = elementArrayPtr;

    }

    setCurrentLoadFactor(0, *hashTable->hashTableSize);

    return hashTable;

}

#endif