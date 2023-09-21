#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using ll = long long;

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

        const auto it0 = find(begin(xs), end(xs), 0LL);
        if (it0 != cend(xs)) {
            ++(*it0);
            const auto ans =
                accumulate(cbegin(xs), cend(xs), 1LL, multiplies<ll>{});
            cout << ans << '\n';
        } else {
            ll ans{};
            for (int i = 0; i < sz(xs); ++i) {
                auto ys = xs;
                ++ys[i];

                const auto cur =
                    accumulate(cbegin(ys), cend(ys), 1LL, multiplies<ll>{});
                ans = max(ans, cur);
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
