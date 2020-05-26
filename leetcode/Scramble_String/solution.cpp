using uss = unordered_set<string>;
using umss = unordered_map<string, uss>;
using vi = vector<int>;

vi letters_count(const string &s) {
    vi ans(CHAR_MAX, 0);
    for (const char c : s) ++ans[c];
    return ans;
}

uss scrambles(umss &memo, const string &s) {
    if (!memo.count(s)) {
        const int sz = s.size();
        
        if (s.empty()) memo[s] = uss{};
        else if (sz == 1) memo[s] = uss{s};
        else {
            memo[s] = uss{s};
            
            for (int i = 1; i < sz; ++i) {
                const auto aset = scrambles(memo, s.substr(0, i));
                const auto bset = scrambles(memo, s.substr(i));
                
                for (const auto &a : aset) {
                    for (const auto &b : bset) {
                        memo[s].insert(a + b);
                        memo[s].insert(b + a);
                    }
                }
            }
        }
    }
    
    return memo.at(s);
}

struct Solution final {
    bool isScramble(const string &s, const string &t) const {
        if (letters_count(s) != letters_count(t)) return false;
        umss memo;
        const auto sset = scrambles(memo, s);
        return sset.count(t);
    }
};
