/**
 * Holds Test functions for hash table insert functionality.
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
unsigned int numOfElements = 1;
signed int *elementArray = NULL;

void beforeAll() {}

void beforeEach() {
    hashTable = createHashTable(0);
    // printHashTable(hashTable);

    static signed int elements[1];
    elementArray = elements;
    createTestData(elements, numOfElements);
}

void afterEach() {
    // printHashTable(hashTable);
    printf("Success\n");
    
    hashTable = NULL;
    elementArray = NULL;
}

void afterAll() {}

// Inserts 1 new value to the hash table
void testInsert1NonExisting() {
    printf("Inserting a non-existng value to the hash table: ");

    insert(hashTable, *elementArray);

    int valFoundAt = search(hashTable, *elementArray);
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    unsigned int pos = getHashPos(*elementArray, currentHashTableSize);
    unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, *elementArray);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 16);
}

// Inserts 1 existing value to the hash table. This is collision handling test.
void testInsert1Existing() {
    printf("Inserting an existng value to the hash table: ");

    insert(hashTable, *elementArray);

    // insert the same value again
    insert(hashTable, *elementArray);

    int valFoundAt = search(hashTable, *elementArray);
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    unsigned int pos = getHashPos(*elementArray, currentHashTableSize);
    unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, *elementArray);
    assert(valFoundAt == probedPos);
}

// Inserts 10 new values to the hash table
void testInsert10NonExisting() {
    printf("Inserting 10 non-existng value to the hash table: ");

    numOfElements = 10;
    static signed int elements[10];
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
}

// Inserts 32 new values to the hash table. This is hash table size boundary case 32.
void testInsert32NonExisting() {
    printf("Inserting 32 non-existng value to the hash table: ");

    numOfElements = 32;
    static signed int elements[32];
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
}

// Inserts 33 new values to the hash table. This is hash table size boundary case 32 and 1 additional element.
void testInsert33NonExisting() {
    printf("Inserting 33 non-existng value to the hash table: ");

    numOfElements = 33;
    static signed int elements[33];
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
}

// Inserts 4098 new values to the hash table. This is hash table size boundary case 4096 and 2 additional element.
void testInsert4098Vals() {
    printf("Inserting 4098 values to the hash table: ");

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

// Inserts 4096 new values to the hash table. This is hash table size boundary case 4096.
void testInsert4096Vals() {
    printf("Inserting 4096 values to the hash table: ");

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
    testFuncPtrDef testFuncDefs[7] = {
        &testInsert1NonExisting, &testInsert1Existing, &testInsert10NonExisting, &testInsert32NonExisting,
        &testInsert33NonExisting, &testInsert4098Vals, &testInsert4096Vals
    };
    runAllTests(testFuncDefs, 7);
    return 0;
}