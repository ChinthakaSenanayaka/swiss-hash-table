#include <string>

#pragma once

using namespace std;

void initTime();
void tearTime();

void setStartTime();
long long getTimeDiff();
void printTimeDiff(string testFileName, string testFileFuncName, string testFuncName);