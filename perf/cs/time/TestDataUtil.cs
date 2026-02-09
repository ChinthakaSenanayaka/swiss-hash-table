using System;
using System.Collections;

namespace cs
{   
    class TestDataUtil
    {
        private readonly Random random = new Random();

        public List<int> genRandomInts(int numOfElements) {
            List<int> randomNums = new List<int>();
            
            for(int counter = 0; counter < numOfElements; counter++) {
                randomNums.Add(random.Next(-2147483648, 2147483647));
            }

            return randomNums;
        }
    }
}
