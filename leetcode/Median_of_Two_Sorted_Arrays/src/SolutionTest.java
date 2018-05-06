import static org.junit.Assert.*;

public class SolutionTest {
    private Solution s = new Solution();

    @org.junit.Test
    public void medianOfEmpty() {
        assertEquals(-1.0, Solution.median(new int[]{1, 2, 3}, 1, 1), 0.001);
    }

    @org.junit.Test
    public void medianOfOneElement() {
        assertEquals(3.0, Solution.median(new int[] {1, 2, 3}, 2, 3), 0.001);
    }

    @org.junit.Test
    public void medianOfEvenElements() {
        assertEquals(1.5, Solution.median(new int[] {1, 2, 3, 4}, 0, 2), 0.001);
    }

    @org.junit.Test
    public void medianOfOddElements() {
        assertEquals(3.0, Solution.median(new int[] {1, 2, 3, 4}, 1, 4), 0.001);
    }

    @org.junit.Test
    public void equivalentToTheControlImplementation() {
        int[] xs = new int[] {3, 5, 6, 6, 7, 8};
        assertEquals(Merge.median(xs), Solution.median(xs, 0, xs.length), 0.001);
    }

    @org.junit.Test
    public void bothEmpty() {
        assertEquals(-1.0, s.findMedianSortedArrays(new int[0], new int[0]), 0.001);
    }

    @org.junit.Test
    public void xs0ys2() {

    }
}
