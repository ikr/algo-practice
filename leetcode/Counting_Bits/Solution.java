class Solution {
    public int[] countBits(int num) {
        if (num == 0) return new int[] {0};

        int[] result = new int[num + 1];
        result[0] = 0;
        result[1] = 1;

        int lastPow2 = 1;
        int x = 2;

        while (x <= num) {
            if (isPow2(x)) {
                result[x] = 1;
                lastPow2 *= 2;
            } else {
                result[x] = 1 + result[x - lastPow2];
            }

            x++;
        }

        return result;
    }

    public boolean isPow2(int x) {
        if (x == 0) return false;
        return (x & (x - 1)) == 0;
    }
}
