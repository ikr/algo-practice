class Solution {
    public String longestPalindrome(String s) {
        if (s.length() == 0) return "";
        String result = s.substring(0, 1);
        if (s.length() == 1) return result;
        if (s.length() == 2) return isPal(s) ? s : result;

        for (int i = 0; i < s.length() - 2; ++i) {
            String sprout = s.substring(i, i + 2);

            if (isPal(sprout)) {
                String candidate = growPal(s, i, i + 2);

                if (candidate.length() > result.length()) {
                    result = candidate;
                }
            }

            sprout = s.substring(i, i + 3);

            if (isPal(sprout)) {
                String candidate = growPal(s, i, i + 3);

                if (candidate.length() > result.length()) {
                    result = candidate;
                }
            }
        }

        String candidate = s.substring(s.length() - 2, s.length());
        return (isPal(candidate) && candidate.length() > result.length()) ? candidate : result;
    }

    private static boolean isPal(String s) {
        return s.charAt(0) == s.charAt(s.length() == 2 ? 1 : 2);
    }

    private static String growPal(String s, int left, int bound) {
        int l = left, b = bound;
        while (l > 0 && b < s.length() && s.charAt(l - 1) == s.charAt(b)) {
            l--;
            b++;
        }
        return s.substring(l, b);
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.println(s.longestPalindrome("babadaaaaazzzff"));
    }
}

