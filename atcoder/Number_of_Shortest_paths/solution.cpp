#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using mint = atcoder::modint1000000007;

static constexpr int INF = 1e9;

vi distances(const vvi &g) {
    const int n = sz(g);

    vi ans(n, INF);
    ans[0] = 0;

    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        const int u = q.front();
        q.pop();

        for (const auto v : g[u]) {
            if (ans[v] != INF) continue;
            ans[v] = ans[u] + 1;
            q.push(v);
        }
    }

    return ans;
}

int shortest_paths_num(const vvi &g) {
    const int n = sz(g);
    const auto ds = distances(g);

    function<mint(int, int)> recur;
    recur = [&](const int u, const int d) -> mint {
        if (d == 0) return 1;

        mint ans = 0;

        for (const auto v : g[u]) {
            if (ds[v] == d - 1) {
                ans += recur(v, d - 1);
            }
        }

        return ans;
    };

    return recur(n - 1, ds.back()).val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vvi g(n, vi{});
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    cout << shortest_paths_num(g) << '\n';

    return 0;
}
