#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using huint = __uint128_t;

static constexpr ull M = 20170123456789ULL;
static constexpr ull B = 27;
static constexpr ull B_ = 12699707361682ULL;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ull mpow_mod(const ull base, const ull exp, const ull m) {
    if (!exp) return 1;
    if (exp % 2ULL) return (base * mpow_mod(base, exp - 1, m)) % m;
    const ull q = mpow_mod(base, exp / 2, m);
    return (q * q) % m;
}

int num_uniques(const string &xs) {
    const auto n = sz(xs);
    ull S = inof(xs[0]) - inof('`');
    vector<ull> bs(n, 1);
    vector<ull> pre(n, S);

    for (int i = 1; i < n; ++i) {
        bs[i] = bs[i - 1] * B;
        bs[i] %= M;

        ull a = inof(xs[i]) - inof('`');
        a *= bs[i];
        a %= M;

        S += a;
        S %= M;
        pre[i] = S;
    }

    const auto ai = [&](const int i) -> ull {
        ull r = inof(xs[i]) - inof('`');
        r *= bs[i];
        r %= M;
        return r;
    };

    set<ull> uq;
    for (int i = 0; i + 2 <= n; ++i) {
        ull h = pre[i + 1];
        h -= ai(i);
        h += M;
        h %= M;

        h -= ai(i + 1);
        h += M;
        h %= M;

        ull t = S;
        t -= pre[i + 1];
        t += M;
        t %= M;

        huint tt = t;
        tt *= B_;
        tt %= static_cast<huint>(M);
        tt *= B_;
        tt %= static_cast<huint>(M);

        t = static_cast<ull>(tt);

        ull x = h + t;
        x %= M;
        uq.insert(x);
    }
    return sz(uq);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << num_uniques(xs) << '\n';
    }

    return 0;
}
