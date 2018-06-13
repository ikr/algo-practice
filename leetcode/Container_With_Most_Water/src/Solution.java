class Solution {
    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.println(s.maxArea(new int[]{1, 5, 4, 3}));
        System.out.println(s.maxArea(new int[]{3, 1, 2, 4, 5}));
        System.out.println(s.maxArea(new int[0]));
        System.out.println(s.maxArea(new int[]{1, 1}));
    }

    public int maxArea(int[] height) {
        int result = 0, l = 0, r = height.length - 1;

        while (l < r) {
            int w = r - l;
            int h = Math.min(height[l], height[r]);
            if (w * h > result) {
                result = w * h;
            }

            if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }

        return result;
    }
}