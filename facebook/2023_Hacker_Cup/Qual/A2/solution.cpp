#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

bool is_K_possible(const ll A, const ll B, const ll C, const ll K) {
    const auto [x, y] = [&]() -> pll {
        const auto prefer_double = (B < 2LL * A);
        if (prefer_double) {
            const auto b = C / B;
            const auto r = C % B;
            const auto a = r / A;
            return {a, b};
        } else {
            const auto a = C / A;
            const auto r = C % A;
            const auto b = r / B;
            return {a, b};
        }
    }();
    return (x + y) * 2LL >= K + 1 && x + 2 * y >= K;
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
