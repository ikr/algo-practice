import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<String> readBinaryWatch(int num) {
        List<String> result = new ArrayList<>();
        for (int i = 0; i < 1024; i++) {
            if (onesCount(i) == num) {
                int h = hours(i);
                int m = minutes(i);

                if (validHours(h) && validMinutes(m)) {
                    result.add(timeString(h, m));
                }
            }
        }
        return result;
    }

    public static int onesCount(int x) {
        int result = 0;
        int mask = 1;
        while (mask <= x) {
            if ((mask & x) != 0) result += 1;
            mask = mask << 1;
        }
        return result;
    }

    private static int hours(int x) {
        return (x & 0b1111000000) >> 6;
    }

    private static int minutes(int x) {
        return x & 0b0000111111;
    }

    private static boolean validHours(int x) {
        return x >= 0 && x < 12;
    }

    private static boolean validMinutes(int x) {
        return x >= 0 && x < 60;
    }

    private static String timeString(int h, int m) {
        return String.format("%d:%02d", h, m);
    }
}
