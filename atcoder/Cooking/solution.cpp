#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_cooking_time(const vi &xs) {
    const int s = accumulate(cbegin(xs), cend(xs), 0);

    // True iff there's a subset [of the first i + 1 elements] having the sum
    // [of exactly to j]
    vector<vector<bool>> dp(sz(xs), vector<bool>(s + 1, false));
    dp[0][0] = true;
    dp[0][xs[0]] = true;

    for (int i = 1; i < sz(xs); ++i) {
        for (int j = 0; j <= s; ++j) {
            dp[i][j] = dp[i - 1][j];

            const int gap = j - xs[i];
            if (gap >= 0 && dp[i - 1][gap]) {
                dp[i][j] = true;
            }
        }
    }

    int ans = INT_MAX;

    for (int j = 0; j <= s / 2; ++j) {
        if (dp.back()[j]) {
            ans = min(ans, max(j, s - j));
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    cout << min_cooking_time(xs) << '\n';
    return 0;
}
