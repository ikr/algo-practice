#include <bits/stdc++.h>

using namespace std;

template <typename T1, typename T2> struct PairHash final {
    size_t operator()(const pair<T1, T2> &p) const {
        return 31 * hash<T1>{}(p.first) + hash<T2>{}(p.second);
    }
};

using Memo = unordered_map<pair<int, size_t>, int, PairHash<int, size_t>>;

int profit(Memo &memo, const vector<int> &ps, const int asset, const size_t index) {
    const pair<int, size_t> key{asset, index};
    if (!memo.count(key)) {
        if (index == ps.size()) {
            memo[key] = 0;
        } else {
            if (asset >= 0) {
                memo[key] = max(
                    ps[index] + profit(memo, ps, -1, index + 1),
                    profit(memo, ps, asset, index + 1)
                );
            } else {
                memo[key] = max(
                    profit(memo, ps, ps[index], index + 1) - ps[index],
                    profit(memo, ps, -1, index + 1)
                );
            }
        }
    }
    
    return memo.at(key);
}

struct Solution final {
    int maxProfit(vector<int> prices) const {
        prices.erase(unique(prices.begin(), prices.end()), prices.end());
        if (is_sorted(prices.crbegin(), prices.crend())) return 0;
        
        Memo memo;
        return profit(memo, prices, -1, 0);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    Solution s;
    
    assert(s.maxProfit({7,1,5,3,6,4}) == 7);
    assert(s.maxProfit({1,2,3,4,5}) == 4);
    assert(s.maxProfit({7,6,4,3,1}) == 0);
    assert(s.maxProfit({2,1,2,0,1}) == 2);
}
