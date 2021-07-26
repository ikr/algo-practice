#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll INF = 1e18;

ll min_cost(const vll &xs) {
    vll ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    const auto sigma = [&ss](const int a, const int b) {
        return ss[b] - (a ? ss[a - 1] : 0);
    };

    vvll dp(sz(xs), vll(sz(xs), INF));
    for (int i = 0; i < sz(xs); ++i) dp[i][i] = 0;

    for (int l = 2; l <= sz(xs); ++l) {
        for (int a = 0; a + l <= sz(xs); ++a) {
            const int b = a + l - 1;

            for (int i = a; i < b; ++i) {
                dp[a][b] = min(dp[a][b], dp[a][i] + dp[i + 1][b] + sigma(a, b));
            }
        }
    }

    return dp[0].back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;
    vll xs(n);
    for (auto &x : xs) cin >> x;

    cout << min_cost(xs) << '\n';
    return 0;
}
