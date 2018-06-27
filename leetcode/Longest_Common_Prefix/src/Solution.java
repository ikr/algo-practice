public class Solution {
    public String longestCommonPrefix(String[] strs) {
        if (strs.length == 0) return "";

        String result = strs[0];

        for (int i = 1; i < strs.length; i++) {
            result = longestCommonPrefix(result, strs[i]);
        }

        return result;
    }

    private static String longestCommonPrefix(String s1, String s2) {
        StringBuilder result = new StringBuilder();
        int i = 0;

        while (i < s1.length() && i < s2.length()) {
            if (s1.charAt(i) == s2.charAt(i)) {
                result.append(s1.charAt(i));
            } else {
                break;
            }
            i++;
        }

        return result.toString();
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.println(s.longestCommonPrefix(new String[]{"flower", "flow", "flight"}));
        System.out.println(s.longestCommonPrefix(new String[]{"dog", "racecar", "car"}));
    }
}
