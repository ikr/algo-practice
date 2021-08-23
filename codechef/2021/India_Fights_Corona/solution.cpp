#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
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

using Weig = unordered_map<pii, int, PairHash<int, int>>;

static constexpr ll INF = 1e18;

using Queue = set<pair<ll, int>>;

// Dijkstra's algorithm
vll min_costs(const vvi &g, const Weig &w) {
    vll ans(sz(g), INF);
    ans[0] = 0;

    Queue front;
    for (const auto u : g[0]) {
        const ll c = w.at(pii{0, u});
        front.emplace(-c, u);
        ans[u] = c;
    }

    while (!front.empty()) {
        const auto [c_, u] = *front.begin();
        front.erase(front.begin());

        for (const auto v : g[u]) {
            const ll c = w.at(pii{u, v});

            if (ans[v] > c + ans[u]) {
                front.erase(pair{ans[v], v});
                ans[v] = c + ans[u];
                front.emplace(-ans[v], v);
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

        vvi g(N + 1);
        Weig w;

        for (int i = 0; i < K; ++i) {
            int x, C;
            cin >> x >> C;

            g[x].push_back(0);
            g[0].push_back(x);

            w[pii{0, x}] = C;
            w[pii{x, 0}] = C;
        }

        for (int i = 0; i < M; ++i) {
            int A, B, D;
            cin >> A >> B >> D;

            g[A].push_back(B);
            g[B].push_back(A);

            w[pii{A, B}] = D;
            w[pii{B, A}] = D;
        }

        const auto ans = min_costs(g, w);
        for (int i = 1; i < sz(ans); ++i) {
            if (i > 1) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
