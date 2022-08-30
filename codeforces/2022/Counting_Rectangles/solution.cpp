#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<ll> partial_sums_of_areas(const vector<pii> &rs) {
    const auto n = sz(rs);
    vector<ll> result(n);
    result[0] = 1LL * rs[0].first * rs[0].second;

    for (int i = 1; i < n; ++i) {
        result[i] = result[i - 1] + 1LL * rs[i].first * rs[i].second;
    }

    return result;
}

vector<ll> total_areas_of_slices(const vector<pii> &rs,
                                 const vector<pair<pii, pii>> &qs) {
    const auto ss = partial_sums_of_areas(rs);

    vector<ll> result(sz(qs), 0);

    for (int k = 0; k < sz(qs); ++k) {
        const auto &[lo, hi] = qs[k];
        const auto [lo_a, lo_b] = lo;
        const auto it =
            lower_bound(cbegin(rs), cend(rs), pii{lo_a + 1, lo_b + 1});
        if (it == cend(rs)) continue;

        const auto [hi_a, hi_b] = hi;
        const auto jt = lower_bound(cbegin(rs), cend(rs), pii{hi_a, hi_b});

        const auto i = inof(distance(cbegin(rs), it));
        const auto j = inof(distance(cbegin(rs), jt));

        result[k] = ss[j - 1] - (i ? ss[i - 1] : 0LL);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<pii> rs(n);
        for (auto &[a, b] : rs) cin >> a >> b;
        sort(begin(rs), end(rs));

        vector<pair<pii, pii>> qs(q);
        for (auto &[lo, hi] : qs) {
            cin >> lo.first >> lo.second >> hi.first >> hi.second;
        }

        for (const auto s : total_areas_of_slices(rs, qs)) {
            cout << s << '\n';
        }
    }

    return 0;
}
