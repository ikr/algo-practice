#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

static const string Pref{"Step "};
static const string Suff{"X can begin."};
static constexpr int BaseSeconds = 60;
static constexpr int NumWorkers = 5;

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

    int seconds_total{};
    vector<pii> remaining_work; // (effort, u)

    while (!empty(pq) || !empty(remaining_work)) {
        while (!empty(pq) && sz(remaining_work) < NumWorkers) {
            const auto u = *cbegin(pq);
            pq.erase(cbegin(pq));
            remaining_work.emplace_back(BaseSeconds + u + 1, u);
            continue;
        }

        if (!empty(remaining_work)) {
            sort(rbegin(remaining_work), rend(remaining_work));
            const auto elapsed = remaining_work.back().first;
            seconds_total += elapsed;

            while (!empty(remaining_work) &&
                   remaining_work.back().first == elapsed) {
                const auto u = remaining_work.back().second;
                remaining_work.pop_back();

                for (const auto v : adj[u]) {
                    if (--deg[v] == 0) pq.insert(v);
                }
            }

            for (auto &[effort, u] : remaining_work) effort -= elapsed;
        }
    }

    return seconds_total;
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
