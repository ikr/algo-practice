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
}