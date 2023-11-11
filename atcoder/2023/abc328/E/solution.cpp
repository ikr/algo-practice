#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
static constexpr ll Inf = 1e18;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_tree(const int N, const vector<pair<int, int>> &edges,
             const int ebits) {
    atcoder::dsu cs(N);
    for (int i = 0; i < sz(edges); ++i) {
        if (ebits & (1 << i)) {
            const auto [u, v] = edges[i];
            if (cs.same(u, v)) return false;
            cs.merge(u, v);
        }
    }
    return cs.size(0) == N;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    ll K;
    cin >> K;

    vector<pair<int, int>> edges;
    vector<vector<ll>> AM(N, vector<ll>(N, Inf));

    for (int i = 0; i < M; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        --u;
        --v;
        edges.emplace_back(min(u, v), max(u, v));

        AM[u][v] = w;
        AM[v][u] = w;
    }

    const auto weight = [&](const int ebits) -> ll {
        ll w{};
        for (int i = 0; i < sz(edges); ++i) {
            if (ebits & (1 << i)) {
                const auto [u, v] = edges[i];
                w += AM[u][v];
                w %= K;
            }
        }
        return w;
    };

    ll ans = K - 1;
    for (int ebits = 0; ebits < (1 << M); ++ebits) {
        if (__builtin_popcount(ebits) != N - 1 || !is_tree(N, edges, ebits)) {
            continue;
        }
        ans = min(ans, weight(ebits));
    }
    cout << ans << '\n';
    return 0;
}
