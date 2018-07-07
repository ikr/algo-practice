class Solution {
    public static void main(String[] args) {
        Solution s = new Solution();
        int[] nums = new int[] {3, 4, 9, 58, 1994};
        for (int num : nums) {
            System.out.format("%d -> %s\n", num, s.intToRoman(num));
        }
    }

    public String intToRoman(int num) {
        StringBuilder buf = new StringBuilder();
        int gradeIndex = 0;

        while (num > 0) {
            if (num >= grades[gradeIndex].value) {
                buf.append(repeat(num / grades[gradeIndex].value, grades[gradeIndex].literal));
                num %= grades[gradeIndex].value;
            }

            gradeIndex++;
        }

        return buf.toString();
    }

    private static StringBuilder recur(StringBuilder prefix, int num) {
        if (num > 1000) {
            int thousands = num / 1000;
            int remainder = num % 1000;
            return recur(prefix.append(repeat(thousands, "M")), remainder);
        }

        return prefix;
    }

    private static Grade[] grades = new Grade[] {
        new Grade(1000, "M"),
        new Grade(900, "CM"),
        new Grade(500, "D"),
        new Grade(400, "CD"),
        new Grade(100, "C"),
        new Grade(90, "XC"),
        new Grade(50, "L"),
        new Grade(40, "XL"),
        new Grade(10, "X"),
        new Grade(9, "IX"),
        new Grade(5, "V"),
        new Grade(4, "IV"),
        new Grade(1, "I"),
    };

    private static class Grade {
        int value;
        String literal;

        public Grade(int value, String literal) {
            this.value = value;
            this.literal = literal;
        }

    }

    private static String repeat(int count, String what) {
        StringBuilder buf = new StringBuilder();

        for (int i = 0; i < count; i++) {
            buf.append(what);
        }

        return buf.toString();
    }
}
