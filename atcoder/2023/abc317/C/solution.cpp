#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

static constexpr int Inf = 0;

int path_length(const vector<vector<int>> &g, const vector<int> &path) {
    int result{};
    for (int i = 1; i < ssize(path); ++i) {
        if (g[path[i - 1]][path[i]] == Inf) return Inf;
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
    atcoder::dsu cs(N);

    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        g[u][v] = w;
        g[v][u] = w;
        cs.merge(u, v);
    }

    int result{};

    for (const auto &us : cs.groups()) {
        auto seq = us;
        ranges::sort(seq);

        do {
            result = max(result, path_length(g, seq));
        } while (next_permutation(begin(seq), end(seq)));
    }

    cout << result << '\n';
    return 0;
}
