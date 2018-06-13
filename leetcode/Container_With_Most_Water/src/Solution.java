class Solution {
    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.println(s.maxArea(new int[]{1, 5, 4, 3}));
        System.out.println(s.maxArea(new int[]{3, 1, 2, 4, 5}));
        System.out.println(s.maxArea(new int[0]));
        System.out.println(s.maxArea(new int[]{1, 1}));
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