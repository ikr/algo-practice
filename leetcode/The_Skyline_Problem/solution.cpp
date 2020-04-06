#include <bits/stdc++.h>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}

set<int> gather_key_xs(const vector<vector<int>> &towers) {
    set<int> ans;
    
    for (const auto &t : towers) {
        const int left = t[0];
        const int right = t[1];
            
        ans.insert(left);
        ans.insert(right);
    }
    
    return ans;
}

map<int, int> derive_histo(const vector<vector<int>> &towers, const set<int> &key_xs) {
    map<int, int> ans;
    
    for (const auto &t : towers) {
        const int left = t[0];
        const int right = t[1];
        const int height = t[2];

        for (auto it = key_xs.lower_bound(left); it != key_xs.cend() && *it <= right; ++it) {
            if (!ans.count(*it)) ans[*it] = -1;
            ans[*it] = max(ans.at(*it), height);
        }
    }

    return ans;
}

struct Solution final {
    vector<vector<int>> getSkyline(const vector<vector<int>> &towers) const {
        const auto key_xs = gather_key_xs(towers);
        map<int, int> histo = derive_histo(towers, key_xs);
        
        vector<vector<int>> ans;
        
        for (const auto [x, h] : histo) {
            if (ans.empty() || ans.back()[1] != h) {
                ans.push_back(vector<int>{x, h});          
            }
        }
        
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    const auto actual = Solution{}.getSkyline(
        vector<vector<int>>{{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}});
                                                                  
    const vector<vector<int>> expected{{2, 10}, {3, 15}, {7, 12}, {12, 0}, {15, 10}, {20, 8}, {24, 0}};
    
    cout << actual << '\n' << expected << endl;
                                                                  
    assert(actual == expected);
    
    return 0;
}
