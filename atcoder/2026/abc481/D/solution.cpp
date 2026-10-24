#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s;
    --t;

    vector<vector<int>> g(n, vector<int>{});
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
    }

    for (auto &vs : g) {
        ranges::sort(vs);
    }

    vector<int> d(n, -1);
    d[s] = 0;

    deque<int> q{s};
    while (!q.empty()) {
        const int u = q.front();
        q.pop_front();

        for (int i = 0; i < sz(g[u]); ++i) {
            const int v = g[u][i];
            const int candidate_d = d[u] + (i != 0);

            if (d[v] == -1 || candidate_d < d[v]) {
                d[v] = candidate_d;

                if (i == 0) {
                    q.push_front(v);
                } else {
                    q.push_back(v);
                }
            }
        }
    }

    cout << d[t] << '\n';
    return 0;
}
