#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
static constexpr int INF = 1'000'000'000;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

void sweep_from_u0(const vector<vector<int>> &g, string &coloring, const int u0,
                   const int req_dist) {
    const auto n = sz(g);
    vector<int> D(n, INF);
    D[u0] = 0;
    queue<int> q;
    q.push(u0);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto v : g[u]) {
            if (D[v] != INF) continue;
            D[v] = D[u] + 1;

            if (D[v] > req_dist) return;
            if (D[v] == req_dist) {
                coloring[v] = '1';
            } else {
                assert(D[v] < req_dist);
                coloring[v] = '0';
            }

            q.push(v);
        }
    }
}

bool verify_for_u0(const vector<vector<int>> &g, const string &coloring,
                   const int u0, const int req_dist) {
    assert(req_dist > 0);
    if (coloring[u0] == '1') return false;

    const auto n = sz(g);
    vector<int> D(n, INF);
    D[u0] = 0;
    queue<int> q;
    q.push(u0);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto v : g[u]) {
            if (D[v] != INF) continue;
            D[v] = D[u] + 1;

            if (D[v] > req_dist) return false;
            if (coloring[v] == '1') return D[v] == req_dist;
            q.push(v);
        }
    }

    return false;
}

string find_coloring(const vector<vector<int>> &g,
                     const vector<pii> &req_dist) {
    const auto n = sz(g);
    if (req_dist.empty()) return string(n, '1');

    string coloring(n, '0');
    for (const auto &[p, d] : req_dist) {
        if (d == 0) coloring[p] = '1';
    }

    for (const auto &[p, d] : req_dist) sweep_from_u0(g, coloring, p, d);

    for (const auto &[p, d] : req_dist) {
        if (d == 0 && coloring[p] != '1') return "";
        if (d != 0 && !verify_for_u0(g, coloring, p, d)) return "";
    }

    return coloring;
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
        g[v].push_back(u);
    }

    int K;
    cin >> K;
    vector<pii> req_dist(K);
    for (auto &[p, d] : req_dist) {
        cin >> p >> d;
        --p;
    }

    const auto ans = find_coloring(g, req_dist);
    if (ans.empty()) {
        cout << "No\n";
    } else {
        cout << "Yes\n" << ans << '\n';
    }
    return 0;
}
