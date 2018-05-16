class Solution {
    public boolean isPalindrome(String s) {
        if (s.length() == 0) return true;
        s = s.toLowerCase();
        int l = 0;
        int r = s.length() - 1;

        do {
            l = skipSeps(s, 1, l);
            r = skipSeps(s, -1, r);

            if (l <= r && s.charAt(l) != s.charAt(r)) return false;

            l++;
            r--;
        } while (l <= r);

        return true;
    }

    private static int skipSeps(String s, int increment, int current) {
        while (isSep(s.charAt(current)) && current + increment >= 0 && current + increment < s.length()) {
            current += increment;
        }

        return current;
    }

    private static boolean isSep(char c) {
        return !isAlphanum(c);
    }

    private static boolean isAlphanum(char c) {
        String s = String.valueOf(c);
        return s.matches("[a-z0-9]");
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.println(s.isPalindrome(""));
    }
}
