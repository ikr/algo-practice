class Solution {
    public String longestPalindrome(String s) {
        if (s.length() == 0) return "";
        String result = s.substring(0, 1);
        if (s.length() == 1) return result;

        for (int i = 0; i < s.length() - 1; ++i) {
            String sprout = s.substring(i, i + 2);

            if (isPal(sprout)) {
                String candidate = growPal(s, i, i + 2);

                if (candidate.length() > result.length()) {
                    result = candidate;
                }
            }
        }

        if (s.length() == 2) return result;

        for (int i = 0; i < s.length() - 2; ++i) {
            String sprout = s.substring(i, i + 3);

            if (isPal(sprout)) {
                String candidate = growPal(s, i, i + 3);

                if (candidate.length() > result.length()) {
                    result = candidate;
                }
            }
        }

        return result;
    }

    private static boolean isPal(String s) {
        return s.charAt(0) == s.charAt(s.length() == 2 ? 1 : 2);
    }

    private static String growPal(String s, int left, int bound) {
        int l = left, b = bound;
        while (left > 0 && bound < s.length() && s.charAt(left) == s.charAt(bound - 1)) {
            l--;
            b++;
        }
        return s.substring(l, b);
    }
}
