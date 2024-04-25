#include <bits/stdc++.h>
using namespace std;

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

using ll = long long;
static constexpr ll M = 1e9 + 7;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

lll max_s(const vector<ll> &xs) {
    const auto n = sz(xs);
    if (n == 1) return xs[0];

    int ir{};
    lll s{};
    if (xs[0] == 1) {
        while (ir + 1 < n && xs[ir + 1] == 1) ++ir;
        s = ir + 1;
    } else {
        s = xs[0];
    }

    for (int i = ir + 1; i < n; ++i) {
        s *= xs[i];
        s %= M;
    }
    return s;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));
        cout << max_s(xs) << endl;
    }

    return 0;
}
