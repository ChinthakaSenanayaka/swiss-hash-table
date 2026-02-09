/**
 * Delete a given element from the hash table.
 *
 * Author: Chinthaka Senanayaka
 * Year: 2025
 */
#include "../headers/DeleteElement.h"

#include "HashTableData.c"
#include "util/HashUtil.c"
#include "util/LoadFactorUtil.c"
#include "util/CreateTableUtil.c"
#include "util/SimdUtil.c"
#include "util/ResizeTableUtil.c"

#ifndef __DeleteElement_C__
#define __DeleteElement_C__

/**
 * Delete the given value in the given hash table.
 *
 * Input:
 *  *hashTable - pointer to the hash table to delete value.
 *  value - value to be deleted.
 *
 * Output:
 *  status - if deleted then 1, otherwise -1.
 */
unsigned int delete(HashTable *hashTable, signed int value) {

    unsigned int elementDeleted = 0;
    signed char *metaArrayPtr = hashTable->metaArray;
    signed int *elementArrayPtr = hashTable->elementArray;
    unsigned int hashTableSize = *hashTable->hashTableSize;

    unsigned int hashPos = getHashPosVal(value) % hashTableSize;
    unsigned int hashPosStrtGrp = hashPos / GROUP_SIZE;
    unsigned short hashPosStrt = hashPos % GROUP_SIZE;

    // Get the SIMD vector filled with same hash verifier value and SIMD vector filled with same EMPTY value.
    char hashVerifierVal = getHashVerifierVal(value);
    vectype hashVerifierValGrp = broadcastValToVector(hashVerifierVal);
    vectype emptyValGrp = broadcastValToVector(EMPTY);

    // Collision handling. Iterate through each group
    unsigned int grpStrtCounter = hashPosStrtGrp * GROUP_SIZE;
    for(unsigned int grpIndex = 0; grpIndex < hashTableSize; grpIndex += GROUP_SIZE) {

        // If hash table end is reached then move to 1st group
        // to cover all the groups when starting in the middle of the groups.
        unsigned int grpCounter = grpStrtCounter + grpIndex;
        grpCounter = grpCounter >= hashTableSize ? grpCounter - hashTableSize : grpCounter;
        
        signed char *metaArrayPtrGrp = metaArrayPtr + grpCounter;

        // Check hash and other meta data in meta array
        // Load group of meta array char values to SIMD vector register.
        vectype metaValGrp = getMetaVectorGrp(metaArrayPtrGrp);

        int verifierBools[GROUP_SIZE], emptyBools[GROUP_SIZE];
        // Perform equality of hash verifier or EMPTY against meta value group and get group of booleans
        getMatchMaskGrp(hashVerifierValGrp, metaValGrp, GROUP_SIZE, verifierBools);
        getMatchMaskGrp(emptyValGrp, metaValGrp, GROUP_SIZE, emptyBools);

        // NOTE: There is a trade off of below check on smaller hash table vs. larger hash tables
        // Iterate through each item of the selected group
        unsigned short itemStrtCounter = grpCounter == grpStrtCounter ? hashPosStrt : 0;
        for(unsigned short itemIndex = 0; itemIndex < GROUP_SIZE; itemIndex++) {

            // If hash table end is reached for 1 group sized hash table then
            // to cover all the elements when starting in the middle of the group.
            unsigned short itemCounter = itemStrtCounter + itemIndex;
            if(hashTableSize == GROUP_SIZE) {
                if(itemCounter >= GROUP_SIZE) {
                    itemCounter = itemCounter - hashTableSize;
                }
            } else {
                if(itemCounter >= GROUP_SIZE) {
                    break;
                }
            }
            
            int verifierBool, emptyBool;
            if(reversedVectorData == 0) {

                verifierBool = verifierBools[itemCounter];
                emptyBool = emptyBools[itemCounter];
            } else {

                int reverserCounter = GROUP_SIZE-1 - itemCounter;
                verifierBool = verifierBools[reverserCounter];
                emptyBool = emptyBools[reverserCounter];
            }

            if(verifierBool == 1) {
                // Element is found in the hash table.
                signed int *elementArrayPtrGrp = elementArrayPtr + grpCounter;
                signed int valueElement = *(elementArrayPtrGrp + itemCounter);
                if(valueElement == value) {
                    // Value is deleted with setting deafult values
                    *(elementArrayPtrGrp + itemCounter) = *createDefaultElement();
                    *(metaArrayPtrGrp + itemCounter) = *createDeletedMetaElement();
                    
                    (*hashTable->delNumOfElements)++;
                    updateCurrentLoadFactor(-1, *hashTable->hashTableSize);
                    
                    elementDeleted = 1;
                    break;
                }
            } else if(emptyBool == 1) {
                // Element is not found in the hash table.
                break;
            }
            // Element is not found in the hash table, continue to next probe.
        }

        if(elementDeleted == 1) {
            // Shrink the table
            if(currentLoadFactor <= MIN_LOAD_FACTOR) {
                *hashTable = *resizeAndTransferElements(hashTable, 0);
            }
            break;
        } // or continue to next group
    }

    return elementDeleted;
}

#endif