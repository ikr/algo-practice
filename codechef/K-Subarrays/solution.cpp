#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll INF = 1e17;

ll max_score(const vll &xs, const int k) {
    // Max score for [i sub-arrays] when the last chosen sub-array ends [exactly
    // at index j], inclusive.
    vvll dp(k + 1, vll(sz(xs), -INF));
    dp[0] = vll(sz(xs), 0);
    dp[1][0] = xs[0];

    // hi[i][j] is the max(dp[i][0], dp[i][1], … dp[i][j - 1], dp[i][j])
    vvll hi = dp;

    for (int j = 1; j < sz(xs); ++j) {
        dp[1][j] = max(xs[j], dp[1][j - 1] + xs[j]);
        hi[1][j] = max(dp[1][j], hi[1][j - 1]);
    }

    for (int i = 2; i <= k; ++i) {
        for (int j = i - 1; j < sz(xs); ++j) {
            // 1-element sub-array #i right where we stand
            const auto o1 = hi[i - 1][j - 1] + i * xs[j];

            // Append current element to last sub-array
            const auto o2 = dp[i][j - 1] + i * xs[j];

            dp[i][j] = max({o1, o2, -INF}); // Also, don't accumulate the -INF-s
            hi[i][j] = max(hi[i][j - 1], dp[i][j]);
        }
    }

    return *max_element(cbegin(dp.back()), cend(dp.back()));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vll xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_score(xs, k) << '\n';
    }

    return 0;
}
