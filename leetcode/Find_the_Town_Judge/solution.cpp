struct Solution {
    int findJudge(const int n, const vector<vector<int>> &es) const {
        unordered_multimap<int, int> out_g;
        unordered_multimap<int, int> in_g;
        
        for (const auto &e : es) {
            out_g.emplace(e[0], e[1]);
            in_g.emplace(e[1], e[0]);
        }
        
        int ans = -1;
        
        for (int i = 1; i <= n; ++i) {
            if (out_g.count(i) == 0 && in_g.count(i) == n - 1) {
                if (ans > 0) return -1;
                ans = i;
            }
        }
            
        return ans;
    }
};
