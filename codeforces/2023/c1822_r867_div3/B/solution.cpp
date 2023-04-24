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

        vector<int> pos;
        vector<int> neg;
        int iz = -1;

        for (int i = 0; i < n; ++i) {
            if (xs[i] == 0) {
                iz = i;
            } else if (xs[i] > 0) {
                pos.push_back(i);

            } else {
                neg.push_back(i);
            }
        }

        sort(begin(pos), end(pos),
             [&](const auto i, const auto j) { return xs[i] < xs[j]; });

        sort(begin(neg), end(neg),
             [&](const auto i, const auto j) { return xs[i] < xs[j]; });

        vector<int> idx;
        if (iz != -1) idx.push_back(iz);
        if (!pos.empty()) {
            idx.push_back(pos[0]);
            idx.push_back(pos.back());
        }
        if (sz(pos) > 1) {
            idx.push_back(pos[1]);
            idx.push_back(pos[sz(pos) - 2]);
        }
        if (!neg.empty()) {
            idx.push_back(neg[0]);
            idx.push_back(neg.back());
        }
        if (sz(neg) > 1) {
            idx.push_back(neg[1]);
            idx.push_back(neg[sz(neg) - 2]);
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
