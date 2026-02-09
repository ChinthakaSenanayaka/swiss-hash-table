import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class TestDataUtil {
    private static Random rand = new Random();

    public static List<Integer> genRandomInt(int numOfElements) {
        List<Integer> randomNums = new ArrayList<>();
        for(int counter = 0; counter < numOfElements; counter++) {
            randomNums.add(rand.nextInt(10000000));
        }
        return randomNums;
    }
}
