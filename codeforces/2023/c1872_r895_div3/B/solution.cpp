#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> ds(n);
        for (auto &[d, s] : ds) {
            cin >> d >> s;
        }

        ranges::sort(ds);

        int lo{INT_MAX};
        for (int i = 0; i < n; ++i) {
            const auto [d, s] = ds[i];
            const auto k = (s % 2) ? (d + s / 2) : (d + s / 2 - 1);
            lo = min(lo, k);
        }

        int hi{1};
        for (int i = 0; i < n; ++i) {
            const auto [d, s] = ds[i];
            const auto k = (s % 2) ? (d + s / 2) : (d + s / 2 - 1);
            if (k > lo) continue;
            hi = max(hi, k);
        }
        cout << hi << '\n';
    }

    return 0;
}
