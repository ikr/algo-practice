#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr bool contains(const vector<T> &xs, const T &x) {
    return find(cbegin(xs), cend(xs), x) != cend(xs);
}

constexpr int path_length(const vector<vector<pii>> &g,
                          const vector<int> &path) {
    int result{};
    for (int i = 1; i < ssize(path); ++i) {
        // TODO
    }
    return result;
}

int longest_path_from(const vector<vector<pii>> &g, const int u0) {
    int result{};
    const auto recur = [&](const auto self, vector<int> &pre) -> void {
        assert(!empty(pre));
        for (const auto &[v, w] : g[pre.back()]) {
            if (contains(pre, v)) continue;
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

    vector<vector<pii>> g(N);

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
