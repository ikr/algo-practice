#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll M = 1e9 + 7;

constexpr ll add_mod(const ll x, const ll y) {
    const ll ans = x + y;
    return ans >= M ? ans - M : ans;
}

ll k_long_paths_num(const ll k, const vvi &adj) {
    // Number of ways to reach [in k steps] [the vertex v]
    vvll dp(k + 1, vll(sz(adj), 0LL));
    dp[0] = vll(sz(adj), 1LL);

    for (ll steps = 1; steps <= k; ++steps) {
        for (int ro = 0; ro < sz(adj); ++ro) {
            for (int co = 0; co < sz(adj); ++co) {
                if (!adj[ro][co]) continue;
                dp[steps][co] = add_mod(dp[steps][co], dp[steps - 1][ro]);
            }
        }
    }

    return accumulate(cbegin(dp.back()), cend(dp.back()), 0LL, add_mod);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    ll k;
    cin >> k;

    vvi adj(n, vi(n));
    for (auto &row : adj) {
        for (auto &cell : row) cin >> cell;
    }

    cout << k_long_paths_num(k, adj) << '\n';
    return 0;
}
