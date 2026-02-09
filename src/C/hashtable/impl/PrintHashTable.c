/**
 * Prints the hash table.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include "../headers/PrintHashTable.h"

#include "HashTableData.c"

#ifndef __PrintHashTable_C__
#define __PrintHashTable_C__

void collectMetaBits(unsigned char value, char bits[]) {
    int i;
    for(i = 7; i >= 0; i--) bits[7-i] = '0' + ((value >> i) & 1);
}

/** 
 * Prints the whole hash table with index, element, position and hash value.
 * 
 * Input:
 *  *hashTable - pointer to the hash table to be printed.
 * 
 * Output:
 */
void printHashTable(HashTable *hashTable) {

    printf("==================Hash Table====================\n");
    signed char *metaArray = hashTable->metaArray;
    int *elementArray = hashTable->elementArray;
    for(int arrayIndex = 0; arrayIndex < *hashTable->hashTableSize; arrayIndex++) {
        char metaBits[8];
        signed char *metaElement = metaArray + arrayIndex;
        collectMetaBits(*metaElement, metaBits);
        printf("index: %4d, control: %.8s [%4d], element: %4d\n", 
            arrayIndex, metaBits, *metaElement, *(elementArray + arrayIndex));
    }
    printf("==================Hash Table====================\n");
}

#endif