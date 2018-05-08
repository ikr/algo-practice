import static org.junit.Assert.*;
import org.junit.Test;

public class SolutionTest {
    @Test
    public void onesCount1023() {
        assertEquals(10, Solution.onesCount(1023));
    }

    @Test
    public void onesCount1024() {
        assertEquals(1, Solution.onesCount(1024));
    }

    @Test
    public void onesCount1025() {
        assertEquals(2, Solution.onesCount(1025));
    }
}