#include <atcoder/fenwicktree>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll opt_pairs(ll k, const ll m, const ll os, const ll ts) {
    auto lo = min(os, ts);
    auto hi = max(os, ts);
    auto r = m - lo - hi;

    if (r > 0LL) {
        const auto d = min({k, hi - lo, r});
        k -= d;
        lo += d;
        r -= d;
    }

    if (lo > hi) swap(lo, hi);

    if (min(r, k) > 0LL) {
        const auto a = min(r, k) / 2;
        const auto b = min(r, k) - a;
        lo += a;
        hi += b;
        k -= a;
        k -= b;
    }

    if (lo > hi) swap(lo, hi);

    if (k && hi - lo > 1) {
        const auto d = min(k, (hi - lo) / 2);
        lo += d;
        hi -= d;
    }

    return lo * hi;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        atcoder::fenwick_tree<int> ones(n);
        atcoder::fenwick_tree<int> twos(n);

        for (int i = 0; i < n; ++i) {
            if (xs[i] == 1) {
                ones.add(i, 1);
            } else if (xs[i] == 2) {
                twos.add(i, 1);
            }
        }

        int Q;
        cin >> Q;
        for (int q = 1; q <= Q; ++q) {
            int l, r, k;
            cin >> l >> r >> k;
            --l;

            const auto os = ones.sum(l, r);
            const auto ts = twos.sum(l, r);
            cout << opt_pairs(k, r - l, os, ts) << '\n';
        }
    }

    return 0;
}
