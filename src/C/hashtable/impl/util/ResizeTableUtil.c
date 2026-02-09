/**
 * Create hash table utility functions.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include "../../headers/HashTableStructure.h"

#include "../HashTableData.c"
#include "HashUtil.c"
#include "LoadFactorUtil.c"
#include "SimdUtil.c"

#ifndef __ResizeTableUtil_C__
#define __ResizeTableUtil_C__

/** 
 * Internal: Insert value/s (given number of elements) to the given hash table.
 * 
 * Input:
 *  *hashTableToInsert - pointer to the hash table to insert values.
 *  *valuesToInsert - pointer to the value/s to be inserted.
 *  numOfElements - number of elements to be inserted.
 * 
 * Output:
 */
void insertHashTableValues(HashTable *hashTableToInsert, signed int *valuesToInsert, unsigned int numOfElements) {
    
    *hashTableToInsert->numberOfElements += numOfElements;
    signed int *elementArrayPtr = hashTableToInsert->elementArray;
    signed char *metaArrayPtr = hashTableToInsert->metaArray;
    unsigned int hashTableSize = *hashTableToInsert->hashTableSize;

    // Load group of value array SIMD vector of same EMPTY or DELETED meta value.
    vectype emptyValGrp = broadcastValToVector(EMPTY);
    vectype delValGrp = broadcastValToVector(DELETED);

    for(unsigned int elementCounter = 0; elementCounter < numOfElements; elementCounter++) {
        signed int valueToInsert = *(valuesToInsert + elementCounter);
        unsigned int hashPos = getHashPosVal(valueToInsert) % hashTableSize;
        unsigned int hashPosStrtGrp = hashPos / GROUP_SIZE;
        unsigned short hashPosStrt = hashPos % GROUP_SIZE;
        int elementInserted = 0;

        // Collision handling
        int valClusterStarted = 0;

        // Get the hash verifier value and load group of value array SIMD vector of same hash verifier meta value.
        char hashVerifierVal = getHashVerifierVal(valueToInsert);
        vectype hashVerifierValGrp = broadcastValToVector(hashVerifierVal);

        // Collision handling. Iterate through each group
        unsigned int grpStrtCounter = hashPosStrtGrp * GROUP_SIZE;
        for(unsigned int grpIndex = 0; grpIndex < hashTableSize; grpIndex += GROUP_SIZE) {

            // If hash table end is reached then move to 1st group
            // to cover all the groups when starting in the middle of the groups.
            unsigned int grpCounter = grpStrtCounter + grpIndex;
            grpCounter = grpCounter >= hashTableSize ? grpCounter - hashTableSize : grpCounter;
            
            signed char *metaArrayPtrGrp = metaArrayPtr + grpCounter;
            signed int *elementArrayPtrGrp = elementArrayPtr + grpCounter;

            // Check hash and other meta data in meta array
            // Load group of meta array char values to SIMD vector register.
            vectype metaValGrp = getMetaVectorGrp(metaArrayPtrGrp);

            int verifierBools[GROUP_SIZE], emptyBools[GROUP_SIZE], delBools[GROUP_SIZE];
            // Perform equality of hash verifier, EMPTY or DELETED against meta value group and get group of booleans
            getMatchMaskGrp(hashVerifierValGrp, metaValGrp, GROUP_SIZE, verifierBools);
            getMatchMaskGrp(emptyValGrp, metaValGrp, GROUP_SIZE, emptyBools);
            getMatchMaskGrp(delValGrp, metaValGrp, GROUP_SIZE, delBools);

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
                
                int verifierBool, emptyBool, delBool;
                if(reversedVectorData == 0) {
                    
                    verifierBool = verifierBools[itemCounter];
                    emptyBool = emptyBools[itemCounter];
                    delBool = delBools[itemCounter];
                } else {
                    
                    int reverseCounter = GROUP_SIZE-1 - itemCounter;
                    verifierBool = verifierBools[reverseCounter];
                    emptyBool = emptyBools[reverseCounter];
                    delBool = delBools[reverseCounter];
                }

                if(verifierBool == 1 || delBool == 1) {
                    // Full: 0xxxxxxx is >= 0, has a value, probe to next
                    continue;
                } else if(emptyBool == 1) {
                    // Element is not found in the hash table.
                    *(metaArrayPtrGrp + itemCounter) = hashVerifierVal;   // Assigning Full: 0xxxxxxx meta value
                    *(elementArrayPtrGrp + itemCounter) = valueToInsert;
                    elementInserted = 1;
                    break;
                }
            }

            if(elementInserted == 1) {
                break;
            } // or continue to next group
        }
    }
}

/** 
 * Internal: create new resized hash table and transferring elements from old table to new table.
 * 
 * Input:
 *  *hashTableToResize - pointer to the hash table to resize.
 *  numOfElements - new number of elements to be added which require table resizing.
 * 
 * Output:
 *  *resizedHashTable - pointer to rezised hash table.
 */
HashTable *resizeAndTransferElements(HashTable *hashTableToResize, unsigned int numOfElements) {

    unsigned int newNumOfElements = 
        *hashTableToResize->numberOfElements - *hashTableToResize->delNumOfElements + numOfElements;
    unsigned int previousHashTableSize = *hashTableToResize->hashTableSize;
    HashTable *previousHashTable = hashTableToResize;
    HashTable *resizedHashTable = createHashTable(newNumOfElements);

    // Transfer elements from old hash table to new
    signed int *elementArrayPtr = previousHashTable->elementArray;
    signed char *metaArrayPtr = previousHashTable->metaArray;

    for(unsigned int elementCounter = 0; elementCounter < previousHashTableSize; elementCounter++) {
        signed char metaBits = *(metaArrayPtr + elementCounter);

        if(metaBits >= 0) {  // Full: 0xxxxxxx is >= 0, has a value
            signed int *valueToInsert = elementArrayPtr + elementCounter;
            insertHashTableValues(resizedHashTable, valueToInsert, 1);
        }
    }
    updateCurrentLoadFactor(newNumOfElements, *resizedHashTable->hashTableSize);

    return resizedHashTable;
}

#endif