class Solution {
    public boolean isMatch(String s, String p) {
        return match(s, 0, p, 0);
    }

    private static boolean match(String s, int sidx, String p, int pidx) {
        if (sidx == s.length()) {
            if (pidx == p.length()) return true;
            if (pidx == p.length() - 2 && p.charAt(pidx + 1) == '*') return true;
            return false;
        }

        if (pidx == p.length()) return false;

        if (p.charAt(pidx) == '.' && p.indexOf(".*", pidx) != pidx) {
            return match(s, sidx + 1, p, pidx + 1);
        }

        if (p.indexOf(".*", pidx) == pidx) {
            return match(s, sidx + 1, p, pidx) || match(s, sidx, p, pidx + 2);
        }

        if (pidx + 1 < p.length() && p.charAt(pidx + 1) == '*') {
            return (
                    (s.charAt(sidx) == p.charAt(pidx) && match(s, sidx + 1, p, pidx))
                            || match(s, sidx, p, pidx + 2)
            );
        }

        if (s.charAt(sidx) != p.charAt(pidx)) return false;

        return match(s, sidx + 1, p, pidx + 1);
    }

    public static void main(String[] args) {
        Solution s = new Solution();

        String[][] cases = new String[][]{
                {"", ""},
                {"aa", "a"},
                {"aa", "aa"},
                {"aa", "a*"},
                {"ab", ".*"},
                {"aab", "c*a*b"},
                {"mississippi", "mis*is*p*."},
                {"mississippi", "mis*is*ip*."},
                {"aasdfasdfasdfasdfas", "aasdf.*asdf.*asdf.*asdf.*s"},
                {"bc", ".*b.*c"},
                {"abc", ".*a.*b.*c.*"}
        };

        for (String[] c : cases) {
            System.out.printf("string %s, pattern %s → %b\n", c[0], c[1], s.isMatch(c[0], c[1]));
        }
    }
}
