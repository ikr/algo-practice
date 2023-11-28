#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using pii = pair<int, int>;

static const string Pref{"Step "};
static const string Suff{"X can begin."};
static constexpr int BaseSeconds = 0;
static constexpr int NumWorkers = 2;

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int total_work_time_seconds(const int n, const vector<pii> &edges) {
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

    array<int, NumWorkers> worker_time{};
    cerr << worker_time << endl;

    while (!empty(pq)) {
        const auto u = *cbegin(pq);
        pq.erase(cbegin(pq));

        const auto it = ranges::min_element(worker_time);
        *it += BaseSeconds + u + 1;
        cerr << worker_time << endl;

        for (const auto v : adj[u]) {
            if (--deg[v] == 0) pq.insert(v);
        }
    }

    return *ranges::max_element(worker_time);
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

    cout << total_work_time_seconds(n, edges) << '\n';
    return 0;
}
