#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_total_weight(const vector<vector<ll>> &g) {
    const auto n = sz(g);
    set<pii> best_set{{0, 1}};

    const auto included_edge = [&](const int v) -> optional<pii> {
        for (int u = 0; u < v; ++u) {
            if (best_set.contains({u, v})) return pii{u, v};
        }
        return nullopt;
    };

    for (int v = 2; v < n; ++v) {
        priority_queue<pair<ll, int>> pq;

        for (int u = 0; u < v; ++u) {
            const auto mbe = included_edge(u);
            if (mbe) {
                const auto [a, b] = *mbe;
                pq.emplace(g[u][v] - g[a][b], u);
            } else {
                pq.emplace(g[u][v], u);
            }
        }

        const auto [_, u] = pq.top();
        const auto mbe = included_edge(u);
        if (mbe) {
            const auto [a, b] = *mbe;
            best_set.erase({a, b});
        }
        best_set.emplace(u, v);
    }

    ll best_total{};
    for (const auto &[a, b] : best_set) best_total += g[a][b];
    return best_total;
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
