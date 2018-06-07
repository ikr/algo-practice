import java.util.regex.Matcher;
import java.util.regex.Pattern;

class Solution {
    private static Pattern dryPattern = Pattern.compile("^ *([+\\-]?\\d+)");

    public int myAtoi(String str) {
        String justNum = dry(str);
        if (justNum.equals("")) return 0;

        int sign;
        String digits;
        if (justNum.substring(0, 1).equals("-")) {
            sign = -1;
            digits = justNum.substring(1);
        } else if (justNum.substring(0, 1).equals("+")) {
            sign = 1;
            digits = justNum.substring(1);
        } else {
            sign = 1;
            digits = justNum;
        }

        digits = dropOpeningZeros(digits);

        if (definitelyHuge(digits)) {
            return sign == -1 ? Integer.MIN_VALUE : Integer.MAX_VALUE;
        }

        long result = digitsVal(digits);

        if (sign == -1 && -result < Integer.MIN_VALUE) {
            return Integer.MIN_VALUE;
        }

        if (sign == 1 && result > Integer.MAX_VALUE) {
            return Integer.MAX_VALUE;
        }

        return (int)result * sign;
    }

    private static String dropOpeningZeros(String digits) {
        int i = 0;

        while (digits.charAt(i) == '0') {
            i++;
        }

        return digits.substring(i);
    }

    private static long digitsVal(String digits) {
        long result = 0, magnitude = 1;

        for (int i = digits.length() - 1; i >= 0; i--) {
            result += digitVal(digits.charAt(i)) * magnitude;
            magnitude *= 10;
        }

        return result;
    }

    private static int digitVal(char d) {
        return (int)d - (int)'0';
    }

    private static boolean definitelyHuge(String digits) {
        return digits.length() > Integer.toString(Integer.MAX_VALUE).length();
    }

    private static String dry(String str) {
        Matcher m = dryPattern.matcher(str);

        if (m.find()) {
            return m.group(1);
        }

        return "";
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.println(s.myAtoi("42"));
        System.out.println(s.myAtoi("   -42"));
        System.out.println(s.myAtoi("4193 with words"));
        System.out.println(s.myAtoi("words and 987"));
        System.out.println(s.myAtoi("-91283472332"));
        System.out.println(s.myAtoi("91283472332"));
        System.out.println(s.myAtoi("+1"));
        System.out.println(s.myAtoi("  0000000000012345678"));
    }
}
