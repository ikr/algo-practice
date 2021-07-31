#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using mint = atcoder::modint998244353;

int k_days_roundtrips(const int k, const vvi &ung) {
    const int n = sz(ung);

    // dp[i] is the number of walks to vertex i
    vector<mint> dp(n, 0);
    dp[0] = 1;

    for (int j = 0; j < k; ++j) {
        const auto total = accumulate(cbegin(dp), cend(dp), mint{0});
        vector<mint> dp_(n, 0);

        for (int i = 0; i < n; ++i) {
            dp_[i] = total;
            for (const auto v : ung[i]) {
                dp_[i] -= dp[v];
            }
        }

        swap(dp, dp_);
    }

    return dp[0].val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, k;
    cin >> n >> m >> k;

    vvi ung(n);

    for (int i = 0; i < n; ++i) {
        ung[i].push_back(i);
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        ung[u].push_back(v);
        ung[v].push_back(u);
    }

    cout << k_days_roundtrips(k, ung) << '\n';
    return 0;
}
