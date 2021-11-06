using vi = vector<int>;
using Iter = vector<vi>::iterator;

bool disjoint(const vi &ivl1, const vi &ivl2) {
    return ivl2[1] < ivl1[0] || ivl1[1] < ivl2[0];
}

vi merge_ivls(const vi &ivl1, const vi &ivl2) {
    vi both = ivl1;
    both.insert(both.cend(), ivl2.cbegin(), ivl2.cend());
    sort(both.begin(), both.end());
    return {both.front(), both.back()};
}

struct Solution final {
    vector<vi> merge(vector<vi> &ivls) {
        if (ivls.size() < 2) return ivls;
        
        sort(ivls.begin(), ivls.end(), [](const vi &lhs, const vi &rhs) { return lhs[0] < rhs[0]; });
        vector<vi> ans{ivls.front()};
        
        for (auto i = 1U; i != ivls.size(); ++i) {
            if (!disjoint(ivls[i], ans.back())) {
                ans.back() = merge_ivls(ivls[i], ans.back());
            } else {
                ans.push_back(ivls[i]);
            }
        }
        
        return ans;
    }
};
