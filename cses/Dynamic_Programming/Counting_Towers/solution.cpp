#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using mint = atcoder::modint1000000007;
static constexpr int LIM = 1'000'001;

// Encoding
//
// 0 |_._|   1 |_|_|   2 |.|.|
//
// 3 |_|.|   4 |.|_|   5 |...|

constexpr int Q = 6;

vector<vector<mint>> sufficiently_large_table() {
    vector<vector<mint>> dp(LIM, vector<mint>(Q, 0));
    dp[0][0] = 1;

    for (int i = 1; i < sz(dp); ++i) {
        const auto &pr = dp[i - 1];

        dp[i][0] = pr[0] + pr[1] + pr[5];
        dp[i][1] = pr[0] + pr[1] + pr[2] + pr[3] + pr[4];
        dp[i][2] = pr[0] + pr[1] + pr[2] + pr[3] + pr[4];
        dp[i][3] = pr[0] + pr[1] + pr[2] + pr[3] + pr[4];
        dp[i][4] = pr[0] + pr[1] + pr[2] + pr[3] + pr[4];
        dp[i][5] = pr[0] + pr[1] + pr[5];
    }

    return dp;
}

mint towers_num(const vector<vector<mint>> &dp, const int n) {
    return dp[n][0] + dp[n][1];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto dp = sufficiently_large_table();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << towers_num(dp, n).val() << '\n';
    }

    return 0;
}
