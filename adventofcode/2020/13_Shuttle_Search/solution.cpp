#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace internal {
constexpr ll safe_mod(ll x, const ll m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

constexpr pair<ll, ll> inv_gcd(ll a, const ll b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};

    ll s = b, t = a;
    ll m0 = 0, m1 = 1;

    while (t) {
        const ll u = s / t;
        s -= t * u;
        m0 -= m1 * u;

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }

    if (m0 < 0) m0 += b / s;
    return {s, m0};
}
} // namespace internal

constexpr ll inv_mod(const ll x, const ll m) {
    assert(1 <= m);
    const auto z = internal::inv_gcd(x, m);
    assert(z.first == 1);
    return z.second;
}

vector<string> tokenize(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

vector<pair<ll, int>> gather_ids_with_deltas(const vector<string> &tt) {
    const int n = tt.size();
    vector<pair<ll, int>> ans{{stoll(tt.front()), 0}};

    for (int i = 1; i < n; ++i) {
        if (tt[i] == "x") continue;
        ans.emplace_back(stoll(tt[i]), i);
    }

    return ans;
}

ll solve(const vector<string> &tt) {
    const auto ids_ds = gather_ids_with_deltas(tt);
    const int sz = ids_ds.size();

    const ll prod = accumulate(
        cbegin(ids_ds), cend(ids_ds), 1LL,
        [](const ll agg, const pair<ll, int> &p) { return agg * p.first; });

    vector<ll> ys(sz, 0);
    for (int i = 0; i < sz; ++i) {
        ys[i] = prod / ids_ds[i].first;
    }

    vector<ll> zs(sz, 0);
    for (int i = 0; i < sz; ++i) {
        zs[i] = inv_mod(ys[i], ids_ds[i].first);
    }

    ll ans = 0;

    for (int i = 0; i < sz; ++i) {
        ans += internal::safe_mod(-ids_ds[i].second, ids_ds[i].first) * ys[i] *
               zs[i];

        ans %= prod;
    }

    return ans;
}

int main() {
    int t;
    cin >> t;
    string s;
    cin >> s;

    cout << solve(tokenize(regex(","), s)) << '\n';
    return 0;
}
