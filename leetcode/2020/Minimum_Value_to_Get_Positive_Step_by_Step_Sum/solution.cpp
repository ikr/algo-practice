#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int minStartValue(const vector<int> &nums) {
        int ans = 0;
        int s = 0;
        
        for (const int x : nums) {
            s += x;
            
            if (s <= 0) {
                ans += -s + 1; 
                s = 1;
            }
        }
        
        return max(1, ans);
    }
};
