#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int max_teleports(const int c, const vector<int> &xs) {
    const auto n = sz(xs);
    vector<ll> rhs_ss(1, xs[div_ceil(n, 2)]);
    rhs_ss.reserve(n / 2);
    for (int i = n - 1; i > n / 2; --i) {
        rhs_ss.push_back(rhs_ss.back() + xs[i]);
    }

    int ans{};
    for (int i = 0; i <= n / 2; ++i) {
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_teleports(c, xs) << '\n';
    }

    return 0;
}
