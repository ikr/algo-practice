using vi = vector<int>;
using Iter = vector<vi>::iterator;

bool disjoint(const vi &ivl1, const vi &ivl2) {
    return ivl2[1] < ivl1[0] || ivl1[1] < ivl2[0];
}

vi merge(const vi &ivl1, const vi &ivl2) {
    vi both = ivl1;
    both.insert(both.cend(), ivl2.cbegin(), ivl2.cend());
    sort(both.begin(), both.end());
    return {both.front(), both.back()};
}

void adjacent_merge_right(vector<vi> &ivls, const Iter it) {
    while (it + 1 != ivls.end() && !disjoint(*it, *(it + 1))) {
        *it = merge(*it, *(it + 1));
        ivls.erase(it + 1);
    }
}

struct Solution final {
    vector<vi> merge(vector<vi> &ivls) {
        sort(ivls.begin(), ivls.end(), [](const vi &lhs, const vi &rhs) { return lhs[0] < rhs[0]; });
        
        for (auto it = ivls.begin(); it != ivls.end(); ++it) {
            adjacent_merge_right(ivls, it);
        }        
        
        return ivls;
    }
};
