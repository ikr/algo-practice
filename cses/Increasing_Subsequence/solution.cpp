#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int max_increasing_subsequence_length(const vi &xs) {
    if (xs.empty()) return 0;
    const int sz = xs.size();
    
    // dp[i] is minimal value closing the sequence of length i + 1 
    vi dp{xs[0]};
    
    for (int i = 1; i < sz; ++i) {
        auto it = lower_bound(dp.begin(), dp.end(), xs[i]);
        if (it == dp.end()) dp.push_back(xs[i]);
        else *it = xs[i];
    }
    
    return dp.size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vi xs(sz, 0);
    for (auto &x : xs) cin >> x;
    cout << max_increasing_subsequence_length(xs) << '\n';
    
    return 0;
}
