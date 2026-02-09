import java.util.Hashtable;
import java.util.List;
import java.util.logging.Logger;

public class TestDelete {

    private static Hashtable<Integer, Integer> ht = null;

    private static Logger logger;

    private static String testFileName;

    private static void beforeAll() {
        logger = TestLogUtil.getTestLogger();
        testFileName = "TestDelete";

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

        testDelete1();
        testDelete81922();

        afterAll();
    }

    private static void testDelete1() {
        beforeEach();
        
        List<Integer> randomNums = TestDataUtil.genRandomInt(1);

        for(int randomNum : randomNums) {
            ht.put(randomNum, randomNum);
        }

        for(int randomNum : randomNums) {
            TestPerfCalcUtil.setStartTime();
            ht.remove(randomNum);
            TestPerfCalcUtil.printTimeDiff(testFileName, 
                "testDelete1", "delete");
        }

        afterEach();
    }
    
    private static void testDelete81922() {
        beforeEach();
        
        List<Integer> randomNums = TestDataUtil.genRandomInt(1000000);

        for(int randomNum : randomNums) {
            ht.put(randomNum, randomNum);
        }

        for(int randomNum : randomNums) {
            TestPerfCalcUtil.setStartTime();
            ht.remove(randomNum);
            TestPerfCalcUtil.printTimeDiff(testFileName, 
                "testDelete81922", "delete");
        }

        afterEach();
    }
}