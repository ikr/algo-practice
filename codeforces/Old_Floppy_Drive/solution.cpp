#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

constexpr ll div_ceil(const ll x, const ll y) { return (x + y - 1) / y; }

pair<vector<ll>, ll> gather_prefix_sums(const vector<int> &xs) {
    const int n = xs.size();
    vector<ll> ans(n, xs[0]);
    ll hi = xs[0];

    for (int i = 1; i < n; ++i) {
        ans[i] = ans[i - 1] + xs[i];
        hi = max(hi, ans[i]);
    }

    return {ans, hi};
}

vector<pair<ll, int>> gather_proper_indices_by_value(const vector<ll> &ss) {
    const int n = ss.size();
    vector<pair<ll, int>> ans;
    ans.reserve(n / 2);

    for (int i = 0; i < n; ++i) {
        if (!i || ss[i] >= ans.back().first) ans.emplace_back(ss[i], i);
    }

    return ans;
}

ll run_time(const int n, const ll total, const ll top_s,
            const vector<pair<ll, int>> idx, const ll x) {
    const auto it = lower_bound(cbegin(idx), cend(idx), pair{x, 0});

    if (it != cend(idx)) return it->second;
    if (total <= 0) return -1;

    const ll k = div_ceil(x - top_s, total);
    const auto jt = lower_bound(cbegin(idx), cend(idx), pair{x - k * total, 0});
    assert(jt != cend(idx));

    return k * n + jt->second;
}

vector<ll> run_times(const vector<int> &as, const vector<int> &xs) {
    const auto [ss, top_s] = gather_prefix_sums(as);
    const int n = ss.size();
    const ll total = ss.back();
    const auto idx = gather_proper_indices_by_value(ss);

    const int m = xs.size();
    vector<ll> ans(m, -1);

    for (int i = 0; i < m; ++i) {
        ans[i] = run_time(n, total, top_s, idx, xs[i]);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> as(n);
        for (auto &a : as) cin >> a;

        vector<int> xs(m);
        for (auto &x : xs) cin >> x;

        cout << run_times(as, xs) << '\n';
    }

    return 0;
}
