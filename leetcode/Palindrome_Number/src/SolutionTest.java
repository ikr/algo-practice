import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;

import static org.junit.Assert.*;

public class SolutionTest {
    private Solution s;

    @Before
    public void setUp() throws Exception {
        s = new Solution();
    }

    @Test
    public void isPalindrome() {
        assertTrue(s.isPalindrome(121));
    }

    @Test
    public void isPalindrome0() {
        assertTrue(s.isPalindrome(0));
    }

    @Test
    public void digits() {
        ArrayList<Integer> ds = s.digits(121);
        assertEquals(3, ds.size());
        assertEquals(1, ds.get(0).intValue());
    }
}
