#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const multiset<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

using ll = long long;
using ull = unsigned long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

namespace kactl { // https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/Factor.h
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

ull mpow(const ull x, const int p) {
    if (p == 0) return 1;
    if (p % 2) return (x * mpow(x, p - 1));
    const ull sq = mpow(x, p / 2);
    return (sq * sq);
}

ull num_present(const ull p, ull n) {
    if (n < p) return 0;

    int hi = 1;
    while (mpow(p, hi + 1) <= n) ++hi;

    vector<ull> memo(hi + 1, 0);
    memo[hi] = n / mpow(p, hi);
    ull s = memo[hi];

    for (int i = hi - 1; i >= 1; --i) {
        memo[i] = n / mpow(p, i) - s;
        s += memo[i];
    }

    ull result{};
    for (int i = 1; i <= hi; ++i) {
        result += i * memo[i];
    }
    return result;
}

ull lowest_N(const ull K) {
    map<ull, int> fs;
    for (const auto p : kactl::factor(K)) {
        ++fs[p];
    }

    ull result{};

    for (const auto &[p, a] : fs) {
        if (a == 1) {
            result = max(result, p);
            continue;
        }

        ull lo = p;
        ull hi = mpow(p, a);

        while (lo + 1 < hi) {
            const auto mid = lo + (hi - lo) / 2UL;
            if (inof(num_present(p, mid)) >= a) {
                hi = mid;
            } else {
                lo = mid;
            }
        }

        result = max(result, hi);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ull K;
    cin >> K;

    cout << lowest_N(K) << '\n';
    return 0;
}
