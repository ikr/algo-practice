#include <atcoder/dsu>
#include <cassert>
#include <iostream>
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

ll min_total_frustration_of_component(const vector<vector<pii>> &G,
                                      const vector<int> &com) {
    return 1;
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
