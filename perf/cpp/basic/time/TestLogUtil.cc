#include <iostream>
#include <fstream>
#include <string>

#include "TestLogUtil.h"

using namespace std;

fstream file;

void initTestLogger()
{
    file.open("./out/logs.txt", ios::app);
    if( !file.is_open())
        exit(1);
}

void printLog(string logText, bool printCout)
{
    if(printCout)
    {
        cout << logText << endl;
    }
    file << logText << endl;
}

void tearTestLogger()
{
    // file.close();
}