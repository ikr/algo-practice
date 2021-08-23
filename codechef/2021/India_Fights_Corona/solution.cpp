#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T1, typename T2> struct PairHash final {
    size_t operator()(const pair<T1, T2> &p) const {
        return 31 * hash<T1>{}(p.first) + hash<T2>{}(p.second);
    }
};

static constexpr ll INF = 1e18;

using Queue = set<pair<ll, int>>;
using Graph = vector<vector<pii>>;

// Dijkstra's algorithm
vll min_costs(const Graph &g) {
    vll ans(sz(g), INF);
    ans[0] = 0;

    Queue q;
    q.emplace(0, 0);

    while (!q.empty()) {
        const auto [_, u] = *q.begin();
        q.erase(q.begin());

        for (const auto [v, w] : g[u]) {
            if (ans[v] > w + ans[u]) {
                q.erase(pair{ans[v], v});
                ans[v] = w + ans[u];
                q.emplace(ans[v], v);
            }
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, M, K;
        cin >> N >> M >> K;

        Graph g(N + 1);

        for (int i = 0; i < K; ++i) {
            int x, C;
            cin >> x >> C;

            g[x].emplace_back(0, C);
            g[0].emplace_back(x, C);
        }

        for (int i = 0; i < M; ++i) {
            int A, B, D;
            cin >> A >> B >> D;

            g[A].emplace_back(B, D);
            g[B].emplace_back(A, D);
        }

        const auto ans = min_costs(g);
        for (int i = 1; i < sz(ans); ++i) {
            if (i > 1) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
