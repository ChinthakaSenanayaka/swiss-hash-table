#include <iostream>
#include <vector>
#include <string>

#include "absl/container/flat_hash_map.h"

#include "TestDataUtil.h"

#include "TestLogUtil.h"
#include "TestPerfCalcUtil.h"

using namespace std;
using namespace absl;

flat_hash_map<int, int> ht;

vector<int> randomNums;
vector<int> randomNums2;

string testFileName;

void beforeAll()
{
    initTestLogger();
    testFileName = "TestSearch";

    initTime();
}
void afterAll()
{
    tearTestLogger();
    tearTime();

    printLog("======Test Search Done=======", true);
}

void beforeEach() {
    ht = {};
}
void afterEach() {
    // for (auto x : ht)
    //     cout << "key: " << x.first << ", value: " << 
    //         x.second << endl;
}

void testSearch1()
{
    beforeEach();

    int numOfElements = 1;
    randomNums = genRandomInts(numOfElements);
    for(int counter = 0; counter < numOfElements; counter++)
    {
        ht[randomNums[counter]] = randomNums[counter];
    }

    for(int counter = 0; counter < numOfElements; counter++)
    {
        int elementVal = randomNums[counter];
        setStartTime();
        ht.at(elementVal);
        printTimeDiff(testFileName, "testSearch1", "search");
    }

    afterEach();
}

void testSearch81922()
{
    beforeEach();

    int numOfElements = 1000000;
    randomNums = genRandomInts(numOfElements);
    for(int counter = 0; counter < numOfElements; counter++)
    {
        ht[randomNums[counter]] = randomNums[counter];
    }

    for(int counter = 0; counter < numOfElements; counter++)
    {
        int elementVal = randomNums[counter];
        setStartTime();
        ht.at(elementVal);
        printTimeDiff(testFileName, "testSearch81922", "search");
    }

    afterEach();
}

int main(int argc, const char **argv) 
{
    beforeAll();

    testSearch1();
    testSearch81922();

    afterAll();

    return 0;
}