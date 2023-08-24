#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

bool is_symm(const vector<int> &xs) {
    const int n = sz(xs);
    if (xs[0] != n) return false;

    for (int i = 0; i < div_ceil(n, 2); ++i) {
        const auto h = xs[i] - i;
        if (h < 0) return false;
        if (i + h > n) return false;
        if (!(i + h == n || xs[i + h] < i)) return false;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << (is_symm(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
