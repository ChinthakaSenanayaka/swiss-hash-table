/**
 * Create hash table utility functions for tests.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include "../../../../src/C/hashtable/headers/HashTableStructure.h"
#include "../../../../src/C/hashtable/impl/HashTableData.c"

#ifndef __TestHashTableUtil_C__
#define __TestHashTableUtil_C__

unsigned int getDelNumOfElements(HashTable *hashTable) {
    return *hashTable->delNumOfElements;
}

unsigned int getNumOfElements(HashTable *hashTable) {
    return *hashTable->numberOfElements;
}

unsigned int getCurrentHashTableSize(HashTable *hashTable) {
    return *hashTable->hashTableSize;
}

unsigned int getHashTableValPosByBasePos(HashTable *hashTable, unsigned int basePos, signed int value) {

    // value is not found is -1.
    int pos = -1;
    unsigned int hashTableSize = getCurrentHashTableSize(hashTable);
    signed int *elementArrayPtr = hashTable->elementArray;
    signed char *metaArrayPtr = hashTable->metaArray;

    for(unsigned int index = 0; index < hashTableSize; index++) {

        // To cover all the groups in the hash table.
        unsigned int counter = basePos + index;
        counter = counter >= hashTableSize ? counter - hashTableSize : counter;

        signed int element = *(elementArrayPtr + counter);
        signed int metaElement = *(metaArrayPtr + counter);

        if(metaElement >= 0) {

            if(element == value) {
                // value is found in the hash table. skipping the loop.
                pos = counter;
                break;
            }
        } else if(metaElement == EMPTY) {
            // value is not in the hash table. not found. skipping the loop.
            break;
        }
    }

    return pos;
}

#endif