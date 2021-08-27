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

static constexpr ll INF = 1e18;

vll min_distances(const vector<vector<pii>> &g) {
    const int n = sz(g);

    vll ans(n, INF);
    ans[0] = 0;

    vi hops(n, n * n);
    hops[0] = 0;
    vector<bool> explored(n, false);

    for (int i = 0; i < n; ++i) {
        int u = -1;

        for (int j = 0; j < n; j++) {
            if (!explored[j] && (u == -1 || ans[j] < ans[u])) {
                u = j;
            }
        }

        if (ans[u] == INF) break;

        explored[u] = true;

        for (const auto e : g[u]) {
            const auto v = e.first;
            const auto w = e.second;

            const int curr_hops = hops[u];

            if (ans[u] + w * (curr_hops + 1LL) < ans[v]) {
                ans[v] = ans[u] + w * (curr_hops + 1LL);
                hops[v] = curr_hops + 1;
            }
        }
    }

    transform(cbegin(ans), cend(ans), begin(ans),
              [](const auto x) { return x == INF ? -1 : x; });
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, m;
    cin >> n >> m;

    vector<vector<pii>> g(n);
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        --x;
        --y;

        g[x].emplace_back(y, w);
        g[y].emplace_back(x, w);
    }

    for (const auto d : min_distances(g)) cout << d << '\n';
    return 0;
}
