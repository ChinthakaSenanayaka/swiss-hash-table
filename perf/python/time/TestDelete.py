from TestDataUtil import *

from TestLogUtil import *
from TestPerfCalcUtil import *

ht = {}

logger = None
testFileName = None;

def beforeAll():
    global logger, testFileName

    logger = getTestLogger()
    testFileName = "TestDelete"

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

def testDelete1():
    global ht, testFileName

    beforeEach()

    randomNums = genRandomInt(1)

    for randomNum in randomNums:
        ht[randomNum] = randomNum

    for randomNum in randomNums:
        setStartTime()
        ht.pop(randomNum, -1)
        printTimeDiff(testFileName,
                      "testDelete1", "delete")

    afterEach()

def testDelete81922():
    global ht, testFileName

    beforeEach()

    randomNums = genRandomInt(1000000)

    for randomNum in randomNums:
        ht[randomNum] = randomNum
    
    for randomNum in randomNums:
        setStartTime()
        ht.pop(randomNum, -1)
        printTimeDiff(testFileName,
                      "testDelete81922", "delete")

    afterEach()

def main():
    beforeAll()

    testDelete1()
    testDelete81922()

    afterAll()

main()