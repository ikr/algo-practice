#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll total_fs(const vvi &adj) {
    const int n = sz(adj);
    vector<vvll> dp(n, vvll(n, vll(n, 0)));

    for (int s = 0; s < n; ++s) {
        for (int t = 0; t < n; ++t) {
            if (adj[s][t]) dp[s][t][0] = adj[s][t];

            if (adj[s][0] && adj[0][t]) {
                dp[s][t][0] =
                    dp[s][t][0] ? min(dp[s][t][0], llof(adj[s][0]) + adj[0][t])
                                : (llof(adj[s][0]) + adj[0][t]);
            }
        }
    }

    for (int k = 1; k < n; ++k) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                dp[u][v][k] = dp[u][v][k - 1];

                if (dp[u][k][k - 1] && dp[k][v][k - 1]) {
                    if (!dp[u][v][k]) {
                        dp[u][v][k] = dp[u][k][k - 1] + dp[k][v][k - 1];
                    } else {
                        dp[u][v][k] =
                            min(dp[u][v][k], dp[u][k][k - 1] + dp[k][v][k - 1]);
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (int s = 0; s < n; ++s) {
        for (int t = 0; t < n; ++t) {
            for (int k = 0; k < n; ++k) {
                ans += dp[s][t][k];
            }
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, m;
    cin >> n >> m;

    vvi adj(n, vi(n, 0));

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;

        adj[a - 1][b - 1] = c;
    }

    cout << total_fs(adj) << '\n';
    return 0;
}
