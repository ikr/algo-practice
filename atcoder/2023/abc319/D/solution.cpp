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

bool can_fit(const vector<ll> &xs, const ll H, const ll W) {
    ll h{1};
    ll w{};

    for (const auto x : xs) {
        if (x > W) return false;
        const auto w_ = w ? (w + 1 + x) : x;

        if (w_ > W) {
            ++h;
            w = x;
        } else {
            w = w_;
        }
    }

    return h <= H;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, H;
    cin >> N >> H;

    vector<ll> xs(N);
    for (auto &x : xs) cin >> x;

    const auto result = [&]() -> ll {
        if (can_fit(xs, H, 1)) return 1;

        ll lo{1};
        ll hi{LONG_LONG_MAX};
        assert(can_fit(xs, H, hi));

        while (lo + 1 < hi) {
            const auto mid = midpoint(lo, hi);
            if (can_fit(xs, H, mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }

        return hi;
    }();
    cout << result << '\n';
    return 0;
}
