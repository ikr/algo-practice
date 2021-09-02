#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

static constexpr ll INF = 1e18;
using Queue = set<pair<ll, int>>;

// Dijkstra's algo
vll min_costs(const vvll &g, const int s) {
    vll ans(sz(g), INF);
    ans[s] = 0;

    Queue q;
    q.emplace(0LL, s);

    while (!q.empty()) {
        const auto [_, u] = *q.begin();
        q.erase(q.begin());

        for (int v = 0; v < sz(g); ++v) {
            const auto w = g[u][v];

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

    int N, K, S;
    cin >> N >> K >> S;
    --S;

    vi al(N, -1);
    for (auto &x : al) {
        cin >> x;
        --x;
        assert(x >= 0 && x < K);
    }

    vvll g(K, vll(K, INF));
    for (int p = 0; p < N; ++p) {
        for (int a = 0; a < K; ++a) {
            ll w;
            cin >> w;
            if (w == -1) w = INF;

            g[al[p]][a] = min(g[al[p]][a], w);
        }
    }

    const auto d = min_costs(g, al[S]);
    vll ans(N, -1);

    for (int p = 0; p < N; ++p) {
        if (d[al[p]] < INF) {
            ans[p] = d[al[p]];
        }
    }

    cout << ans << '\n';
    return 0;
}
