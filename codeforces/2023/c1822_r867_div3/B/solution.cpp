#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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

        int n_lo = INT_MAX;
        int in_lo = -1;

        int n_hi = INT_MIN;
        int in_hi = -1;

        int p_lo = INT_MAX;
        int ip_lo = -1;

        int p_hi = INT_MIN;
        int ip_hi = -1;

        int iz = -1;

        for (int i = 0; i < n; ++i) {
            if (xs[i] == 0) {
                iz = i;
            } else if (xs[i] < 0) {
                if (xs[i] < n_lo) {
                    n_lo = xs[i];
                    in_lo = i;
                }

                if (xs[i] > n_hi) {
                    n_hi = xs[i];
                    in_hi = i;
                }
            } else {
                assert(xs[i] > 0);
                if (xs[i] < p_lo) {
                    p_lo = xs[i];
                    ip_lo = i;
                }

                if (xs[i] > p_hi) {
                    p_hi = xs[i];
                    ip_hi = i;
                }
            }
        }

        vector<int> idx;
        for (const auto i : {iz, in_lo, in_hi, ip_lo, ip_hi}) {
            if (i >= 0) idx.push_back(i);
        }
        sort(begin(idx), end(idx));
        idx.erase(unique(begin(idx), end(idx)), end(idx));
        assert(!idx.empty());

        const auto ans = [&]() -> ll {
            assert(sz(xs) >= 2);
            if (sz(idx) == 1) return xs[0] * xs[1];

            ll hi = LONG_LONG_MIN;
            for (int i = 0; i < sz(idx) - 1; ++i) {
                for (int j = i + 1; j < sz(idx); ++j) {
                    hi = max(hi, 1LL * xs[idx[i]] * xs[idx[j]]);
                }
            }
            return hi;
        }();
        cout << ans << '\n';
    }

    return 0;
}
