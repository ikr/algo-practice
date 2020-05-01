#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll solve(const ll capacity, const vector<pair<ll, ll>> &items) {
    const int sz = items.size();
    
    const ll max_value = accumulate(items.cbegin(), items.cend(), 0, [](const ll agg, const auto item) { 
        return agg + item.second; 
    });
    
    // dp -- min weight [up to item index i][with total value exactly j]
    vector<vector<ll>> dp(sz, vector<ll>(max_value + 1, LLONG_MAX));
    ll ans = LLONG_MIN;
    
    for (int i = 0; i != sz; ++i) {
        for (ll j = 1; j <= max_value; ++j) {
            const ll w = items[i].first;
            const ll v = items[i].second;
            
            if (!i) {
                if (v == j) dp[i][j] = w;
            } else {
                if (v == j) {
                    dp[i][j] = min(dp[i - 1][j], w);
                } else if (v < j) {
                    if (dp[i - 1][j - v] != LLONG_MAX) dp[i][j] = min(dp[i - 1][j - v] + w, dp[i - 1][j]);
                    else dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }

            if (dp[i][j] <= capacity) {
                ans = max(ans, j);
            }
        }
    }
    
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll N, W;
    cin >> N >> W;
    vector<pair<ll, ll>> items(N);
    
    for (auto &item : items) {
        ll w, v;
        cin >> w >> v;
        item = {w, v};
    }
    
    cout << solve(W, items) << endl;
    
    return 0;
}
