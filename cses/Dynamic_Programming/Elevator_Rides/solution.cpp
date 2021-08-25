#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_rides(const int cap, const vi &xs) {
    const auto n = sz(xs);
    const auto lim = 1 << n;

    // dp[i] is a pair (kᵢ wᵢ) for a subset bits of passengers i:
    // kᵢ is the minimal number of elevator rides for the subset i
    // wᵢ is the total weight of the last ride
    vector<pii> dp(lim, {n + 1, cap});
    dp[0] = {1, 0};

    for (int bits = 1; bits < lim; ++bits) {
        for (int j = 0; j < n; ++j) {
            if (bits & (1 << j)) {
                const auto [k0, w0] = dp[bits ^ (1 << j)];
                auto &[k, w] = dp[bits];
                const auto fits = w0 + xs[j] <= cap;

                if (fits) {
                    if (k0 <= k) {
                        k = k0;
                        w = min(w, w0 + xs[j]);
                    }
                } else {
                    if (k0 + 1 <= k) {
                        k = k0 + 1;
                        w = min(w, xs[j]);
                    }
                }
            }
        }
    }

    return dp.back().first;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, cap;
    cin >> n >> cap;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    cout << min_rides(cap, xs) << '\n';
    return 0;
}
