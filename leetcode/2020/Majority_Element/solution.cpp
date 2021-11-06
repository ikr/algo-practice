struct Solution final {
    int majorityElement(vector<int> &xs) const {
        sort(xs.begin(), xs.end());
        
        int max_count = 0;
        int ans = 0;
        optional<int> current;
        int current_count = 0;
        
        for (const int x : xs) {
            if (!current || *current != x) {
                current_count = 1;
                current = x;
            } else {
                ++current_count;
            }
            
            if (current_count > max_count) {
                ans = *current;
                max_count = current_count;
            }
        }
        
        return ans;
    }
};
