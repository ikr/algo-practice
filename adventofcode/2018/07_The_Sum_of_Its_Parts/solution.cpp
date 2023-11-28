#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

static const string Pref{"Step "};
static const string Suff{"X can begin."};

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string deterministic_toposort(const int n, const vector<pii> &edges) {
    vector<vector<int>> adj(n);
    vector<int> deg(n);

    for (const auto &[u, v] : edges) {
        adj[u].push_back(v);
        ++deg[v];
    }

    set<int> pq;

    for (int u = 0; u < n; ++u) {
        if (deg[u] == 0) pq.insert(u);
    }

    string result;
    while (!empty(pq)) {
        const auto u = *cbegin(pq);
        pq.erase(cbegin(pq));
        result += chof('A' + u);

        for (const auto v : adj[u]) {
            if (--deg[v] == 0) pq.insert(v);
        }
    }
    return result;
}

int main() {
    int n{1};
    vector<pii> edges;

    for (string line; getline(cin, line);) {
        const char U = line[sz(Pref)];
        const char V = line[sz(line) - sz(Suff)];

        edges.emplace_back(U - 'A', V - 'A');
        n = max(n, max(U, V) - 'A' + 1);
    }

    cout << deterministic_toposort(n, edges) << '\n';
    return 0;
}
