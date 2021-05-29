#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_drinks(const vll &xs) {
    vector<map<ll, int>> dp(sz(xs));

    dp[0][0] = 0;
    if (xs[0] >= 0) dp[0][xs[0]] = 1;

    for (int i = 1; i < sz(xs); ++i) {
        for (const auto [k, v] : dp[i - 1]) {
            dp[i][k] = max(dp[i][k], v);

            if (k + xs[i] >= 0) {
                dp[i][k + xs[i]] = max(dp[i][k + xs[i]], v + 1);
            }
        }
    }

    int ans = 0;
    for (const auto [_, v] : dp.back()) {
        ans = max(ans, v);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vll xs(n);
    for (auto &x : xs) cin >> x;

    cout << max_drinks(xs) << '\n';
    return 0;
}
