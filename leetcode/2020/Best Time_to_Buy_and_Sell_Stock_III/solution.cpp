using vi = vector<int>;

vi max_profits_from_all_points(const vi &xs) {
    const int sz = xs.size();
    int hi = xs[sz - 1];
    vi ans(sz, 0);
    
    for (int i = sz - 2; i >= 0; --i) {
        ans[i] = max(ans[i + 1], hi - xs[i]);
        hi = max(hi, xs[i]);
    }
    
    return ans;
}

vi max_profits_till_all_points(const vi &xs) {
    const int sz = xs.size();
    int lo = xs[0];
    vi ans(sz, 0);
    
    for (int i = 1; i <= sz - 1; ++i) {
        ans[i] = max(ans[i - 1], xs[i] - lo);
        lo = min(lo, xs[i]);
    }
    
    return ans;
}

struct Solution final {
    int maxProfit(const vi &xs) const {
        if(xs.empty()) return 0;
        const int sz = xs.size();
        
        const auto best_from = max_profits_from_all_points(xs);
        const auto best_till = max_profits_till_all_points(xs);
        
        int ans = 0;
        for (int i = 0; i != sz - 1; ++i) {
            ans = max(ans, (i > 0 ? best_till[i - 1] : 0) + best_from[i]);
        }
        return ans;
    }
};
