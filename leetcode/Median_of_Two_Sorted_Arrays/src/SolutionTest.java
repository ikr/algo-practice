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
    public void medianEquivalentToTheControlImplementation() {
        int[] xs = new int[] {3, 5, 6, 6, 7, 8};
        assertEquals(Merge.median(xs), Solution.median(xs, 0, xs.length), 0.001);
    }

    @org.junit.Test
    public void bothEmpty() {
        assertEquals(-1.0, s.findMedianSortedArrays(new int[0], new int[0]), 0.001);
    }

    @org.junit.Test
    public void xs0ys2() {
        assertEquals(5.0, s.findMedianSortedArrays(new int[0], new int[]{4, 6}), 0.001);
    }

    @org.junit.Test
    public void xs1ys1() {
        assertEquals(6.5, s.findMedianSortedArrays(new int[] {6}, new int[]{7}), 0.001);
    }

    @org.junit.Test
    public void xs1ysOdd() {
        assertEquals(11.0, s.findMedianSortedArrays(new int[] {5}, new int[]{5, 10, 12, 15, 20}), 0.001);
    }

    @org.junit.Test
    public void xs1ysEven() {
        assertEquals(10.0, s.findMedianSortedArrays(new int[] {10}, new int[]{5, 10, 12, 15}), 0.001);
    }

    @org.junit.Test
    public void xs2ys2() {
        assertEquals(2.5, s.findMedianSortedArrays(new int[] {1, 3}, new int[]{2, 4}), 0.001);
    }

    @org.junit.Test
    public void xs2ysOdd() {
        assertEquals(12.0, s.findMedianSortedArrays(new int[] {2, 16}, new int[]{5, 10, 12, 15, 20}), 0.001);
    }

    @org.junit.Test
    public void xs2ysEven() {
        assertEquals(10.0, s.findMedianSortedArrays(new int[] {9, 10}, new int[]{5, 10, 12, 15}), 0.001);
    }
}
