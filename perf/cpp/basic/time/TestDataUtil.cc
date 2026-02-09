#include <iostream>
#include <vector>

#include "TestDataUtil.h"

using namespace std;

vector<int> genRandomInts(int numOfElements)
{
    srand((unsigned) time(NULL));
    vector<int> randomNums = {};

    for (int counter = 0; counter < numOfElements; counter++) {
        randomNums.push_back(rand());
    }

	return randomNums;
}