public class Merge {
    public static int[] merge(int[] xs, int[] ys) {
        int[] result = new int[xs.length + ys.length];

        int i = 0, j = 0, k = 0;
        while (i < xs.length || j < ys.length) {
            int curr;
            if (i < xs.length && j < ys.length) {
                if (xs[i] < ys[j]) {
                    curr = xs[i];
                    i++;
                } else {
                    curr = ys[j];
                    j++;
                }
            } else {
                if (i < xs.length) {
                    curr = xs[i];
                    i++;
                } else {
                    curr = ys[j];
                    j++;
                }
            }

            result[k] = curr;
            k++;
        }

        return result;
    }
}
