import java.util.ArrayList;
import java.util.Stack;

class Solution {
    private static class TestCase {
        public int[] heights;
        public int expectedResult;

        public TestCase(int[] heights, int expectedResult) {
            this.heights = heights;
            this.expectedResult = expectedResult;
        }
    }

    public static void main(String[] args) {
        ArrayList<TestCase> cases = new ArrayList<>();
        cases.add(new TestCase(new int[]{2, 1, 5, 6, 2, 3}, 10));
        cases.add(new TestCase(new int[]{6, 2, 5, 4, 5, 1, 6}, 12));
        cases.add(new TestCase(new int[]{0, 0, 1, 0, 0, 1, 0}, 1));
        cases.add(new TestCase(new int[0], 0));
        cases.add(new TestCase(new int[]{0}, 0));
        cases.add(new TestCase(new int[]{2}, 2));
        cases.add(new TestCase(new int[]{2, 2, 2}, 6));
        cases.add(new TestCase(new int[]{0, 0}, 0));

        Solution s = new Solution();
        for (TestCase tc : cases) {
            int result = s.largestRectangleArea(tc.heights);
            System.out.printf("Expected %d, got %d -- %b\n", tc.expectedResult, result, tc.expectedResult == result);
        }
    }

    public int largestRectangleArea(int[] heights) {
        int result = 0;
        Stack<Integer> limiters = new Stack<>();

        for (int i = 0; i < heights.length; i++) {
            if (limiters.empty() || heights[limiters.peek()] <= heights[i]) {
                limiters.push(i);
            } else {
                int left = -1, lim = -1;

                while (!limiters.empty() && heights[limiters.peek()] > heights[i]) {
                    lim = limiters.pop();
                    int area = heights[lim] * (i - lim);
                    if (area > result) result = area;
                    left = lim - 1;
                }

                if (!limiters.empty()) lim = limiters.pop();
                if (!limiters.empty()) left = limiters.pop();

                int area = heights[lim] * (i - left - 1);
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
