class Solution {
    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.println(s.maxArea(testArray1()));
    }

    private static int[] testArray1() {
        return new int[]{1, 1};
    }

    public int maxArea(int[] height) {
        int result = 0;

        for (int i = 0; i < height.length; ++i) {
            for (int j = i + 1; j < height.length; ++j) {
                int h = Math.min(height[i], height[j]);
                int w = j - i;

                if (h * w > result) {
                    result = h * w;
                }
            }
        }

        return result;
    }
}