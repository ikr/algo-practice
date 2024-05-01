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
    assert(lo + hi <= m);

    const auto d = min({hi - lo, k, m - lo - hi});
    lo += d;
    k -= d;
    if (!k) return lo * hi;

    const auto r1 = m - lo - hi;
    const auto d1 = min(k / 2, r1 / 2);
    k -= d1;
    k -= d1;
    lo += d1;
    hi += d1;

    const auto r2 = m - lo - hi;
    const auto d2 = min(k, r2);
    lo += d2;
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
