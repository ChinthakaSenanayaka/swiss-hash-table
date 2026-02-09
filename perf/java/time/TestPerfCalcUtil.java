import java.util.logging.Logger;

public class TestPerfCalcUtil {

    private static long startTime;

    private static Logger logger;

    static void initTime(Logger log) {
        logger = log;
    }
    
    static void tearTime() {
        logger = null;
    }

    static void initEach() {
        startTime = 0l;
    }

    static void tearEach() {}

    static void setStartTime() {
        startTime = System.nanoTime();
    }
    
    private static long getTimeDiff() {
        return System.nanoTime() - startTime;
    }

    static void printTimeDiff(String testFileName, String testFileFuncName, String testFuncName) {
        logger.info(testFileName + " " + testFileFuncName + " " + testFuncName + 
                    ", time taken: " + getTimeDiff() + " nanosecs");
    }

}
