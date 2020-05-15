int edges_max(const vector<int> &xs) {
    const int sz = xs.size();
    
    bool left = true;
    int lo = -1, hi = sz;
    int ans = INT_MIN;
    int curr = 0;
    
    for (;;) {
        if (left) ++lo; else --hi;
        if (lo == hi) break;
        
        if (left) curr = max(xs[lo], curr + xs[lo]);
        else curr = max(xs[hi], curr + xs[hi]);
        
        if (curr > ans) ans = curr;
        left = !left;
    }
    
    return ans;
}

int normal_max(const vector<int> &xs) {
    int ans = INT_MIN;
    int curr = 0;
        
    for (const int x : xs) {
        curr = max(x, curr + x);
        if (curr > ans) ans = curr;
    }
        
    return ans;
}

struct Solution final {
    int maxSubarraySumCircular(const vector<int> &xs) const {
        return max(edges_max(xs), normal_max(xs));
    }
};
