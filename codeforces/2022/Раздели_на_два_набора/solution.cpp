#include <bits/stdc++.h>
using namespace std;

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

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> graph(const vector<pii> &ab) {
    const auto n = sz(ab);
    map<int, vector<int>> idx;

    for (int i = 0; i < n; ++i) {
        const auto [a, b] = ab[i];
        idx[a].push_back(i);
        idx[b].push_back(i);
    }

    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        const auto [a, b] = ab[i];

        for (const auto j : idx[a]) {
            if (j != i) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }

        for (const auto j : idx[b]) {
            if (j != i) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    for (auto &vs : g) {
        sort(begin(vs), end(vs));
        vs.erase(unique(begin(vs), end(vs)), end(vs));
    }

    return g;
}

enum class Side { A, B };

constexpr Side opposite(const Side x) {
    return x == Side::A ? Side::B : Side::A;
}

// Reference:
// https://cp-algorithms.com/graph/bipartite-check.html#implementation
//
bool is_bipartite(const vector<vector<int>> &g) {
    const auto n = sz(g);
    vector<optional<Side>> side(n, nullopt);

    bool result = true;
    queue<int> q;

    for (int st = 0; st < n; ++st) {
        if (side[st]) continue;

        q.push(st);
        side[st] = Side::A;

        while (!q.empty()) {
            const int u = q.front();
            q.pop();

            for (const auto v : g[u]) {
                if (!side[v]) {
                    side[v] = opposite(*side[u]);
                    q.push(v);
                } else if (*side[v] == *side[u]) {
                    result = false;
                }
            }
        }
    }

    return result;
}

bool is_possible(const vector<pii> &ab) {
    if (any_of(cbegin(ab), cend(ab),
               [](const pii p) { return p.first == p.second; })) {
        return false;
    }

    const auto g = graph(ab);
    return is_bipartite(g);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> ab(n);
        for (auto &[a, b] : ab) {
            cin >> a >> b;
        }

        cout << (is_possible(ab) ? "YES" : "NO") << '\n';
    }

    return 0;
}
