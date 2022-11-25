#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<vector<pii>> &g, const int a, const int b) {
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, a, b;
        cin >> n >> a >> b;
        --a;
        --b;

        vector<vector<pii>> g(n);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u;
            --v;

            g[u].emplace_back(v, w);
        }

        cout << (is_possible(g, a, b) ? "YES" : "NO") << '\n';
    }

    return 0;
}
