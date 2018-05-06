import java.util.Arrays;

/**
 * Based on https://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/
 */
class Solution {
    public double findMedianSortedArrays(int[] xs, int[] ys) {
        return recur(xs, 0, xs.length, ys, 0, ys.length);
    }

    private static double recur(int[] xs, int xl, int xr, int[] ys, int yl, int yr) {
        if (xr - xl > yr - yl) return recur(ys, yl, yr, xs, xl, xr);
        if (xr - xl == 0) return median(ys, yl, yr);

        if (xr - xl < 3 && yr - yl < 3) {
            int[] mArr = concatArrays(xs, xl, xr, ys, yl, yr);

            Arrays.sort(mArr);
            return median(mArr, 0, mArr.length);
        }

        int midy = yl + (yr - yl) / 2;

        if (xr - xl == 1 && (yr - yl) % 2 == 1) {
            int[] mArr = new int[] {ys[midy - 1], ys[midy + 1], xs[xl]};
            Arrays.sort(mArr);

            return (median(mArr, 0, 3) + ys[midy]) / 2.0;
        }

        if (xr - xl == 1 && (yr - yl) % 2 == 0) {
            int[] mArr = new int[] {ys[midy - 1], ys[midy], xs[xl]};
            Arrays.sort(mArr);
            return median(mArr, 0, 3);
        }

        if (xr - xl == 2 && yr - yl == 2) {
            int[] mArr = new int[] {xs[xl], xs[xl + 1], ys[yl], ys[yl + 1]};
            Arrays.sort(mArr);
            return median(mArr, 0, 4);
        }

        if (xr - xl == 2 && (yr - yl) % 2 == 1) {
            int[] mArr = new int[] {ys[midy], Math.max(xs[xl], ys[midy - 1]), Math.min(xs[xl + 1], ys[midy + 1])};
            Arrays.sort(mArr);
            return median(mArr, 0, 3);
        }

        if (xr - xl == 2 && (yr - yl) % 2 == 0) {
            int[] mArr = new int[] {ys[midy], ys[midy - 1], Math.max(xs[xl], ys[midy - 2]), Math.min(xs[xl + 1], ys[midy + 1])};
            Arrays.sort(mArr);
            return median(mArr, 0, 4);
        }

        int xsSz = (xr - xl);
        int newXsSz = xsSz / 2 + 1;

        if (median(xs, xl, xr) >= median(ys, yl, yr)) {
            return recur(xs, xl, xl + newXsSz, ys, yl + (xsSz - newXsSz), yr);
        }

        return recur(xs, xl + (xsSz - newXsSz), xr, ys, yl, yr - (xsSz - newXsSz));
    }

    private static int[] concatArrays(int[] xs, int xl, int xr, int[] ys, int yl, int yr) {
        int[] mArr = new int[xr - xl + yr - yl];

        for (int i = 0; i < xr - xl; i++) {
            mArr[i] = xs[xl + i];
        }

        for (int j = 0; j < yr - yl; j++) {
            mArr[xr - xl + j] = ys[yl + j];
        }
        return mArr;
    }

    public static double median(int[] xs, int l, int r) {
        if (r - l == 0) return -1.0;
        if ((r - l) % 2 == 0) return (xs[l + (r - l) / 2 - 1] + xs[l + (r - l) / 2]) / 2.0;
        return (double)xs[l + (r - l) / 2];
    }
}
