#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_sum(const vector<ll> &xs) {
    vector<pll> D0(sz(xs)); // prev kept intact
    vector<pll> D1(sz(xs)); // swapped with prev

    D0[0] = {xs[0], xs[0]}; // (s b) — max sum s, last element b
    D1[0] = {xs[0], xs[0]};

    for (int i = 1; i < sz(xs); ++i) {
        {
            const auto [s0, b0] = D0[i - 1];
            const auto [s1, b1] = D0[i - 1];

            D0[i] = pll{(s0 >= s1 ? s0 : s1) + xs[i], xs[i]};
        }

        D1[i] = [&]() -> pll {
            const auto [s0, b0] = D0[i - 1];
            const auto [s1, b1] = D0[i - 1];

            const auto sa = s0 - b0;
            const auto sb = s1 - b1;

            if (sa >= sb) {
                return {sa - xs[i], -b0};
            } else {
                return {sb - xs[i], -b1};
            }
        }();
    }

    return max(D0.back().first, D1.back().first);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_sum(xs) << '\n';
    }

    return 0;
}
