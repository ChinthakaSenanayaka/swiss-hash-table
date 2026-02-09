/**
 * Holds Test functions for hash table delete functionality.
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
    strncpy(testFileName, "TestDelete", 20);
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

void testDelete1() {
    insert(hashTable, *elementArray);

    signed int elementVal = *elementArray;
    setStartTime();
    delete(hashTable, elementVal);
    printTimeDiff(testFileName, "testDelete1", "delete");

    printf("--- Deleting an existing value to the hash table: ");
}

void testDelete81922() {
    numOfElements = 1000000;
    static signed int elements[1000000];
    elementArray = elements;
    createTestData(elements, numOfElements);
    
    for(int counter = 0; counter < numOfElements; counter++) {
        signed int *elementValPtr = elementArray + counter;
        insert(hashTable, *elementValPtr);
    }

    for(int index = 0; index < numOfElements; index++) {

        signed int elementVal = *(elementArray + index);
        
        setStartTime();
        delete(hashTable, elementVal);
        printTimeDiff(testFileName, "testDelete81922", "delete");
    }

    printf("--- Deleting 81922 values to the hash table: ");
}

// Runs the test framework.
int main() {
    testFuncPtrDef testFuncDefs[2] = {
        &testDelete1, &testDelete81922
    };
    runAllTests(testFuncDefs, 2);
    return 0;
}