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
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> T max_in(const pair<T, T> &xy) {
    const auto [x, y] = xy;
    return max(x, y);
}

ll max_beauty(const vector<pii> &ranges, const vvi &g) {
    vector<bool> discovered(sz(g), false);

    function<pair<ll, ll>(int)> beauty;
    beauty = [&](const int u) -> pair<ll, ll> {
        vector<pair<int, pair<ll, ll>>> bs;

        for (const auto v : g[u]) {
            if (discovered[v]) continue;
            discovered[v] = true;
            bs.emplace_back(v, beauty(v));
        }

        const auto [u_lo, u_hi] = ranges[u];
        pair<ll, ll> ans = {0, 0};

        for (const auto [v, b] : bs) {
            const auto [b_lo, b_hi] = b;
            const auto [v_lo, v_hi] = ranges[v];

            ans.first += max(abs(u_lo - v_lo) + b_lo, abs(u_lo - v_hi) + b_hi);
            ans.second += max(abs(u_hi - v_lo) + b_lo, abs(u_hi - v_hi) + b_hi);
        }

        return ans;
    };

    discovered[0] = true;
    return max_in(beauty(0));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> ranges(n);
        for (auto &[lo, hi] : ranges) cin >> lo >> hi;

        vvi g(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            g[u].push_back(v);
            g[v].push_back(u);
        }

        cout << max_beauty(ranges, g) << '\n';
    }

    return 0;
}
