using vi = vector<int>;

int max_profit(const vi & xs, const int first, const int last) {
    if (first >= last - 1) return 0;
    int lo = xs[first];
    int ans = max(0, xs[first + 1] - xs[first]);
    
    for (int i = first + 1; i < last; ++i) {
        ans = max(ans, xs[i] - lo);
        if (xs[i] < lo) lo = xs[i];
    }
    
    return ans;
}

struct Solution final {
    int maxProfit(const vi &xs) const {
        if(xs.empty()) return 0;
        const int sz = xs.size();

        int ans = 0;
        for (int mid = 0; mid <= sz; ++mid) {
            const int left = max_profit(xs, 0, mid);
            const int right = max_profit(xs, mid, sz);
            ans = max(ans, left + right);
        }
        return ans;
    }
};
