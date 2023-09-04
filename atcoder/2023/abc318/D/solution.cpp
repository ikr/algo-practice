#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_total_weight(const vector<vector<ll>> &g) {
    const auto n = sz(g);
    vector<ll> dp(1 << n, 0);

    for (int v_bits = 3; v_bits < (1 << n); ++v_bits) {
        for (int u = 0; u < n - 1; ++u) {
            for (int v = u + 1; v < n; ++v) {
                if ((v_bits & (1 << u)) && (v_bits & (1 << v))) {
                    dp[v_bits] = max(
                        dp[v_bits], dp[v_bits ^ (1 << u) ^ (1 << v)] + g[u][v]);
                }
            }
        }
    }

    return dp.back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<vector<ll>> g(N, vector(N, -1LL));
    for (int u = 0; u < N - 1; ++u) {
        for (int v = u + 1; v < N; ++v) {
            ll w;
            cin >> w;
            g[u][v] = w;
            g[v][u] = w;
        }
    }

    cout << max_total_weight(g) << '\n';
    return 0;
}
