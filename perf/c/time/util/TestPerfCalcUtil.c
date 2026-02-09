/**
 * Utility performance measuring functions.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include <time.h>

#ifndef __TestPerfCalcUtil_C__
#define __TestPerfCalcUtil_C__

struct timespec startTime, endTime;

void initTime() {
    startTime.tv_sec=0;
    startTime.tv_nsec=0;
    endTime.tv_sec=0;
    endTime.tv_nsec=0;
}

void tearTime() {}

void setStartTime() {
    clock_gettime(CLOCK_MONOTONIC, &startTime);
}

long getTimeDiff() {
    clock_gettime(CLOCK_MONOTONIC, &endTime);
    return ((long)(endTime.tv_sec - startTime.tv_sec) * 1000000000) + 
        (endTime.tv_nsec - startTime.tv_nsec);
}

void printTimeDiff(char* testFileName, char* testFileFuncName, char* testFuncName) {
    printf("%s %s %s, time taken: %ld nanosecs\n", testFileName, testFileFuncName, testFuncName, getTimeDiff());
}

#endif