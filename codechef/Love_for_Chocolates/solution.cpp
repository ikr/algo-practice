#include <bits/stdc++.h>
using namespace std;
static constexpr int A_MAX = 1000;

bool solve(const int k, const vector<int> &xs) {
    const int n = xs.size();
    const int total = accumulate(cbegin(xs), cend(xs), 0);
    if (k > total) return false;

    vector<vector<bool>> dp(k + 1, vector<bool>(n, false));
    dp[0][0] = true;
    if (xs[0] <= k) dp[xs[0]][0] = true;

    for (int j = 1; j < n; ++j) {
        for (int i = 0; i <= k; ++i) {
            if (dp[i][j - 1]) {
                dp[i][j] = true;
                continue;
            }

            if (i - xs[j] >= 0) {
                dp[i][j] = dp[i - xs[j]][j - 1];
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        if (dp[k][j]) return true;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int k, n;
        cin >> k;
        cin >> n;
        vector xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << solve(k, xs) << '\n';
    }

    return 0;
}
