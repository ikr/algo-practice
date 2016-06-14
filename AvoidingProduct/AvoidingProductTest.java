import junit.framework.TestCase;

public class AvoidingProductTest extends TestCase {
    public void testTripleConstructionFunction() {
        int[] expected = {1, 2, 3};
        assertTriplesEqual(expected, AvoidingProduct.triple(1, 2, 3));
    }

    public void testIsAllowedWithEmptyForbiddenReturnsTrue() {
        assertTrue(AvoidingProduct.isAllowed(42, new int[0]));
    }

    public void testIsAllowedForAForbiddenNumberIsFalse() {
        assertFalse(AvoidingProduct.isAllowed(2, AvoidingProduct.triple(1, 2, 3)));
    }

    public void testArrayMaximum() {
        assertEquals(3, AvoidingProduct.max(AvoidingProduct.triple(1, 2, 3)));
    }

    public void testArrayMinimum() {
        assertEquals(1, AvoidingProduct.min(AvoidingProduct.triple(1, 2, 3)));
    }

    public void testEmptyArrayMinimumIs1() {
        assertEquals(1, AvoidingProduct.min(new int[0]));
    }

    public void testUpperBound1() {
        assertEquals(4, AvoidingProduct.upperBound(AvoidingProduct.triple(1, 2, 3), 1));
    }

    public void testUpperBound2() {
        assertEquals(5, AvoidingProduct.upperBound(AvoidingProduct.triple(1, 2, 3), 4));
    }

    public void testLowerBound1() {
        assertEquals(1, AvoidingProduct.lowerBound(AvoidingProduct.triple(5, 6, 7)));
    }

    public void testLowerBound2() {
        assertEquals(3, AvoidingProduct.lowerBound(AvoidingProduct.triple(1, 2, 4)));
    }

    public void testLowerBound3() {
        assertEquals(4, AvoidingProduct.lowerBound(AvoidingProduct.triple(1, 2, 3)));
    }

    public void testLowerBound4() {
        int[] a = {1};
        assertEquals(2, AvoidingProduct.lowerBound(a));
    }

    public void testLowerBoundOfEmptyArrayIs1() {
        assertEquals(1, AvoidingProduct.lowerBound(new int[0]));
    }

    public void testNextTripleWithoutAnyForbidden1() {
        assertTriplesEqual(
                AvoidingProduct.triple(1, 1, 2),
                AvoidingProduct.nextTriple(AvoidingProduct.triple(1, 1, 1), new int[0], 1, 10)
        );
    }

    public void testNextTripleWithoutAnyForbiddenMagnitudeGain1() {
        assertTriplesEqual(
                AvoidingProduct.triple(1, 2, 1),
                AvoidingProduct.nextTriple(AvoidingProduct.triple(1, 1, 3), new int[0], 1, 3)
        );
    }

    public void testNextTripleWithoutAnyForbiddenMagnitudeGain2() {
        assertTriplesEqual(
                AvoidingProduct.triple(2, 1, 1),
                AvoidingProduct.nextTriple(AvoidingProduct.triple(1, 3, 3), new int[0], 1, 3)
        );
    }

    public void testNextTripleWithoutAnyForbiddenCommon() {
        assertTriplesEqual(
                AvoidingProduct.triple(3, 1, 1),
                AvoidingProduct.nextTriple(AvoidingProduct.triple(2, 5, 5), new int[0], 1, 5)
        );
    }

    public void testNextTripleWithoutAnyForbiddenMax() {
        assertTriplesEqual(
                AvoidingProduct.triple(3, 3, 3),
                AvoidingProduct.nextTriple(AvoidingProduct.triple(3, 3, 2), new int[0], 1, 3)
        );
    }

    public void testNextTripleWithoutAnyForbiddenBound() {
        assertTriplesEqual(
                AvoidingProduct.triple(3, 3, 3),
                AvoidingProduct.nextTriple(AvoidingProduct.triple(3, 3, 3), new int[0], 1, 3)
        );
    }

    public void testNextTripleFailedCase() {
        int[] a = {2, 4};

        assertTriplesEqual(
                AvoidingProduct.triple(1, 3, 1),
                AvoidingProduct.nextTriple(AvoidingProduct.triple(1, 1, 5), a, 1, 5)
        );
    }

    public void testNextAllowedWithoutAnyForbiddenIsIncrement() {
        assertEquals(5, AvoidingProduct.nextAllowed(4, new int[0]));
    }

    public void testNextAllowed1() {
        assertEquals(9, AvoidingProduct.nextAllowed(6, AvoidingProduct.triple(2, 7, 8)));
    }

    public void testNextAllowed2() {
        assertEquals(3, AvoidingProduct.nextAllowed(1, AvoidingProduct.triple(2, 7, 8)));
    }

    public void testNextAllowed3() {
        int[] a = {2, 4};
        assertEquals(6, AvoidingProduct.nextAllowed(5, a));
    }

    public void testGetTriple0() {
        int[] a = {2, 4};
        assertTriplesEqual(AvoidingProduct.triple(1, 1, 3), algorithm().getTriple(a, 4));
    }

    public void testGetTriple1() {
        int[] a = {1};
        assertTriplesEqual(AvoidingProduct.triple(2, 2, 2), algorithm().getTriple(a, 10));
    }

    public void testGetTriple2() {
        int[] a = {1, 2};
        assertTriplesEqual(AvoidingProduct.triple(3, 3, 3), algorithm().getTriple(a, 10));
    }

    public void testGetTriple3() {
        int[] a = {1, 3};
        assertTriplesEqual(AvoidingProduct.triple(2, 2, 2), algorithm().getTriple(a, 12));
    }

    public void testGetTriple4() {
        int[] a = {1, 3};
        assertTriplesEqual(AvoidingProduct.triple(2, 2, 4), algorithm().getTriple(a, 13));
    }

    public void testGetTriple5() {
        int[] a = {1, 15};
        assertTriplesEqual(AvoidingProduct.triple(2, 5, 9), algorithm().getTriple(a, 90));
    }

    private static AvoidingProduct algorithm() {
        return new AvoidingProduct();
    }

    private void assertTriplesEqual(int[] expected, int[] actual) {
        assertEquals(expected[0], actual[0]);
        assertEquals(expected[1], actual[1]);
        assertEquals(expected[2], actual[2]);
    }
}
