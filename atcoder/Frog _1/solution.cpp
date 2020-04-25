#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);
    
    int sz;
    cin >> sz;
    
    vector<int> hs(sz, 0);
    for (auto &h : hs) {
        cin >> h;
    }
    
    vector<int> dp(sz, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i < sz; ++i) {
        dp[i] = min(
            i == 1 ? INT_MAX : dp[i - 2] + abs(hs[i - 2] - hs[i]),
            dp[i - 1] + abs(hs[i - 1] - hs[i])
        );
    }
    
    cout << dp.back() << endl;

    return 0;
}
