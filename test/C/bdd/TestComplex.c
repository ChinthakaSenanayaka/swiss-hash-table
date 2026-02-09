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

// 1 insert -> 1 search (existing) -> 1 del -> 1 search (non-existing) -> 1 insert -> 1 search (existing).
void test1ElementAllOps() {
    printf("All ops for 1 element: ");

    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }
    int valFoundAt = search(hashTable, *elementArray);
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    unsigned int pos = getHashPos(*elementArray, currentHashTableSize);
    unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, *elementArray);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 16);

    delete(hashTable, *elementArray);
    valFoundAt = search(hashTable, *elementArray);

    currentHashTableSize = getCurrentHashTableSize(hashTable);
    pos = getHashPos(*elementArray, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, *elementArray);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 16);

    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }

    valFoundAt = search(hashTable, *elementArray);
    currentHashTableSize = getCurrentHashTableSize(hashTable);
    pos = getHashPos(*elementArray, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, *elementArray);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 16);
}

// 32 inserts (16*2 expand, , collisions and duplicates) -> 1 search (1st group value search, collisions and duplicates) ->
// 1 search (2nd group value search, collisions and duplicates) -> 
// 4064 insert (4096-32 expand, collisions and duplicates) -> 1 search (4th group value search)
void testAllOpsWithExpandHTbl() {
    printf("All ops with expand table: ");

    // 16*2 insert and expand
    numOfElements = 32;
    static signed int elements32[32];
    elementArray = elements32;
    createTestData(elements32, numOfElements);

    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }

    unsigned int currentNumOfElements = getNumOfElements(hashTable);
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    signed int searchValGrp1, searchValGrp2;
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 1st group value to search
        if(getHashPosGroup(elements32[counter], currentHashTableSize) == 0) {
            searchValGrp1 = elements32[counter];
            break;
        }
    }
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 2nd group value to search
        if(getHashPosGroup(elements32[counter], currentHashTableSize) == 1) {
            searchValGrp2 = elements32[counter];
            break;
        }
    }

    int valFoundAt = search(hashTable, searchValGrp1);
    unsigned int pos = getHashPos(searchValGrp1, currentHashTableSize);
    unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp1);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 64);
    
    valFoundAt = search(hashTable, searchValGrp2);
    pos = getHashPos(searchValGrp2, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp2);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 64);

    // 4096-32=4064 inserts and expand
    numOfElements = 4064;
    static signed int elements4064[4064];
    elementArray = elements4064;
    createTestData(elements4064, numOfElements);

    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }

    currentHashTableSize = getCurrentHashTableSize(hashTable);
    signed int searchValGrp4;
    currentNumOfElements = getNumOfElements(hashTable);
    for(int counter = 0; counter < currentNumOfElements; counter++) {
        // get 4th group value to search
        if(getHashPosGroup(elements4064[counter], currentHashTableSize) == 3) {
            searchValGrp4 = elements4064[counter];
            break;
        }
    }

    valFoundAt = search(hashTable, searchValGrp4);
    pos = getHashPos(searchValGrp4, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp4);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 8192);
    assert(currentNumOfElements == 4096);
}

// 4100 (4096+4) inserts -> 1 search (4th group value search) -> 1 search (7th group value search) ->
// 2015 (4100-2015=2085 shrink & 2085>2048) delete -> 1 search (2nd group value search)
void testAllOpsWithShrinkHTbl() {
    printf("All ops with shrink table: ");

    // 4096+4 inserts and expand
    numOfElements = 4100;
    static signed int elements4100[4100];
    elementArray = elements4100;
    createTestData(elements4100, numOfElements);

    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }

    unsigned int currentNumOfElements = getNumOfElements(hashTable);
    unsigned int currentDelNumOfElements = getDelNumOfElements(hashTable);
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    signed int searchValGrp4, searchValGrp7;
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 4th group value to search
        if(getHashPosGroup(elements4100[counter], currentHashTableSize) == 3) {
            searchValGrp4 = elements4100[counter];
            break;
        }
    }
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 7th group value to search
        if(getHashPosGroup(elements4100[counter], currentHashTableSize) == 6) {
            searchValGrp7 = elements4100[counter];
            break;
        }
    }
    
    int valFoundAt = search(hashTable, searchValGrp4);
    unsigned int pos = getHashPos(searchValGrp4, currentHashTableSize);
    unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp4);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 16384);
    
    valFoundAt = search(hashTable, searchValGrp7);
    pos = getHashPos(searchValGrp7, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp7);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 16384);

    // 4100-2015=2085 shrink
    numOfElements = 2085;
    static signed int elements2085[2085];
    elementArray = elements2085;

    for(int counter = 0; counter < 2015; counter++) {
        signed int toBeDeleted = elements4100[counter];

        unsigned int isDeleted = delete(hashTable, toBeDeleted);
        assert(isDeleted == 1);
    }

    for(int counter = 2015; counter < 4100; counter++) {
        signed int toBeRemained = elements4100[counter];
        elements2085[counter-2015] = toBeRemained;
    }

    currentHashTableSize = getCurrentHashTableSize(hashTable);
    signed int searchValGrp2;
    currentNumOfElements = getNumOfElements(hashTable);
    currentDelNumOfElements = getDelNumOfElements(hashTable);
    for(int counter = 0; counter < currentNumOfElements; counter++) {
        // get 2nd group value to search
        if(getHashPosGroup(elements2085[counter], currentHashTableSize) == 1) {
            searchValGrp4 = elements2085[counter];
            break;
        }
    }

    valFoundAt = search(hashTable, searchValGrp2);
    pos = getHashPos(searchValGrp2, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp2);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 8192);
    assert(currentNumOfElements-currentDelNumOfElements == 2085);
}

