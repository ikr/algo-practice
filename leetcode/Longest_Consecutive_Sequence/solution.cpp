using vi = vector<int>;
using usi = unordered_set<int>;
using umi = unordered_map<int, int>;

int count_consecutive(const usi &xs_set, umi &memo, const int x) {
    if (memo.count(x)) return memo.at(x);
    memo[x] = 1;

    for (int i = x + 1; xs_set.count(i) == 1; ++i) {
        if (memo.count(i)) {
            memo[x] += memo[i];
            break;
        }
        
        ++memo[x];
    }
    
    return memo.at(x);
}

struct Solution final {
    int longestConsecutive(const vi &xs) const {
        if (xs.empty()) return 0;
        usi xs_set(xs.cbegin(), xs.cend());
        umi memo;
        
        int ans = 0;
        for (const int x : xs_set) ans = max(ans, count_consecutive(xs_set, memo, x));
        return ans;
    }
};
