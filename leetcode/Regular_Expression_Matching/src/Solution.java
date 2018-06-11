class Solution {
    public boolean isMatch(String s, String p) {
        return false;
    }

    public static void main(String[] args) {
        Solution s = new Solution();

        String[][] cases = new String[][]{
                {"aa", "a"},
                {"aa", "a*"},
                {"ab", ".*"},
                {"aab", "c*a*b"},
                {"mississippi", "mis*is*p*."}
        };

        for (String[] c : cases) {
            System.out.printf("string %s, pattern %s → %b\n", c[0], c[1], s.isMatch(c[0], c[1]));
        }
    }
}
