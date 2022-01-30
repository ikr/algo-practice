#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int happiness_delta(const int h1, const int h2) {
    if (h1 >= h2) return h1 - h2;
    return 2 * (h1 - h2);
}

constexpr ll INF = 1e16;

ll max_happiness(const vector<vector<pii>> &g) {
    const auto n = sz(g);
    vll d(n, -INF);
    d[0] = 0;

    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto [v, w] : g[u]) {
            if (d[u] + w > d[v]) {
                d[v] = d[u] + w;
                q.push(v);
            }
        }
    }

    return *max_element(cbegin(d), cend(d));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vi H(N, 0);
    for (auto &h : H) cin >> h;

    vector<vector<pii>> g(N);

    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].emplace_back(v, happiness_delta(H[u], H[v]));
        g[v].emplace_back(u, happiness_delta(H[v], H[u]));
    }

    cout << max_happiness(g) << '\n';
    return 0;
}
