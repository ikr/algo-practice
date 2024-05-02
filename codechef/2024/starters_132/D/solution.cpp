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

    while (k && lo + hi < m) {
        const auto d = max(1LL, min({hi - lo, k, m - hi - lo}));
        lo += d;
        if (lo > hi) swap(lo, hi);
        k -= d;
    }

    while (k && lo != hi) {
        const auto d = max(1LL, min(k, hi - lo));
        lo += d;
        hi -= d;
        if (lo > hi) swap(lo, hi);
        k -= d;
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
