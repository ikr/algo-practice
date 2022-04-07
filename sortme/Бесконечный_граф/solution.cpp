#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

using ll = long long;
using ull = unsigned long long;

template <typename T> constexpr ull ullof(const T x) {
    return static_cast<ull>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

// Source:
// https://github.com/kth-competitive-programming/kactl/tree/main/content/number-theory

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

#define all(x) begin(x), end(x)
vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

ull smallest_factor(const ull x) {
    const auto fs = factor(x);
    return *min_element(cbegin(fs), cend(fs));
}

map<ull, ull> distances_from(ull x) {
    map<ull, ull> result{{x, 0ULL}};
    while (x > 1ULL) {
        const auto f = smallest_factor(x);
        if (f == x) {
            result[1ULL] = f + result[x];
            break;
        }
        result[x / f] = f + result[x];
        x /= f;
    }
    return result;
}

ull min_distance(const int a, const int b) {
    const auto da = distances_from(a);
    const auto db = distances_from(b);

    cerr << "da:" << da << " db:" << db << endl;

    for (auto it = crbegin(da); it != crend(da); ++it) {
        const auto jt = db.find(it->first);
        if (jt == cend(db)) continue;
        return it->second + jt->second;
    }

    assert(false && "/o\\");
    return a + b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << min_distance(min(a, b), max(a, b)) << '\n';
    }

    return 0;
}

// AJN 2022-04-07 https://sort-me.org/contest/11/32
