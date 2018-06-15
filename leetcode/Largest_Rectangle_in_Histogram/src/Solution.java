import java.util.Stack;

class Solution {
    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.println(s.largestRectangleArea(new int[]{2, 1, 5, 6, 2, 3})); // 10
        System.out.println(s.largestRectangleArea(new int[]{6, 2, 5, 4, 5, 1, 6})); // 12
        System.out.println(s.largestRectangleArea(new int[]{0, 0, 1, 0, 0, 1, 0})); // 1
        System.out.println(s.largestRectangleArea(new int[0])); // 0
        System.out.println(s.largestRectangleArea(new int[]{0})); // 0
        System.out.println(s.largestRectangleArea(new int[]{2})); // 2
        System.out.println(s.largestRectangleArea(new int[]{2, 2, 2})); // 6
        System.out.println(s.largestRectangleArea(new int[]{0, 0, 0})); // 0
    }

    public int largestRectangleArea(int[] heights) {
        int result = 0;
        Stack<Integer> limiters = new Stack<>();

        for (int i = 0; i < heights.length; i++) {
            if (limiters.empty() || limiters.peek() <= heights[i]) {
                limiters.push(i);
            } else {
                while (!limiters.empty() && limiters.peek() > heights[i]) {
                    limiters.pop();
                }

                int limiter = limiters.empty() ? i : limiters.pop() + 1;
                int left = limiters.empty() ? i : limiters.peek() + 1;
                int area = limiter * (i - left + 1);
                if (area > result) result = area;
            }
        }

        return result;
    }
}