// 4100 insert (4096+4=4100) -> 1 search (4th group value search) -> 2015 delete (4100-2015=2085) ->
// 1 search (250th group value search) -> 4096 insert (2085+4096=6181 expand) -> 1 search (500th group value search)
void testAllOpsWithExpandAndShrinkHTbl() {
    printf("All ops with expand and shrink table: ");

    // 4100 insert
    numOfElements = 4100;
    static signed int elements4100[4100];
    elementArray = elements4100;
    createTestData(elements4100, numOfElements);

    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }
    
    unsigned int currentNumOfElements = getNumOfElements(hashTable);
    unsigned int currentDelNumOfElements = getDelNumOfElements(hashTable);
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);

    // 4th group search
    signed int searchValGrp4;
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 4th group value to search
        if(getHashPosGroup(elements4100[counter], currentHashTableSize) == 3) {
            searchValGrp4 = elements4100[counter];
            break;
        }
    }

    int valFoundAt = search(hashTable, searchValGrp4);
    unsigned int pos = getHashPos(searchValGrp4, currentHashTableSize);
    unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp4);
    assert(valFoundAt == probedPos);
    assert(currentHashTableSize == 16384);

    // 4100-2015=2085 shrink
    numOfElements = 2085;
    static signed int elements2085[2085];
    elementArray = elements2085;

    for(int counter = 0; counter < 2015; counter++) {
        signed int toBeDeleted = elements4100[counter];
        unsigned int isDeleted = delete(hashTable, toBeDeleted);
        assert(isDeleted == 1);
    }

    for(int counter = 2015; counter < 4100; counter++) {
        signed int toBeRemained = elements4100[counter];
        elements2085[counter-2015] = toBeRemained;
    }

    currentHashTableSize = getCurrentHashTableSize(hashTable);
    currentNumOfElements = getNumOfElements(hashTable);
    currentDelNumOfElements = getDelNumOfElements(hashTable);
    assert(currentHashTableSize == 8192);
    assert(currentNumOfElements-currentDelNumOfElements == 2085);

    // 250th group search
    signed int searchValGrp250;
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 250th group value to search
        if(getHashPosGroup(elements4100[counter], currentHashTableSize) == 249) {
            searchValGrp250 = elements4100[counter];
            break;
        }
    }

    valFoundAt = search(hashTable, searchValGrp250);
    pos = getHashPos(searchValGrp250, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp250);
    assert(valFoundAt == probedPos);

    // 4096 insert (2085+4096=6181 expand)
    numOfElements = 4096;
    static signed int elements4096[4096];
    elementArray = elements4096;
    createTestData(elements4096, numOfElements);

    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }

    currentNumOfElements = getNumOfElements(hashTable);
    currentHashTableSize = getCurrentHashTableSize(hashTable);
    assert(currentHashTableSize == 16384);
    assert(currentNumOfElements == 6181);

    // 500th group search
    signed int searchValGrp500;
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 7th group value to search
        if(getHashPosGroup(elements4096[counter], currentHashTableSize) == 499) {
            searchValGrp500 = elements4096[counter];
            break;
        }
    }

    valFoundAt = search(hashTable, searchValGrp500);
    
    pos = getHashPos(searchValGrp500, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp500);
    assert(valFoundAt == probedPos);
}

