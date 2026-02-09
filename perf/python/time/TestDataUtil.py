import random

def genRandomInt(numOfElements: int):
    randomNums = []

    for counter in range(numOfElements):
        randomNums.append(random.randrange(-2147483648, 2147483647, 1))
    
    return randomNums