from TestDataUtil import *

from TestLogUtil import *
from TestPerfCalcUtil import *

ht = {}

logger = None
testFileName = None;

def beforeAll():
    global logger, testFileName

    logger = getTestLogger()
    testFileName = "TestSearch"

    initTime(logger);

def afterAll():
    global logger, testFileName

    logger = None
    testFileName = None

    tearTime()

def beforeEach():
    global ht
    ht = {}

    initEach()

def afterEach():
    global ht, logger

    # logger.info(f"Hashtable Elements: {ht}")
    ht = {}

    tearEach()

def testSearch1():
    global ht

    beforeEach()

    randomNums = genRandomInt(1)

    for randomNum in randomNums:
        ht[randomNum] = randomNum

    for randomNum in randomNums:
        setStartTime()
        ht.get(randomNum)
        printTimeDiff(testFileName, 
                      "testSearch1", "search")

    afterEach()

def testSearch81922():
    global ht

    beforeEach()

    randomNums = genRandomInt(1000000)

    for randomNum in randomNums:
        ht[randomNum] = randomNum
    
    for randomNum in randomNums:
        setStartTime()
        ht.get(randomNum)
        printTimeDiff(testFileName, 
                      "testSearch81922", "search")

    afterEach()

def main():
    beforeAll()

    testSearch1()
    testSearch81922()

    afterAll()

main()