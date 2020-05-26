using uss = unordered_set<string>;
using umss = unordered_map<string, uss>;
using vi = vector<int>;

template <typename T1, typename T2> struct PairHash final {
    size_t operator()(const pair<T1, T2> &p) const {
        return 31 * hash<T1>{}(p.first) + hash<T2>{}(p.second);
    }
};

vi letters_count(const string &s) {
    vi ans(CHAR_MAX, 0);
    for (const char c : s) ++ans[c];
    return ans;
}

struct Solution final {
    bool isScramble(const string &s, const string &t) {
        pair<string, string> key{s, t};
        if (memo.count(key)) return memo.at(key);
        
        if (letters_count(s) != letters_count(t)) memo[key] = false;
        else if (s == t) memo[key] = true;
        else {
            const int sz = s.size();
            bool ok = false;
            for (int i = 1; i < sz; ++i) {
                if (
                    (isScramble(s.substr(0, i), t.substr(0, i)) && isScramble(s.substr(i), t.substr(i))) ||
                    (isScramble(s.substr(0, i), t.substr(sz - i)) && isScramble(s.substr(i), t.substr(0, sz - i)))
                ) {
                    ok = true;
                    break;
                }
            }
            memo[key] = ok;
        }
        
        return memo.at(key);
    }
    
private:
    unordered_map<pair<string, string>, bool, PairHash<string, string>> memo;
};
