#include <bits/stdc++.h>
using namespace std;

int longest_path_from(const vector<vector<pair<int, int>>> &g, const int u0) {
    const auto n = ssize(g);
    vector<int> D(n, -1);
    D[u0] = 0;

    const auto recur = [&](const auto &self, const int u) -> void {
        for (const auto &[v, w] : g[u]) {
            if (D[v] != -1) continue;
            self(self, v);
            D[u] = max(D[u], w + D[v]);
        }
    };

    recur(recur, u0);
    return *max_element(cbegin(D), cend(D));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, int>>> g(N);

    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    int result{};

    for (int u = 0; u < N; ++u) {
        result = max(result, longest_path_from(g, u));
    }

    cout << result << '\n';
    return 0;
}
