#include <string>

#pragma once

using namespace std;

void initTestLogger();
void printLog(string logText, bool printCout=false);
void tearTestLogger();