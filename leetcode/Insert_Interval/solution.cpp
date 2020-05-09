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

Iter insert_in_order(vector<vi> &ivls, const vi &ivl) {
    auto it = upper_bound(
        ivls.cbegin(), 
        ivls.cend(), 
        ivl, 
        [](const vi &lhs, const vi &rhs) { return lhs[0] < rhs[0]; }
    );
    
    return ivls.insert(it, ivl);
}

Iter adjacent_merge_left(vector<vi> &ivls, const Iter it) {
    if (it == ivls.begin() || disjoint(*(it - 1), *it)) return it;
    *it = merge(*(it - 1), *it);
    return ivls.erase(it - 1);
}

void adjacent_merge_right(vector<vi> &ivls, const Iter it) {
    if (it + 1 == ivls.end() || disjoint(*it, *(it + 1))) return;
    
    auto last = upper_bound(
        it + 1, 
        ivls.end(), 
        *it,
        [](const vi &lhs, const vi &rhs) { return disjoint(lhs, rhs); }
    );
    
    *it = merge(*it, vi{(*(it + 1))[0], (*(last - 1))[1]});
    ivls.erase(it + 1, last);
}

struct Solution final {
    vector<vi> insert(vector<vi> &ivls, vi ivl) const {
        auto it = insert_in_order(ivls, ivl);
        it = adjacent_merge_left(ivls, it);
        adjacent_merge_right(ivls, it);
        return ivls;
    }
};
