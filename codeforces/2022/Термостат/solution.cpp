#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_hops(const pii lr, const int x, const pii ab) {
    const auto [l, r] = lr;
    const auto [a, b] = ab;
    assert(l <= r);
    assert(a <= b);

    if (a == b) return 0;
    if (b - a >= x) return 1;

    if (a - x >= l || b + x <= r) return 2;

    if (b - x >= l) {
        if (r - a >= x) return 3;
    }

    if (a + x <= r) {
        if (b - l >= x) return 3;
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int l, r, x;
        cin >> l >> r >> x;

        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);

        cout << min_hops({l, r}, x, {a, b}) << '\n';
    }

    return 0;
}
