struct Solution final {
    int findMaxLength(const vector<int> &xs) const {
        if (xs.empty()) return 0;
    
        int ans = 0;
        int balance = 0;
        unordered_map<int, int> indices_by_balance{{0, -1}};
        
        for (int i = 0; i != xs.size(); ++i) {
            if (xs[i]) ++balance;
            else --balance;
            
            if (indices_by_balance.count(balance)) {
                ans = max(ans, i - indices_by_balance.at(balance));
            } else {
                indices_by_balance[balance] = i;
            }
        }
        
        return ans;
    }
};
