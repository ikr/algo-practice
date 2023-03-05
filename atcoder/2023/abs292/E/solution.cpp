#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> vertices_reachabe_from_u(const vector<vector<int>> &g,
                                     const int u) {
    vector<int> ans;
    vector<bool> done(sz(g), false);
    queue<int> q;
    q.push(u);
    done[u] = true;

    while (!q.empty()) {
        const auto v = q.front();
        q.pop();

        for (const auto v_ : g[v]) {
            if (done[v_]) continue;
            ans.push_back(v_);
            done[v_] = true;
            q.push(v_);
        }
    }

    return ans;
}

int min_ops(const vector<vector<int>> &g, const set<pii> &es) {
    int ans{};
    for (int u = 0; u < sz(g); ++u) {
        const auto vs = vertices_reachabe_from_u(g, u);
        for (const auto v : vs) {
            if (!es.count({u, v})) ++ans;
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
