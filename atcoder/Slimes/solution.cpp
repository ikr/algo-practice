#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll INF = 1e18;

ll min_combo(const vi &xs) {
    // Answer for [combo length] [starting from index]
    vvll dp(sz(xs) + 1, vll(sz(xs), INF));

    for (int i = 0; i < sz(xs); ++i) {
        dp[1][i] = xs[i];
    }

    for (int l = 2; l <= sz(xs); ++l) {
        for (int i = 0; i + l <= sz(xs); ++i) {
        }
    }

    return dp.back()[0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;
    vi xs(n);
    for (auto &x : xs) cin >> x;

    cout << min_combo(xs) << '\n';
    return 0;
}
