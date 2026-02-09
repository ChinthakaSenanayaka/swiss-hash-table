using System;
using System.Collections;

namespace cs
{
    class TestInsert
    {
        private TestDataUtil testDataUtil;

        private Hashtable ht;

        List<int> randomNums;

        private string testFileName;

        private void beforeAll() {
            testDataUtil = new TestDataUtil();

            testFileName = "TestInsert";
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

        private void testInsert1() {
            beforeEach();

            int numOfElements = 1;
            randomNums = testDataUtil.genRandomInts(numOfElements);
            for(int counter = 0; counter < numOfElements; counter++) {
                try
                {
                    int elementVal = randomNums[counter];
                    TestPerfCalcUtil.setStartTime();
                    ht[elementVal] = elementVal;
                    TestPerfCalcUtil.printTimeDiff(testFileName, "testInsert1", "insert");
                }
                catch {TestPerfCalcUtil.printTimeDiff(testFileName, "testInsert1", "insert");}
            }

            afterEach();
        }

        private void testInsert81922() {
            beforeEach();

            int numOfElements = 1000000;
            randomNums = testDataUtil.genRandomInts(numOfElements);
            for(int counter = 0; counter < numOfElements; counter++) {
                try
                {
                    int elementVal = randomNums[counter];
                    TestPerfCalcUtil.setStartTime();
                    ht[randomNums[counter]] = randomNums[counter];
                    TestPerfCalcUtil.printTimeDiff(testFileName, "testInsert81922", "insert");
                }
                catch {TestPerfCalcUtil.printTimeDiff(testFileName, "testInsert81922", "insert");}
            }

            afterEach();
        }

        public void testStart() {
            beforeAll();

            testInsert1();
            testInsert81922();

            afterAll();
        }
    }
}
