#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_remaining_beauties_sum(const vi &h, const vi &a) {
    vll dp(sz(h), 0);

    for (int i = 0; i < sz(h); ++i) {
        ll best_val = 0;

        for (int j = i - 1; j >= 0; --j) {
            if (h[j] >= h[i]) continue;
            if (dp[j] > best_val) best_val = dp[j];
        }

        dp[i] = a[i] + best_val;
    }

    return *max_element(cbegin(dp), cend(dp));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vi h(n);
    for (auto &x : h) cin >> x;

    vi a(n);
    for (auto &x : a) cin >> x;

    cout << max_remaining_beauties_sum(h, a) << '\n';
    return 0;
}
