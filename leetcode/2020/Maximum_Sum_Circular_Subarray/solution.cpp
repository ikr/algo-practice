using vi = vector<int>;

int max_cont_sum(const vi &xs) {
    int ans = INT_MIN;
    int curr = 0;
        
    for (const int x : xs) {
        curr = max(x, curr + x);
        if (curr > ans) ans = curr;
    }
        
    return ans;
}

struct Solution final {
    int maxSubarraySumCircular(vi xs) const {
        if (all_of(xs.cbegin(), xs.cend(), [](const int x) { return x < 0; })) {
            return *max_element(xs.cbegin(), xs.cend());
        }
        
        const int normal = max_cont_sum(xs);
        const int total = accumulate(xs.cbegin(), xs.cend(), 0);
        
        transform(xs.cbegin(), xs.cend(), xs.begin(), [](const int x) { return -x; });
        const int edge = total + max_cont_sum(xs);
        return max(edge, normal);
    }
};
