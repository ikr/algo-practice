#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll first_multiple_of_x_greater_than_y(const ll x, const ll y) {
    if (x == 1LL) return y + 1LL;
    assert(x > 0LL);

    // ll k = 1;
    // while (x * k <= y) ++k;
    // return k * x;

    return x * (y / x + 1LL);
}

ll solve(const vector<ll> &xs) {
    ll ans = 0;
    for (const auto x : xs) {
        ans = first_multiple_of_x_greater_than_y(x, ans);
    }
    return ans;
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
        cout << solve(xs) << '\n';
    }

    return 0;
}
