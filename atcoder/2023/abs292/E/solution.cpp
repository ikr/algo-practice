#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const vector<vector<int>> &g) {
    const auto n = sz(g);
    vector<vector<int>> m(n, vector(n, 0));
    for (int u = 0; u < n; ++u) {
        for (const auto v : g[u]) {
            m[u][v] = 1;
        }
    }

    vector<vector<int>> m2(n, vector(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int s{};

            for (const auto v : g[i]) {
                s += m[v][j];
            }

            m2[i][j] = s;
        }
    }

    int ans{};
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            ans += (m2[u][v] && !m[u][v]);
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N);
    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
    }

    cout << min_ops(g) << '\n';
    return 0;
}
