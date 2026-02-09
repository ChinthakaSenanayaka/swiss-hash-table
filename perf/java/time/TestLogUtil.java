import java.util.logging.FileHandler;
import java.util.logging.SimpleFormatter;
import java.util.logging.Logger;

import java.io.IOException;

public class TestLogUtil {

    private static Logger logger;

    public static Logger getTestLogger() {
        logger = Logger.getLogger("Test Java HT");  
        FileHandler fh;  

        try {  
            
            fh = new FileHandler("./build/perf/java/time/out/logs.txt", true);  
            logger.addHandler(fh);
            SimpleFormatter formatter = new SimpleFormatter();  
            fh.setFormatter(formatter);   

        } catch (SecurityException e) {  
            e.printStackTrace();  
        } catch (IOException e) {  
            e.printStackTrace();  
        } 

        return logger;
    }
    
}
