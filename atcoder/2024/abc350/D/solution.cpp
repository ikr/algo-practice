#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> edges;
    atcoder::dsu g(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g.merge(u, v);

        edges.emplace_back(min(u, v), max(u, v));
    }

    unordered_map<int, int> edges_by_leader;
    for (const auto &[u, v] : edges) {
        assert(g.leader(u) == g.leader(v));
        ++edges_by_leader[g.leader(u)];
    }

    ll result{};

    for (const auto &vs : g.groups()) {
        const ll n = sz(vs);
        if (n < 2) continue;
        const ll hi = n * (n - 1) / 2LL;

        const ll m = edges_by_leader.at(g.leader(vs[0]));
        result += hi - m;
    }

    cout << result << '\n';
    return 0;
}
