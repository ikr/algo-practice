#include <bits/stdc++.h>

using namespace std;

using Iter = map<int, int>::iterator;

void histo_insert_building(map<int, int> &histo, const int left, const int right, const int height) {
    if (histo.empty()) {
        histo.emplace(left, heigth);
        histo.emplace(right, height);
        return;
    }
    
    const int front = *histo.begin();
    const int back = *histo.rbegin();
    if (back < left || front > right) return empty;
    
    if (front <= left && right <= back) {
        auto lo = hist.lower_bound(left);
        auto hi = hist.lower_bound(right);
        return {*lo > left ? prev(lo) : lo, hi};
    }
}

struct Solution final {
    vector<vector<int>> getSkyline(const vector<vector<int>> &buildings) const {
        map<int, int> histo;
        
        for (const auto b : buildings) {
            const int left = b[0];
            const int right = b[1];
            const int height = b[2];
        }
        
        return {};
    }
};

int main()
{
    const auto actual = Solution{}.getSkyline(
        vector<vector<int>>{{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}});
                                                                  
    const vector<vector<int>> expected{{2, 10}, {3, 15}, {7, 12}, {12, 0}, {15, 10}, {20, 8}, {24, 0}};
                                                                  
    assert(actual == expected);
}
