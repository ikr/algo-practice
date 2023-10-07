#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

bool is_K_possible(const ll A, const ll B, const ll C, const ll K) {
    vector<pair<ll, ll>> opt;
    const auto prefer_double = (B < 2LL * A);
    if (prefer_double) {
        {
            const auto b = min(C / B, div_ceil(K, 2LL));
            const auto r = C - b * B;
            const auto a = r / A;
            opt.emplace_back(a, b);
        }
        {
            const auto b = min(C / B, K / 2LL);
            const auto r = C - b * B;
            const auto a = r / A;
            opt.emplace_back(a, b);
        }
        {
            const auto b = min({C / B, K / 2LL - 1LL, 0LL});
            const auto r = C - b * B;
            const auto a = r / A;
            opt.emplace_back(a, b);
        }
    } else {
        {
            const auto a = min(0LL, C / A - 1LL);
            const auto r = C - a * A;
            const auto b = r / B;
            opt.emplace_back(a, b);
        }
        {
            const auto a = C / A;
            const auto r = C - a * A;
            const auto b = r / B;
            opt.emplace_back(a, b);
        }
    }

    for (const auto &[x, y] : opt) {
        if ((x + y) * 2LL >= K + 1 && x + 2 * y >= K) return true;
    }
    return false;
}

ll max_K(const ll A, const ll B, const ll C) {
    ll lo{};
    ll hi = LONG_LONG_MAX;

    while (lo + 1LL < hi) {
        const auto mid = midpoint(lo, hi);
        if (is_K_possible(A, B, C, mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return lo;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        ll A, B, C;
        cin >> A >> B >> C;

        cout << "Case #" << i << ": " << max_K(A, B, C) << '\n';
    }

    return 0;
}
