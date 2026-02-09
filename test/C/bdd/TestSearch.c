/**
 * Holds Test functions for hash table search functionality.
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

// Searches a non exiting value in the hash table.
void testSearch1NonExisting() {
    printf("Searching a non-existng value to the hash table: ");

    int valFoundAt = search(hashTable, *elementArray);

    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    unsigned int pos = getHashPos(*elementArray, currentHashTableSize);
    unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, *elementArray);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 16);
}

// Inserts 1 new values to the hash table and search that value.
void testSearch1Existing() {
    printf("Searching an existng value to the hash table: ");

    insert(hashTable, *elementArray);

    int valFoundAt = search(hashTable, *elementArray);

    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    unsigned int pos = getHashPos(*elementArray, currentHashTableSize);
    unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, *elementArray);
    assert(valFoundAt == probedPos);
}

// Inserts 4098 new values to the hash table (can have duplicates) and search all 4098 values.
// This is to search duplicates and search through multiple groups (4096 boundary case + 2 values and collisions).
void testSearch4098Vals() {
    printf("Searching 4098 values to the hash table: ");

    numOfElements = 4098;
    static signed int elements[4098];
    elementArray = elements;
    createTestData(elements, numOfElements);
    
    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }

    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);

    for(int index = 0; index < numOfElements; index++) {
        signed int elementVal = *(elementArray + index);

        int valFoundAt = search(hashTable, elementVal);

        unsigned int pos = getHashPos(elementVal, currentHashTableSize);
        unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, elementVal);
        assert(valFoundAt == probedPos);
    }
    assert(currentHashTableSize == 16384);
}

// Inserts 4096 new values to the hash table (can have duplicates) and search all 4096 values.
// This is to search duplicates and search through multiple groups (4096 boundary case and collisions).
void testSearch4096Vals() {
    printf("Searching 4096 values to the hash table: ");

    numOfElements = 4096;
    static signed int elements[4096];
    elementArray = elements;
    createTestData(elements, numOfElements);
    
    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }

    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);

    for(int index = 0; index < numOfElements; index++) {
        signed int elementVal = *(elementArray + index);

        int valFoundAt = search(hashTable, elementVal);

        unsigned int pos = getHashPos(elementVal, currentHashTableSize);
        unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, elementVal);
        assert(valFoundAt == probedPos);
    }
    assert(currentHashTableSize == 8192);
}

// Runs the test framework.
int main() {
    testFuncPtrDef testFuncDefs[4] = {
        &testSearch1NonExisting, &testSearch1Existing, &testSearch4098Vals, &testSearch4096Vals
    };
    runAllTests(testFuncDefs, 4);
    return 0;
}