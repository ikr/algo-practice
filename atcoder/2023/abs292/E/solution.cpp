#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const vector<vector<int>> &g, const set<pii> &es) {
    set<pii> ans;

    queue<pii> q;
    for (const auto &uv : es) {
        q.push(uv);
    }

    while (!q.empty()) {
        const auto [u, v] = q.front();
        q.pop();

        for (const auto w : g[v]) {
            const pii uw{u, w};
            if (es.count(uw) || ans.count(uw)) continue;

            ans.insert(uw);
            q.push(uw);
        }
    }

    return sz(ans);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N);
    set<pii> es;
    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        es.emplace(u, v);
    }

    cout << min_ops(g, es) << '\n';
    return 0;
}
