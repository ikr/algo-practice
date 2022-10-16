#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << x.first << ' ' << x.second;
    return os;
}

using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;

// https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory
namespace kactl {
ull modmul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
    ull ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}

bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n - 1), d = n >> s;
    for (ull a : A) { // ^ count trailing zeroes
        ull p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}

ull pollard(ull n) {
    auto f = [n](ull x) { return modmul(x, x, n) + 1; };
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}

#define all(x) begin(x), end(x)

vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}
} // namespace kactl

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pll find_x_and_y(const ull a, const ull b, const ull c, const ull d) {
    const auto T = a * b;
    auto cur = 2 * T;

    for (;;) {
        if (cur > c * d) break;
        auto fs = kactl::factor(cur);

        for (ull bits = 1ULL; bits < (1ULL << sz(fs)); ++bits) {
            ull x = 1ULL;

            for (int i = 0; i < sz(fs); ++i) {
                if (bits & (1ULL << i)) {
                    x *= fs[i];
                }
            }

            const auto y = cur / x;

            if (a < x && x <= c && b < y && y <= d) return {x, y};
        }

        cur += T;
    }

    return {-1, -1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ull a, b, c, d;
        cin >> a >> b >> c >> d;

        cout << find_x_and_y(a, b, c, d) << '\n';
    }

    return 0;
}
