using vi = vector<int>;
using usi = unordered_set<int>;

struct Solution final {
    int longestConsecutive(const vi &xs) const {
        if (xs.empty()) return 0;
        usi xs_set(xs.cbegin(), xs.cend());
        const auto [itmin, itmax] = minmax_element(xs.cbegin(), xs.cend());
        
        int ans = 1;
        for (int i = (*itmin) + 1, prev = *itmin, curr = 1; i <= *itmax; ++i) {
            if (xs_set.count(i)) {
                if (i == prev + 1) ++curr;
                else curr = 1;
                
                prev = i;
            } else {
                curr = 0;
                prev = i - 1;
            }
            
            ans = max(ans, curr);
        }        
        return ans;
    }
};
