#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;
static constexpr int INF = 1e6;

vi numerize(const string &xs) {
    vi ans(sz(xs), -1);
    transform(cbegin(xs), cend(xs), begin(ans),
              [](const char c) { return inof(c) - inof('A'); });
    return ans;
}

vi distances_from(const vvi &g, const int s) {
    vi ans(sz(g), INF);
    ans[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto v : g[u]) {
            if (ans[v] != INF) continue;
            ans[v] = ans[u] + 1;
            q.push(v);
        }
    }

    return ans;
}

vvi all_distances(const vvi &g) {
    vvi ans(sz(g));

    for (int u = 0; u < sz(g); ++u) {
        ans[u] = distances_from(g, u);
    }

    return ans;
}

int total_ops(const vi &src, const vvi &d, const int t) {
    return transform_reduce(cbegin(src), cend(src), 0, plus<int>{},
                            [&d, t](const int s) { return d[s][t]; });
}

int min_ops_to_consistency(const vi &src, const vvi &g) {
    const auto d = all_distances(g);
    int ans = INF;

    for (int t = 0; t < sz(g); ++t) {
        ans = min(ans, total_ops(src, d, t));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        string xs;
        cin >> xs;

        int k;
        cin >> k;

        vvi g(AZ);
        for (int e = 0; e < k; ++e) {
            string ab;
            cin >> ab;

            const auto uv = numerize(ab);
            g[uv[0]].push_back(uv[1]);
        }
        const auto ans = min_ops_to_consistency(numerize(xs), g);
        cout << "Case #" << i << ": " << (ans >= INF ? -1 : ans) << '\n';
    }

    return 0;
}
