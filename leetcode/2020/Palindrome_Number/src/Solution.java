import java.util.ArrayList;

class Solution {
    public boolean isPalindrome(int x) {
        if (x < 0) return false;
        if (x < 10) return true;

        ArrayList<Integer> ds = digits(x);
        int sz = ds.size();
        for (int i = 0; i <= sz / 2; ++i) {
            if (ds.get(i).intValue() != ds.get(sz - i - 1).intValue()) return false;
        }
        return true;
    }

    public ArrayList<Integer> digits(int x) {
        ArrayList<Integer> result = new ArrayList<>();
        int y = x;

        while (y > 0) {
            int digit = y % 10;
            result.add(0, digit);
            y /= 10;
        }

        return result;
    }
}
