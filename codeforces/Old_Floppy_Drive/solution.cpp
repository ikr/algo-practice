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

constexpr ll div_ceil(const ll numerator, const ll denominaotor) {
    return numerator % denominaotor ? numerator / denominaotor + 1
                                    : numerator / denominaotor;
}

vector<ll> gather_prefix_sums(const vector<ll> &xs) {
    vector<ll> ans(xs.size(), 0);
    partial_sum(cbegin(xs), cend(xs), begin(ans));
    return ans;
}

vector<pair<ll, int>> gather_indices_by_value(const vector<ll> &xs) {
    const int n = xs.size();
    vector<pair<ll, int>> ans(n);
    for (int i = 0; i < n; ++i) ans[i] = pair{xs[i], i};
    sort(begin(ans), end(ans));
    return ans;
}

ll run_time(const vector<ll> &ss, const ll top_s,
            const vector<pair<ll, int>> idx, const ll x) {
    const int n = ss.size();
    const ll total = ss.back();
    const auto it = lower_bound(cbegin(idx), cend(idx), pair{x, 0});

    if (it != cend(idx)) return it->second;
    if (total <= 0) return -1;

    const ll k = div_ceil(x - top_s, total);
    const auto jt = lower_bound(cbegin(idx), cend(idx), pair{x - k * total, 0});
    assert(jt != cend(idx));

    return k * n + jt->second;
}

vector<ll> run_times(const vector<ll> &as, const vector<ll> &xs) {
    const auto ss = gather_prefix_sums(as);
    const ll top_s = *max_element(cbegin(ss), cend(ss));
    const auto idx = gather_indices_by_value(ss);

    const int m = xs.size();
    vector<ll> ans(m, -1);

    for (int i = 0; i < m; ++i) {
        ans[i] = run_time(ss, top_s, idx, xs[i]);
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

        vector<ll> as(n);
        for (auto &a : as) cin >> a;

        vector<ll> xs(m);
        for (auto &x : xs) cin >> x;

        cout << run_times(as, xs) << '\n';
    }

    return 0;
}
