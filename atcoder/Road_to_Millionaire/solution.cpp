#include <bits/stdc++.h>
using namespace std;

int max_yen(const vector<int> &xs) {
    const int sz = xs.size();
    vector<vector<int>> dp(sz, vector<int>(sz + 1, -1));

    for (int y = 1000, s = 0; y >= 0 && s <= sz; y -= xs[0], ++s) {
        dp[0][s] = y;
    }

    for (int d = 1; d < sz; ++d) {
        for (int s = 0; s <= sz; ++s) {
            for (int y = dp[d - 1][s], ss = s; y >= 0 && ss <= sz;
                 y -= xs[d], ++ss) {
                dp[d][ss] = max(dp[d][ss], y);
            }

            for (int ss = s; s > 0; --ss) {
                dp[d][ss - 1] = max(dp[d][ss], dp[d][ss] + xs[d]);
            }
        }
    }

    int ans = -1;

    for (const auto &r : dp) {
        ans = max(ans, *max_element(r.cbegin(), r.cend()));
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<int> xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout << max_yen(xs) << '\n';

    return 0;
}