// This is to test complex test case with large group boundary numbers of elements.
// 4096 insert (256 groups) -> 1 search (200th group value search) -> 2048 delete (128 groups) ->
// 1 search (100th group value search) -> 4096 insert (2048+4096=6144, 384 groups expand) -> 
// 1 search (301st group value search) -> 6134 delete (10 elements, 2 groups) -> 1 search (1st group value search)
void testAllOpsWithExpandAndShrinkHTblGrpBoundary() {
    printf("All ops with expand and shrink table with boundary number of elements: ");
    
    // 4096 insert
    numOfElements = 4096;
    static signed int elements4096[4096];
    elementArray = elements4096;
    createTestData(elements4096, numOfElements);

    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }

    unsigned int currentNumOfElements = getNumOfElements(hashTable);
    unsigned int currentDelNumOfElements = getDelNumOfElements(hashTable);
    unsigned int currentHashTableSize = getCurrentHashTableSize(hashTable);
    assert(currentHashTableSize == 8192);
    assert(currentNumOfElements-currentDelNumOfElements == 4096);

    // 200th group search
    signed int searchValGrp200;
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 200th group value to search
        if(getHashPosGroup(elements4096[counter], currentHashTableSize) == 199) {
            searchValGrp200 = elements4096[counter];
            break;
        }
    }

    int valFoundAt = search(hashTable, searchValGrp200);
    unsigned int pos = getHashPos(searchValGrp200, currentHashTableSize);
    unsigned int probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp200);
    assert(valFoundAt == probedPos);

    // 2048 delete, shrink
    numOfElements = 2048;
    static signed int elements2048[2048];
    elementArray = elements2048;

    for(int counter = 0; counter < 2048; counter++) {
        signed int toBeDeleted = elements4096[counter];
        unsigned int isDeleted = delete(hashTable, toBeDeleted);
        assert(isDeleted == 1);
    }

    for(int counter = 2048; counter < 4096; counter++) {
        signed int toBeRemained = elements4096[counter];
        elements2048[counter-2048] = toBeRemained;
    }

    currentHashTableSize = getCurrentHashTableSize(hashTable);
    currentNumOfElements = getNumOfElements(hashTable);
    currentDelNumOfElements = getDelNumOfElements(hashTable);
    assert(currentHashTableSize == 4096);
    assert(currentNumOfElements-currentDelNumOfElements == 2048);

    // 100th group search
    signed int searchValGrp100;
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 100th group value to search
        if(getHashPosGroup(elements2048[counter], currentHashTableSize) == 99) {
            searchValGrp100 = elements2048[counter];
            break;
        }
    }

    valFoundAt = search(hashTable, searchValGrp100);
    pos = getHashPos(searchValGrp100, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp100);
    assert(valFoundAt == probedPos);

    // 4096 insert (2048+4096=6144)
    numOfElements = 4096;
    elementArray = elements4096;
    createTestData(elements4096, numOfElements);

    for(int index = 0; index < numOfElements; index++) {
        insert(hashTable, *(elementArray + index));
    }

    currentNumOfElements = getNumOfElements(hashTable);
    currentDelNumOfElements = getDelNumOfElements(hashTable);
    currentHashTableSize = getCurrentHashTableSize(hashTable);
    assert(currentHashTableSize == 16384);
    assert(currentNumOfElements-currentDelNumOfElements == 6144);

    // 301st group search
    signed int searchValGrp301;
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 301st group value to search
        if(getHashPosGroup(elements4096[counter], currentHashTableSize) == 300) {
            searchValGrp301 = elements4096[counter];
            break;
        }
    }

    valFoundAt = search(hashTable, searchValGrp301);
    pos = getHashPos(searchValGrp301, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp301);
    assert(valFoundAt == probedPos);

    // 6134 delete (6144+6134=10), shrink
    numOfElements = 10;
    static signed int elements10[10];
    elementArray = elements10;

    for(int counter = 0; counter < 2048; counter++) {
        signed int toBeDeleted = elements2048[counter];
        unsigned int isDeleted = delete(hashTable, toBeDeleted);
        assert(isDeleted == 1);
    }

    for(int counter = 0; counter < 4086; counter++) {
        signed int toBeDeleted = elements4096[counter];
        unsigned int isDeleted = delete(hashTable, toBeDeleted);
        assert(isDeleted == 1);
    }

    for(int counter = 4086; counter < 4096; counter++) {
        signed int toBeRemained = elements4096[counter];
        elements10[counter-4086] = toBeRemained;
    }

    currentHashTableSize = getCurrentHashTableSize(hashTable);
    currentNumOfElements = getNumOfElements(hashTable);
    currentDelNumOfElements = getDelNumOfElements(hashTable);
    assert(currentHashTableSize == 32);
    assert(currentNumOfElements-currentDelNumOfElements == 10);

    // 2nd group search
    signed int searchValGrp2;
    for(int counter = 0; counter < numOfElements; counter++) {
        // get 2nd group value to search
        if(getHashPosGroup(elements10[counter], currentHashTableSize) == 1) {
            searchValGrp2 = elements10[counter];
            break;
        }
    }

    valFoundAt = search(hashTable, searchValGrp2);
    pos = getHashPos(searchValGrp2, currentHashTableSize);
    probedPos = getHashTableValPosByBasePos(hashTable, pos, searchValGrp2);
    assert(valFoundAt == probedPos);
}

// Runs the test framework.
int main() {
    testFuncPtrDef testFuncDefs[5] = {
        &test1ElementAllOps, &testAllOpsWithExpandHTbl, &testAllOpsWithShrinkHTbl,
        &testAllOpsWithExpandAndShrinkHTbl, &testAllOpsWithExpandAndShrinkHTblGrpBoundary
    };
    runAllTests(testFuncDefs, 5);
    return 0;
}