/**
 * Holds Test functions for hash table delete functionality.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "./util/TestFramework.h"
#include "../../../HashTable.h"

#include "./util/TestHashTableUtil.c"
#include "./util/TestDataUtil.c"

HashTable *hashTable = NULL;
unsigned int numOfElements = 0;
signed int *elementArray = NULL;

void beforeAll() {}

void beforeEach() {
    hashTable = createHashTable(0);
    // printHashTable(hashTable);

    numOfElements = 1;
    static signed int elements[1];
    elementArray = elements;
    createTestData(elements, numOfElements);
}

void afterEach() {
    // printHashTable(hashTable);
    printf("Success\n");
    
    hashTable = NULL;
    elementArray = NULL;
    numOfElements = 0;
}

void afterAll() {}

// Insert 1 value -> search that existing value -> delete non exsting value. 
void testDelete1NonExisting() {
    printf("Deleting a non-existng value to the hash table: ");

    signed int nonExistingElements = 15;
    unsigned int isDeleted = delete(hashTable, nonExistingElements);

    assert(isDeleted == 0);
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    assert(currentHashTableSize == 16);
}

// Insert 1 value -> search that existing value -> delete the existing value.
void testDelete1Existing() {
    printf("Deleting an existing value to the hash table: ");

    insert(hashTable, *elementArray);

    int valFoundAt = search(hashTable, *elementArray);
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    unsigned int pos = getHashPos(*elementArray, currentHashTableSize);
    unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, *elementArray);
    assert(valFoundAt == probedPos);

    unsigned int isDeleted = delete(hashTable, *elementArray);

    assert(isDeleted == 1);
    assert(currentHashTableSize == 16);
}

// Insert 4098 values (4096 boundary case + 2 values) -> search all existing values (duplicates and collisions) -> 
// delete all the existing values (4096 boundary case + 2 values, duplicates and collisions).
void testDelete4098Vals() {
    printf("Deleting 4098 values to the hash table: ");

    numOfElements = 4098;
    static signed int elements[4098];
    elementArray = elements;
    createTestData(elements, numOfElements);
    
    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    assert(currentHashTableSize == 16384);

    for(int index = 0; index < numOfElements; index++) {

        signed int elementVal = *(elementArray + index);
        int valFoundAt = search(hashTable, elementVal);
        currentHashTableSize = getCurrentHashTableSize(hashTable);
        unsigned int pos = getHashPos(elementVal, currentHashTableSize);
        unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, elementVal);
        assert(valFoundAt == probedPos);
        
        unsigned int isDeleted = delete(hashTable, elementVal);

        assert(isDeleted == 1);
    }
    
    currentHashTableSize = getCurrentHashTableSize(hashTable);
    assert(currentHashTableSize == 16);
}


// Insert 4096 values (4096 boundary case) -> search all existing values (duplicates and collisions) -> 
// delete all the existing values (4096 boundary case, duplicates and collisions).
void testDelete4096Vals() {
    printf("Deleting 4096 values to the hash table: ");
    
    numOfElements = 4096;
    static signed int elements[4096];
    elementArray = elements;
    createTestData(elements, numOfElements);
    
    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    assert(currentHashTableSize == 8192);

    for(int index = 0; index < numOfElements; index++) {
        signed int elementVal = *(elementArray + index);
        int valFoundAt = search(hashTable, elementVal);
        currentHashTableSize = getCurrentHashTableSize(hashTable);
        unsigned int pos = getHashPos(elementVal, currentHashTableSize);
        unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, elementVal);
        assert(valFoundAt == probedPos);

        unsigned int isDeleted = delete(hashTable, elementVal);

        assert(isDeleted == 1);
    }

    currentHashTableSize = getCurrentHashTableSize(hashTable);
    assert(currentHashTableSize == 16);
}

// Runs the test framework.
int main() {
    testFuncPtrDef testFuncDefs[4] = {
        &testDelete1NonExisting, &testDelete1Existing, &testDelete4098Vals, &testDelete4096Vals
    };
    runAllTests(testFuncDefs, 4);
    return 0;
}