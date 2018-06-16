import java.util.Stack;

class Solution {
    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.println(s.largestRectangleArea(new int[]{2, 1, 5, 6, 2, 3})); // 10
//        System.out.println(s.largestRectangleArea(new int[]{6, 2, 5, 4, 5, 1, 6})); // 12
//        System.out.println(s.largestRectangleArea(new int[]{0, 0, 1, 0, 0, 1, 0})); // 1
//        System.out.println(s.largestRectangleArea(new int[0])); // 0
//        System.out.println(s.largestRectangleArea(new int[]{0})); // 0
//        System.out.println(s.largestRectangleArea(new int[]{2})); // 2
//        System.out.println(s.largestRectangleArea(new int[]{2, 2, 2})); // 6
//        System.out.println(s.largestRectangleArea(new int[]{0, 0, 0})); // 0
    }

    public int largestRectangleArea(int[] heights) {
        int result = 0;
        Stack<Integer> limiters = new Stack<>();

        for (int i = 0; i < heights.length; i++) {
            if (limiters.empty() || heights[limiters.peek()] <= heights[i]) {
                limiters.push(i);
            } else {
                while (!limiters.empty() && heights[limiters.peek()] > heights[i]) {
                    int lim = limiters.pop();
                    if (heights[lim] > result) result = heights[lim];
                }

                int lim = limiters.empty() ? -1 : limiters.pop();
                int left = limiters.empty() ? -1 : limiters.pop();
                int area = lim >= 0 ? heights[lim] * (i - left - 1) : 0;
                if (area > result) result = area;

                if (lim >= 0) limiters.push(lim);
                limiters.push(i);
            }
        }

        while (!limiters.empty()) {
            int lim = limiters.pop();
            int left = limiters.empty() ? lim - 1 : limiters.peek();
            int area = heights[lim] * (heights.length - left - 1);
            if (area > result) result = area;
        }

        return result;
    }
}
