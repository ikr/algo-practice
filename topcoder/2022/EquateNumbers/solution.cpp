#include "lest.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

// Source:
// https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory

using ll = long long;
typedef unsigned long long ull;
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

struct EquateNumbers final {
    string canMakeEqual(const vector<int> &xs) const {
        if (sz(set<int>(xbegin(xs), xend(xs))) == 1) return "yes";

        map<ull, int> fs;

        for (const auto x : xs) {
            auto ps = factor(x);
            sort(begin(ps), end(ps));
            ps.erase(unique(begin(ps), end(ps)), end(ps));
            for (const auto p : ps) {
                ++fs[p];
            }
        }

        for (const auto f : fs) {
            if (f.second == sz(xs)) return "yes";
        }

        return "no";
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = EquateNumbers{}.canMakeEqual({2, 4});
        const auto expected = "yes";
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = EquateNumbers{}.canMakeEqual({3, 6, 7});
        const auto expected = "no";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
