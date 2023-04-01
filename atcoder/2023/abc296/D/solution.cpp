#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ulll = __uint128_t;
using lll = __int128_t;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr lll lllof(const T x) {
    return static_cast<lll>(x);
}

namespace kactl { // https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/Factor.h
ulll modmul(ulll a, ulll b, ulll M) {
    lll ret = a * b - M * ulll(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (lll)M);
}
ulll modpow(ulll b, ulll e, ulll mod) {
    ulll ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}

bool isPrime(ulll n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ulll A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
         s = __builtin_ctzll(n - 1), d = n >> s;
    for (ulll a : A) { // ^ count trailing zeroes
        ulll p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}

ulll pollard(ulll n) {
    auto f = [n](ulll x) { return modmul(x, x, n) + 1; };
    ulll x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}

#define all(x) begin(x), end(x)

vector<ulll> factor(ulll n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    ulll x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}
} // namespace kactl

bool factorizable_under_N(const lll N, const lll a) {
    auto fs = kactl::factor(a);
    sort(begin(fs), end(fs));
    return lllof(fs.back()) <= N;
}

ll find_X(const lll N, const lll M) {
    if (N >= M) return llof(N);
    if (N * N < M) return -1;

    lll hi = N * N;
    lll lo = M;
    lll ans = hi;

    while (lo + lllof(1) < hi) {
        const auto mid = lo + (hi - lo) / lllof(2);
        if (mid >= M) {
            hi = mid;
            if (factorizable_under_N(N, hi)) {
                ans = hi;
            }
        } else {
            lo = mid;
        }
    }

    return llof(ans);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, M;
    cin >> N >> M;
    cout << find_X(N, M) << '\n';
    return 0;
}
