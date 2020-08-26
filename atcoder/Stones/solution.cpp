#include <bits/stdc++.h>
using namespace std;

bool first_wins(const vector<int> &xs, const int k) {
    // winning on [i stones]
    vector<bool> dp(k + 1, false);

    for (int i = 1; i <= k; ++i) {
        for (const auto x : xs) {
            if (i - x >= 0 && !dp[i - x]) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[k];
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
