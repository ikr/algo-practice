#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

constexpr int multiples_of_x(const int x, const int l, const int r) {
    return r / x - (l - 1) / x;
}

template <typename T> constexpr T sqr(const T x) { return x * x; }

ll proper_pairs_num(const int l, const int r) {
    // dp[i] is the number of pairs x y in [l, r]: gcd(x, y) = i
    vll dp(r + 1, 1);

    for (int i = r - 1; i >= 1; --i) {
        dp[i] = sqr(llof(multiples_of_x(i, l, r)));

        for (int k = 2; llof(k) * i <= llof(r); ++k) {
            dp[i] -= dp[k * i];
        }
    }

    ll muls = 0;

    for (int i = l; i <= r; ++i) {
        muls += multiples_of_x(i, l, r);
    }

    return sqr(llof(r - l + 1)) - dp[1] - muls;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int l, r;
    cin >> l >> r;

    cout << proper_pairs_num(l, r) << '\n';
    return 0;
}
