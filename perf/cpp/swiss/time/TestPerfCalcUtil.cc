#include <iostream>
#include <chrono>
#include <string>

#include "TestPerfCalcUtil.h"

#include "TestLogUtil.h"

using namespace std;
using namespace chrono;

time_point<system_clock> startTime;

void initTime()
{

}

void tearTime()
{

}

void setStartTime()
{
    startTime = high_resolution_clock::now();
}

long long getTimeDiff()
{
    time_point<system_clock> endTime = high_resolution_clock::now();
    return duration_cast<nanoseconds>(endTime-startTime).count();
}

void printTimeDiff(string testFileName, string testFileFuncName, string testFuncName) {
    printLog(testFileName + " " + testFileFuncName + " " + testFuncName + 
                ", time taken: " + to_string(getTimeDiff()) + " nanosecs");
}