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

    queue<int> q;
    for (int u = 0; u < n; ++u) {
        if (!ideg[u]) q.push(u);
    }

    vector<int> ans(n, 0);
    int cur{};

    while (!q.empty()) {
        if (sz(q) != 1) return {};
        const auto u = q.front();
        q.pop();
        ans[u] = cur;
        ++cur;

        for (const auto v : g[u]) {
            --ideg[v];
            if (!ideg[v]) q.push(v);
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

    for (auto &row : g) {
        sort(begin(row), end(row));
        row.erase(unique(begin(row), end(row)), end(row));
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
