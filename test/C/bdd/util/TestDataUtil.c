/**
 * Creates test data with random values as required by tests.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include <time.h>
#include <stdlib.h>

#include "./TestHashUtil.h"

#ifndef __TestDataUtil_C__
#define __TestDataUtil_C__

static int randConfigInit = 0;

int getRandomInt() {

    // Intitilizing srand only once.
    if (randConfigInit == 0) {
        srand(time(NULL));
        randConfigInit = 1;
    }

    return rand();
}

unsigned int getHashPos(long long int value, unsigned int hashTableSize) {
    return getHashPosVal(value) % hashTableSize;
}

unsigned int getHashPosInGroup(long long int value, unsigned int hashTableSize) {
    return (getHashPosVal(value) % hashTableSize) % GROUP_SIZE;
}

unsigned int getHashPosGroup(long long int value, unsigned int hashTableSize) {
    return (getHashPosVal(value) % hashTableSize) / GROUP_SIZE;
}

/**
 * Creates test data.
 * 
 * Input:
 *   elementArray - integer element array to be used as data in hash table.
 * 
 * Output:
 */
void createTestData(int elementArray[], int arraySize) {
    for(int index = 0; index < arraySize; index++) {
        elementArray[index] = getRandomInt();
    }
}

#endif