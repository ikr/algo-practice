#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr bool contains(const vector<T> &xs, const T &x) {
    return find(cbegin(xs), cend(xs), x) != cend(xs);
}

constexpr int path_length(const vector<vector<int>> &g,
                          const vector<int> &path) {
    int result{};
    for (int i = 1; i < ssize(path); ++i) {
        result += g[path[i - 1]][path[i]];
    }
    return result;
}

int longest_path_from(const vector<vector<int>> &g, const int u0) {
    int result{};
    const auto recur = [&](const auto self, vector<int> &pre) -> void {
        assert(!empty(pre));
        const auto u = pre.back();
        for (int v = 0; v < ssize(g); ++v) {
            if (g[u][v] == -1 || contains(pre, v)) continue;
            pre.push_back(v);
            result = max(result, path_length(g, pre));
            self(self, pre);
            pre.pop_back();
        }
    };
    vector<int> pre{u0};
    recur(recur, pre);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N, vector<int>(N, -1));

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
