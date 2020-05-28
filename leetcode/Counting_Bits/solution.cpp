using vi = vector<int>;

constexpr bool is_power_of_two(const int x) {
    if (x == 0) return false;
    return (x & (x - 1)) == 0;
}

struct Solution final {
    vi countBits(const int x) {
        if (!x) return {0};
        vi ans(x + 1, 0);
        ans[1] = 1;
        
        for (int i = 2, last_2_exp = 1; i <= x; ++i) {
            if (is_power_of_two(i)) {
                ans[i] = 1;
                last_2_exp *= 2;
            } else {
                ans[i] = ans[i - last_2_exp] + 1;
            }
        }
        
        return ans;
    }
};
