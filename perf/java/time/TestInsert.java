import java.util.Hashtable;
import java.util.List;

import java.util.logging.Logger;

public class TestInsert {

    private static Hashtable<Integer, Integer> ht = null;

    private static Logger logger;

    private static String testFileName;

    private static void beforeAll() {
        logger = TestLogUtil.getTestLogger();
        testFileName = "TestInsert";

        TestPerfCalcUtil.initTime(logger);
    }
    private static void afterAll() {
        testFileName = null;

        TestPerfCalcUtil.tearTime();
        logger = null;
    }

    private static void beforeEach() {
        ht = new Hashtable<>();

        TestPerfCalcUtil.initEach();
    }
    private static void afterEach() {
        // logger.info("Hashtable Elements: " + ht);

        ht = null;

        TestPerfCalcUtil.tearEach();
    }

    public static void main(String[] args) {

        beforeAll();

        testInsert1();
        testInsert81922();

        afterAll();
    }

    private static void testInsert1() {
        beforeEach();
        
        List<Integer> randomNums = TestDataUtil.genRandomInt(1);

        for(int randomNum : randomNums) {
            TestPerfCalcUtil.setStartTime();
            ht.put(randomNum, randomNum);
            TestPerfCalcUtil.printTimeDiff(testFileName, 
                "testInsert1", "insert");
        }

        afterEach();
    }

    private static void testInsert81922() {
        beforeEach();
        
        List<Integer> randomNums = TestDataUtil.genRandomInt(1000000);

        for(int randomNum : randomNums) {
            TestPerfCalcUtil.setStartTime();
            ht.put(randomNum, randomNum);
            TestPerfCalcUtil.printTimeDiff(testFileName, 
                "testInsert81922", "insert");
        }

        afterEach();
    }
}