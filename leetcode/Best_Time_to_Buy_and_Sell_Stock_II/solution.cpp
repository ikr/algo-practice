#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int maxProfit(const vector<int> ps) const {
        int ans = 0;
        
        for (auto i = 1U; i < ps.size(); ++i) {
            if (ps[i - 1] < ps[i]) ans += ps[i] - ps[i - 1];
        }
        
        return ans;
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
