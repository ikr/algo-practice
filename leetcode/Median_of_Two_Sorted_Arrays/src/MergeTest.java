import static org.junit.Assert.*;

public class MergeTest {
    @org.junit.Test
    public void mergeOfEmpties() {
        assertArrayEquals(new int[0], Merge.merge(new int[0], new int[0]));
    }

    @org.junit.Test
    public void mergeOfEmptyWithNonEmpty() {
        assertArrayEquals(new int[] {1, 2, 3}, Merge.merge(new int[0], new int[] {1, 2, 3}));
    }

    @org.junit.Test
    public void mergeOfNonEmptyWithEmpty() {
        assertArrayEquals(new int[] {1, 2, 3}, Merge.merge(new int[] {1, 2, 3}, new int[0]));
    }

    @org.junit.Test
    public void mergeOfNonEmpties() {
        assertArrayEquals(new int[] {1, 2, 3, 4}, Merge.merge(new int[] {2, 4}, new int[] {1, 3}));
    }

    @org.junit.Test
    public void medianOfEmpty() {
        assertEquals(-1.0, Merge.median(new int[0]), 0.001);
    }

    @org.junit.Test
    public void medianOfOneElement() {
        assertEquals(13.0, Merge.median(new int[] {13}), 0.001);
    }

    @org.junit.Test
    public void medianOfEvenElements() {
        assertEquals(1.5, Merge.median(new int[] {1, 2}), 0.001);
    }

    @org.junit.Test
    public void medianOfOddElements() {
        assertEquals(2.0, Merge.median(new int[] {1, 2, 3}), 0.001);
    }
}
