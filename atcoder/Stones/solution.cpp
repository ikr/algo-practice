#include <bits/stdc++.h>
using namespace std;

bool first_wins(const vector<int> &xs, const int k) {
    const int n = xs.size();

    // winning on [i stones] using pull-numbers [up to index j]
    vector<vector<bool>> dp(k + 1, vector(n, false));

    for (int i = 1; i <= k; ++i) {
        const int x = xs[0];
        dp[i][0] = (i / x) % 2 == 1;
    }

    for (int j = 1; j < n; ++j) {
        for (int i = 1; i <= k; ++i) {
            const int x = xs[j];

            dp[i][j] =
                i - x >= 0 ? !dp[i - x][j] || dp[i][j - 1] : dp[i][j - 1];
        }
    }

    return dp[k][n - 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    cout << (first_wins(xs, k) ? "First" : "Second") << '\n';

    return 0;
}
