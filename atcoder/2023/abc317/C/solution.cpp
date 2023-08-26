#include <bits/stdc++.h>
using namespace std;

static constexpr int Inf = 1'000'000'000;

int longest_path_from(const vector<vector<int>> &g, const int u) {
    const auto n = ssize(g);
    vector<int> D(n, -1);

    D[u] = 0;
    set<pair<int, int>> q;
    q.emplace(0, u);

    while (!q.empty()) {
        const auto v = cbegin(q)->second;
        q.erase(cbegin(q));

        for (int e = 0; e < n; ++e) {
            if (g[v][e] == Inf) continue;

            const auto to = e;
            const auto len = g[v][e];

            if (D[to] == -1 || D[v] + len > D[to]) {
                q.erase({-D[to], to});
                D[to] = D[v] + len;
                q.emplace(-D[to], to);
            }
        }
    }

    int result{};
    for (const auto d : D) {
        if (d != Inf) result = max(result, d);
    }
    return result;
}

int path_length(const vector<vector<int>> &g, const vector<int> &path) {
    int result{};
    for (int i = 1; i < ssize(path); ++i) {
        if (g[path[i - 1]][path[i]] == Inf) return 0;
        result += g[path[i - 1]][path[i]];
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N, vector(N, Inf));

    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        g[u][v] = w;
        g[v][u] = w;
    }

    int result{};

    for (int u = 0; u < N; ++u) {
        result = max(result, longest_path_from(g, u));
    }

    cout << result << '\n';
    return 0;
}
