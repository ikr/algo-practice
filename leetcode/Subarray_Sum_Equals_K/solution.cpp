struct Solution final {
    int subarraySum(const vector<int> &xs, const int k) const {
        const int sz = xs.size();
        if (sz == 0) return 0;
        
        int ans = 0;
        unordered_map<int, int> counts_by_prefix_sum{{0, 1}};
        int current_sum = 0;
        
        for (const int x : xs) {
            current_sum += x;
            
            const int diff = current_sum - k;
            ans += counts_by_prefix_sum[diff];
            
            ++counts_by_prefix_sum[current_sum];
        }
        
        return ans;
    }
};
