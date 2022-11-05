#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (auto &row : g) {
        sort(begin(row), end(row));
        cout << sz(row);
        if (!row.empty()) cout << ' ';

        for (auto i = row.cbegin(); i != row.cend(); ++i) {
            if (i != row.cbegin()) cout << ' ';
            cout << ((*i) + 1);
        }

        cout << '\n';
    }

    return 0;
}
