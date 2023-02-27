#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> construct_permutation(const vector<vector<int>> &g) {
    const auto n = sz(g);
    vector<int> ideg(n, 0);

    for (int u = 0; u < n; ++u) {
        for (const auto v : g[u]) ++ideg[v];
    }

    vector<int> zus;
    for (int u = 0; u < n; ++u) {
        if (ideg[u] == 0) zus.push_back(u);
    }
    if (sz(zus) != 1) return {};

    vector<int> ans;

    for (;;) {
        const auto zu = zus[0];
        ans.push_back(zu);
        if (sz(ans) == n) return ans;
        zus.clear();

        for (const auto v : g[zu]) {
            --ideg[v];
            if (ideg[v] == 0) zus.push_back(v);
        }

        if (sz(zus) != 1) return {};
    }

    return {};
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

    const auto ans = construct_permutation(g);

    if (ans.empty()) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        for (auto i = ans.cbegin(); i != ans.cend(); ++i) {
            if (i != ans.cbegin()) cout << ' ';
            const auto a = (*i) + 1;
            cout << a;
        }
        cout << '\n';
    }

    return 0;
}
