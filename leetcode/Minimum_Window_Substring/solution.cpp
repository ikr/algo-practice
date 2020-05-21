using vi = vector<int>;
using pi = pair<int, int>;

vi gather_letter_counts(const string &s, const int first, const int last) {
    vi ans(CHAR_MAX + 1, 0);
    for (auto i = first; i != last; ++i) ++ans[s[i]];
    return ans;
}

bool confirm_includes(const vi &total_counts, const vi &specific_counts) {
    for (int i = 0; i <= CHAR_MAX; ++i) {
        if (total_counts[i] < specific_counts[i]) return false;
    }
    return true;
}

pi keep_shortest(const pi &lohi, const int lo, const int hi) {
    const auto [a, b] = lohi;
    return b - a > hi - lo ? pi{lo, hi} : lohi;
}

struct Solution final {
    string minWindow(const string &s, const string &t) const {
        if (t.empty()) return "";
        const auto t_counts = gather_letter_counts(t, 0, t.size());
        if (!confirm_includes(gather_letter_counts(s, 0, s.size()), t_counts)) return "";
        
        auto curr = gather_letter_counts(s, 0, t.size());
        pi ans{0, s.size()};
        
        for (int lo = 0, hi = t.size(); lo != hi;) {
            const bool covered = confirm_includes(curr, t_counts);
            
            if (covered || hi == s.size()) { // contract
                if (covered) ans = keep_shortest(ans, lo, hi);
                --curr[s[lo]];
                ++lo;
            } else { // expand
                ++hi;
                ++curr[s[hi - 1]];
            }
        }
        
        return s.substr(ans.first, ans.second - ans.first);
    }
};
