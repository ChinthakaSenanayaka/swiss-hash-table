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
    testFileName = "TestDelete";

    initTime();
}

void afterAll()
{
    tearTestLogger();
    tearTime();

    printLog("======Test Delete Done=======", true);
}

void beforeEach() {
    ht = {};
}
void afterEach() {
    // for (auto x : ht)
    //     cout << "key: " << x.first << ", value: " << 
    //         x.second << endl;
}

void testDelete1()
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
        try {
            int elementVal = randomNums[counter];
            setStartTime();
            ht.erase(elementVal);
            printTimeDiff(testFileName, "testDelete1", "delete");
        } catch (const exception &e) {}
    }

    afterEach();
}

void testDelete81922()
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
        try {
            int elementVal = randomNums[counter];
            setStartTime();
            ht.erase(elementVal);
            printTimeDiff(testFileName, "testDelete81922", "delete");
        } catch (const exception &e) {}
    }

    afterEach();
}

int main(int argc, const char **argv) 
{
    beforeAll();

    testDelete1();
    testDelete81922();

    afterAll();

    return 0;
}