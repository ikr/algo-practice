int max_perfect_2_power_in(const int x) {
    if (!x) return 0;
    
    int ans = 1 << 30;
    while (ans != 1) {
        if (ans & x) break;
        ans /= 2;
    }
    
    return ans;
}

struct Solution final {
    int rangeBitwiseAnd(int m, int n) const {
        int ans = 0;
        
        for (;;) {
            const int pm = max_perfect_2_power_in(m);
            if (!pm || pm != max_perfect_2_power_in(n)) break;
            
            ans |= pm;
            m -= pm;
            n -= pm;
        }
        
        return ans;
    }
};


