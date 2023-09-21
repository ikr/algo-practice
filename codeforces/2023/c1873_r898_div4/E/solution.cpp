#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool can_use_at_most_W_of_water(const vector<ll> &A, const ll W, const ll h) {
    ll w{};
    for (const auto a : A) {
        if (a >= h) continue;
        w += h - a;
        if (w > W) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        ll W;
        cin >> N >> W;

        vector<ll> A(N);
        for (auto &a : A) cin >> a;

        ll lo = 0;
        ll hi = LONG_LONG_MAX;

        while (lo + 1LL < hi) {
            const auto mid = midpoint(lo, hi);
            if (can_use_at_most_W_of_water(A, W, mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        cout << lo << '\n';
    }

    return 0;
}
