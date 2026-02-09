#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

#include "TestDataUtil.h"

#include "TestLogUtil.h"
#include "TestPerfCalcUtil.h"

using namespace std;

unordered_map<int, int> ht;

vector<int> randomNums;
vector<int> randomNums2;

string testFileName;

void beforeAll()
{
    initTestLogger();
    testFileName = "TestInsert";

    initTime();
}

void afterAll()
{
    tearTestLogger();
    tearTime();

    printLog("======Test Insert Done=======", true);
}

void beforeEach()
{
    ht = {};
}
void afterEach()
{
    // for (auto x : ht)
    //     cout << "key: " << x.first << ", value: " << 
    //         x.second << endl;
}

void testInsert1()
{
    beforeEach();

    int numOfElements = 1;
    randomNums = genRandomInts(numOfElements);
    for(int counter = 0; counter < numOfElements; counter++)
    {
        int elementVal = randomNums[counter];
        setStartTime();
        ht[elementVal] = elementVal;
        printTimeDiff(testFileName, "testInsert1", "insert");
    }

    afterEach();
}

void testInsert81922()
{
    beforeEach();

    int numOfElements = 1000000;
    randomNums = genRandomInts(numOfElements);
    for(int counter = 0; counter < numOfElements; counter++)
    {
        int elementVal = randomNums[counter];
        setStartTime();
        ht[elementVal] = elementVal;
        printTimeDiff(testFileName, "testInsert81922", "insert");
    }

    afterEach();
}

int main(int argc, const char **argv) 
{
    beforeAll();

    testInsert1();
    testInsert81922();

    afterAll();

    return 0;
}