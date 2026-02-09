/**
 * Holds Test functions for hash table insert functionality.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include <stdio.h>
#include <string.h>

#include "../../../test/C/bdd/util/TestFramework.h"
#include "../../../HashTable.h"

#include "../../../test/C/bdd/util/TestHashTableUtil.c"
#include "../../../test/C/bdd/util/TestDataUtil.c"

#include "./util/TestPerfCalcUtil.c"

HashTable *hashTable = NULL;
unsigned int numOfElements = 0;
signed int *elementArray = NULL;
char testFileName[20];

void beforeAll() {
    strncpy(testFileName, "TestInsert", 20);
}

void beforeEach() {
    hashTable = createHashTable(0);
    // printHashTable(hashTable);

    numOfElements = 1;
    static signed int elements[1];
    elementArray = elements;
    createTestData(elements, numOfElements);

    initTime();
}

void afterEach() {
    // printHashTable(hashTable);
    printf("Success ---\n");
    
    hashTable = NULL;
    elementArray = NULL;
    numOfElements = 0;

    tearTime();
}

void afterAll() {}

void testInsert1() {
    setStartTime();
    insert(hashTable, *elementArray);
    printTimeDiff(testFileName, "testInsert1", "insert");

    printf("--- Inserting a non-existng value to the hash table: ");
}

void testInsert81922() {
    numOfElements = 1000000;
    static signed int elements[1000000];
    elementArray = elements;
    createTestData(elements, numOfElements);
    

    for(int counter = 0; counter < numOfElements; counter++) {
        signed int *elementValPtr = elementArray + counter;
        setStartTime();
        insert(hashTable, *elementValPtr);
        printTimeDiff(testFileName, "testInsert81922", "insert");
    }

    printf("--- Inserting 81922 values to the hash table: ");
}

// Runs the test framework.
int main() {
    testFuncPtrDef testFuncDefs[2] = {
        &testInsert1, &testInsert81922
    };
    runAllTests(testFuncDefs, 2);
    return 0;
}