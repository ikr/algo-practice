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

ll rgb_paintings_num(const vvi &g) {
    const int n = sz(g);
    vvll dp(n, vll(8, 0));

    dp[0][1] = 1;
    dp[0][2] = 1;
    dp[0][4] = 1;

    for (int u = 1; u < n; ++u) {
        const set<int> adj(cbegin(g[u]), cend(g[u]));

        ll mul = 1LL;

        for (int v = 0; v < u; ++v) {
            if (!adj.count(v)) {
                mul *= accumulate(cbegin(dp[v]), cend(dp[v]), 0LL, plus<ll>{});
                continue;
            }

            for (int sh = 0; sh < 3; ++sh) {
                const int mask = 1 << sh;

                for (int bits = 1; bits < 8; ++bits) {
                    if ((bits & mask) == 0) {
                        dp[u][bits | mask] += dp[v][bits];
                    }
                }
            }
        }

        for (int bits = 1; bits < 8; ++bits) {
            dp[u][bits] *= mul;
        }
    }

    return accumulate(cbegin(dp.back()), cend(dp.back()), 0LL, plus<ll>{});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, m;
    cin >> n >> m;

    vvi g(n, vi{});

    while (m--) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    cout << rgb_paintings_num(g) << '\n';
    return 0;
}
