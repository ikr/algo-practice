#include <bits/stdc++.h>

using namespace std;

int before_back(const vector<int> &xs) {
    return xs.at(xs.size() - 2);
}

vector<int> gen_fibs(const int bound) {
    vector<int> ans{1, 1};
    
    while (before_back(ans) + ans.back() <= bound) {
        ans.push_back(before_back(ans) + ans.back());
    }
    
    return ans;
}

struct Solution final {
    int findMinFibonacciNumbers(int k) const {
        const auto fibs = gen_fibs(k);
        int ans = 0;
        
        for (auto it = fibs.crbegin(); it != fibs.crend() && !!k; ++it) {
            if (*it <= k) {
                k -= *it;
                ++ans;
            }
        }
        
        return ans;
    }
};
