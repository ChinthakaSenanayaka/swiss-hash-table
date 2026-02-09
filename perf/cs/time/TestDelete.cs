using System;
using System.Collections;

namespace cs
{
    class TestDelete
    {
        private TestDataUtil testDataUtil;

        private Hashtable ht;

        List<int> randomNums;

        private string testFileName;

        private void beforeAll() {
            testDataUtil = new TestDataUtil();

            testFileName = "TestDelete";
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

        private void testDelete1() {
            beforeEach();

            int numOfElements = 1;
            randomNums = testDataUtil.genRandomInts(numOfElements);
            for(int counter = 0; counter < numOfElements; counter++) {
                try {ht.Add(randomNums[counter], randomNums[counter]);} catch {}
            }

            for(int counter = 0; counter < numOfElements; counter++) {
                int elementVal = randomNums[counter];
                TestPerfCalcUtil.setStartTime();
                ht.Remove(elementVal);
                TestPerfCalcUtil.printTimeDiff(testFileName, "testDelete1", "delete");
            }

            afterEach();
        }

        private void testDelete81922() {
            beforeEach();

            int numOfElements = 1000000;
            randomNums = testDataUtil.genRandomInts(numOfElements);
            for(int counter = 0; counter < numOfElements; counter++) {
                try {ht.Add(randomNums[counter], randomNums[counter]);} catch {}
            }

            for(int counter = 0; counter < numOfElements; counter++) {
                int elementVal = randomNums[counter];
                TestPerfCalcUtil.setStartTime();
                ht.Remove(elementVal);
                TestPerfCalcUtil.printTimeDiff(testFileName, "testDelete81922", "delete");
            }

            afterEach();
        }

        public void testStart() {
            beforeAll();

            testDelete1();
            testDelete81922();

            afterAll();
        }
    }
}
