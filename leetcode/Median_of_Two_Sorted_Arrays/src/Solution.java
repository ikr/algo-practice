class Solution {
    public double findMedianSortedArrays(int[] xs, int[] ys) {
        if (ys.length < xs.length) return findMedianSortedArrays(ys, xs);
        return recur(xs, 0, xs.length, ys, 0, ys.length);
    }

    private static double recur(int[] xs, int xl, int xr, int[] ys, int yl, int yr) {
        if (xr - xl == 0 && yr - yl == 2) return median(ys, yl, yr);
        return -1.0;
    }

    public static double median(int[] xs, int l, int r) {
        if (r - l == 0) return -1.0;
        if ((r - l) % 2 == 0) return (xs[l + (r - l) / 2 - 1] + xs[l + (r - l) / 2]) / 2.0;
        return (double)xs[l + (r - l) / 2];
    }
}
