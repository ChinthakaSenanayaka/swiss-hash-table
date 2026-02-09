using System;
using System.Collections;

namespace cs
{
    class TestSearch
    {
        private TestDataUtil testDataUtil;

        private Hashtable ht;

        List<int> randomNums;

        private string testFileName;

        private void beforeAll() {
            testDataUtil = new TestDataUtil();

            testFileName = "TestSearch";
        }

        private void afterAll() {
            testDataUtil = null;

            testFileName = null;
        }

        private void beforeEach() {
            ht = new Hashtable();

            TestPerfCalcUtil.initTime();
        }

        private void afterEach() {
            // foreach(var key in ht.Keys) {
            //     Console.WriteLine("{0} and {1}", key,
            //                     ht[key]);
            // }

            ht = null;
            randomNums = null;

            TestPerfCalcUtil.tearTime();
        }

        private void testSearch1() {
            beforeEach();

            int numOfElements = 1;
            randomNums = testDataUtil.genRandomInts(numOfElements);
            for(int counter = 0; counter < numOfElements; counter++) {
                try {ht.Add(randomNums[counter], randomNums[counter]);} catch {}
            }

            int elementVal = randomNums[0];
            TestPerfCalcUtil.setStartTime();
            ht.ContainsKey(elementVal);
            TestPerfCalcUtil.printTimeDiff(testFileName, "testSearch1", "search");

            afterEach();
        }
        
        private void testSearch81922() {
            beforeEach();

            int numOfElements = 1000000;
            randomNums = testDataUtil.genRandomInts(numOfElements);
            for(int counter = 0; counter < numOfElements; counter++) {
                try {ht.Add(randomNums[counter], randomNums[counter]);} catch {}
            }
            
            for (int counter = 0; counter < numOfElements; counter++) {

                int elementVal = randomNums[counter];
                TestPerfCalcUtil.setStartTime();
                ht.ContainsKey(elementVal);
                TestPerfCalcUtil.printTimeDiff(testFileName, "testSearch81922", "search");
            }

            afterEach();
        }

        public void testStart() {
            beforeAll();

            testSearch1();
            testSearch81922();

            afterAll();
        }
    }
}
