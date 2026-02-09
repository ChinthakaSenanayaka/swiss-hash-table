import time

startTime = None
logger = None

def initTime(log):
    global logger

    logger = log
    
def tearTime():
    global logger

    logger = None

def initEach():
    global startTime
    
    startTime = 0

def tearEach():
    pass

def setStartTime():
    global startTime

    startTime = time.time_ns()

def getTimeDiff():
    global startTime

    return time.time_ns() - startTime

def printTimeDiff(testFileName, testFileFuncName, testFuncName):
    global logger
    
    logger.info(f"{testFileName} {testFileFuncName} {testFuncName}, time taken: {getTimeDiff()} nanosecs")