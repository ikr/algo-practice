#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll solve(const int capacity, const vector<pair<int, ll>> &items) {
    const int sz = items.size();
    
    // dp[up to item index][capacity]
    vector<vector<ll>> dp(sz, vector<ll>(capacity + 1, 0));
    
    for (int i = 0; i != sz; ++i) {
        for (int c = 1; c <= capacity; ++c) {
            const auto w = items[i].first;
            const auto v = items[i].second;
            
            if (!i) {
                dp[i][c] = w <= c ? v    : 0;
                continue;
            }
            
            if (w > c) {
                dp[i][c] = dp[i - 1][c];
            } else {
                dp[i][c] = max(dp[i - 1][c], dp[i - 1][c - w] + v);
            }
        }
    }
    
    return dp[sz - 1][capacity];
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);
    
    int N, W;
    cin >> N >> W;
    vector<pair<int, ll>> items(N);
    
    for (auto &item : items) {
        int w;
        ll v;
        cin >> w >> v;
        item = {w, v};
    }
    
    cout << solve(W, items) << endl;
    
    return 0;
}
