int sum_digit_squares(int x) {
    int ans = 0;
    
    while (x) {
        const int d = x % 10;
        ans += d * d;
        x /= 10;
    }
    
    return ans;
}


class Solution final {
public:
    bool isHappy(int n) const {
        unordered_set<int> seen;
        
        while (n != 1 && !seen.count(n)) {
            seen.insert(n);
            n = sum_digit_squares(n);
        }
        
        return n == 1;
    }
};
