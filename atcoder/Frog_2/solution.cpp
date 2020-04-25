#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);
    
    int sz, k;
    cin >> sz >> k;
    
    vector<int> hs(sz, 0);
    for (auto &h : hs) {
        cin >> h;
    }
    
    vector<int> dp(sz, INT_MAX);
    dp[0] = 0;
    
    for (int i = 0; i < sz; ++i) {
        for (int j = 1; j <= k && i + j < sz; ++j) {
            dp[i + j] = min(dp[i + j], dp[i] + abs(hs[i] - hs[i + j]));
        }
    }
    
    cout << dp.back() << endl;

    return 0;
}
