#include <algorithm>
#include <atcoder/dsu>
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<pii>> frustration_graph(const vector<int> &X,
                                      const vector<int> &C) {
    const int N = sz(X);
    assert(sz(C) == N);
    vector<vector<pii>> G(N);

    for (int i = 0; i < N; ++i) {
        G[X[i]].emplace_back(i, C[i]);
    }

    return G;
}

vector<vector<int>> all_components(const vector<vector<pii>> &G) {
    const auto N = sz(G);
    atcoder::dsu d(N);

    for (int u = 0; u < N; ++u) {
        for (const auto &[v, _] : G[u]) {
            d.merge(u, v);
        }
    }

    return d.groups();
}

using tri = tuple<int, int, int>;

map<int, int> indices_by_value(const vector<int> &xs) {
    map<int, int> result;
    for (int i = 0; i < sz(xs); ++i) {
        result[xs[i]] = i;
    }
    return result;
}

vector<int> topo_sort(const vector<int> &vs, const multimap<int, int> &g) {
    set<int> done;
    vector<int> result;

    const auto recur = [&](const auto self, const int u) -> void {
        assert(!done.count(u));
        const auto [first, last] = g.equal_range(u);

        for (auto it = first; it != last; ++it) {
            const auto v = it->second;
            if (done.count(v)) continue;
            self(self, v);
        }

        result.push_back(u);
        done.insert(u);
    };

    for (const auto u : vs) {
        if (!done.count(u)) {
            recur(recur, u);
        }
    }

    reverse(begin(result), end(result));
    return result;
}

ll min_total_frustration_of_component(const vector<vector<pii>> &G,
                                      const vector<int> &com) {
    assert(!com.empty());

    priority_queue<tri> q;
    for (const auto u : com) {
        for (const auto &[v, c] : G[u]) {
            q.emplace(c, u, v);
        }
    }

    const auto idx = indices_by_value(com);
    multimap<int, int> g;
    atcoder::dsu d(sz(com));

    while (d.size(idx.at(com[0])) != sz(com)) {
        assert(!q.empty());

        const auto [_, u, v] = q.top();
        q.pop();
        if (d.same(idx.at(u), idx.at(v))) continue;

        d.merge(idx.at(u), idx.at(v));
        g.emplace(v, u);
    }

    const auto ord = topo_sort(com, g);
    const auto ord_idx = indices_by_value(ord);

    ll result{};
    for (const auto u : com) {
        for (const auto &[v, c] : G[u]) {
            if (ord_idx.at(u) < ord_idx.at(v)) result += c;
        }
    }
    return result;
}

ll min_total_frustration(const vector<int> &X, const vector<int> &C) {
    const auto G = frustration_graph(X, C);
    ll result{};

    for (const auto &com : all_components(G)) {
        result += min_total_frustration_of_component(G, com);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> X(N);
    for (auto &x : X) {
        cin >> x;
        --x;
    }

    vector<int> C(N);
    for (auto &c : C) cin >> c;

    cout << min_total_frustration(X, C) << '\n';
    return 0;
}
