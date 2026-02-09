from TestDataUtil import *

from TestLogUtil import *
from TestPerfCalcUtil import *

ht = {}

logger = None
testFileName = None;

def beforeAll():
    global logger, testFileName

    logger = getTestLogger()
    testFileName = "TestInsert"

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

def testInsert1():
    global ht, testFileName

    beforeEach()

    randomNums = genRandomInt(1)

    for randomNum in randomNums:
        setStartTime()
        ht[randomNum] = randomNum
        printTimeDiff(testFileName, 
                      "testInsert1", "insert")

    afterEach()

def testInsert81922():
    global ht, testFileName

    beforeEach()

    randomNums = genRandomInt(1000000)

    for randomNum in randomNums:
        setStartTime()
        ht[randomNum] = randomNum
        printTimeDiff(testFileName, 
                      "testInsert81922", "insert")

    afterEach()

def main():
    beforeAll()

    testInsert1()
    testInsert81922()

    afterAll()

main()