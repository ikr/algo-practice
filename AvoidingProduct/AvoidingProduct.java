public class AvoidingProduct {
    public int[] getTriple(int[] a, int n) {
        int lowerBound = lowerBound(a);
        int[] best = triple(lowerBound, lowerBound, lowerBound);

        int upperBound = upperBound(a, n);
        int[] current = triple(lowerBound, lowerBound, lowerBound);

        while (!triplesEqual(current, triple(upperBound, upperBound, upperBound))) {
            if (Math.abs(n - product(current)) < Math.abs(n - product(best))) {
                best = current;
            }

            current = nextTriple(current, a, lowerBound, upperBound);
        }

        return best;
    }

    public static int[] nextTriple(
    int[] currentTriple, int[] forbidden, int lowerBound, int upperBound) {
        if (triplesEqual(currentTriple, triple(upperBound, upperBound, upperBound))) {
            return currentTriple;
        }

        int x = currentTriple[0];
        int y = currentTriple[1];
        int z = nextAllowed(currentTriple[2], forbidden);

        if (z > upperBound) {
            y = nextAllowed(y, forbidden);
            z = lowerBound;
        }

        if (y > upperBound) {
            x = nextAllowed(x, forbidden);
            y = lowerBound;
        }

        return triple(x, y, z);
    }

    public static int upperBound(int[] a, int n) {
        return Math.max(max(a) + 1, n + 1);
    }

    public static int lowerBound(int[] a) {
        if (a.length == 0 || min(a) > 1) return 1;

        return nextAllowed(1, a);
    }

    public static int nextAllowed(int current, int[] forbidden) {
        if (forbidden.length == 0 || current >= max(forbidden)) {
            return current + 1;
        }

        for (int i = current + 1; i <= max(forbidden) + 1; i++) {
            if (isAllowed(i, forbidden)) return i;
        }

        return max(forbidden) + 1;
    }

    public static boolean isAllowed(int x, int[] forbidden) {
        for (int i : forbidden) {
            if (x == i) return false;
        }

        return true;
    }

    public static int max(int[] a) {
        int result = 0;

        for (int i : a) {
            if (i > result) {
                result = i;
            }
        }

        return result;
    }

    public static int min(int[] a) {
        if (a.length == 0) return 1;

        int result = a[0];

        for (int i : a) {
            if (i < result) {
                result = i;
            }
        }

        return result;
    }

    public static int[] triple(int x, int y, int z) {
        int[] result = {x, y, z};
        return result;
    }

    private static boolean triplesEqual(int[] t1, int[] t2) {
        for (int i = 0; i < 3; i++) {
            if (t1[i] != t2[i]) return false;
        }

        return true;
    }

    private static int product(int[] triple) {
        return triple[0] * triple[1] * triple[2];
    }
}
