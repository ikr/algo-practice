#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using lll = __int128_t;
using ulll = __uint128_t;

ostream &operator<<(ostream &dest, const lll value) {
    ostream::sentry s(dest);
    if (s) {
        ulll tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = end(buffer);

        do {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);

        if (value < 0) {
            --d;
            *d = '-';
        }

        const int len = static_cast<int>(end(buffer) - d);
        if (dest.rdbuf()->sputn(d, len) != len) dest.setstate(ios_base::badbit);
    }
    return dest;
}

template <typename T> constexpr lll lllof(const T x) {
    return static_cast<lll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<ll> xs(n);
    for (auto &x : xs) cin >> x;

    vector<ll> ss(n);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    lll hi = lllof(ss[n - 2]) * lllof(xs.back());
    int opt_i = n - 2;

    for (int i = 0; i < n - 1; ++i) {
        const lll left = ss[i];
        const lll right = ss.back() - ss[i];
        if (left * right > hi) {
            hi = left * right;
            opt_i = i;
        }
    }

    cerr << (opt_i + 1) << '\n';
    return 0;
}
