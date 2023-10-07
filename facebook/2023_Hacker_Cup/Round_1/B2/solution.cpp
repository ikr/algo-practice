#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

using ull = unsigned long long;
using ll = long long;

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

vector<ull> try_combining(const ull s0, const vector<ull> &fs) {
    vector<ull> ans;
    const auto recur = [&](const auto self, const vector<ull> &xs) -> void {
        if (!empty(ans)) return;
        const auto s = accumulate(cbegin(xs), cend(xs), 0ULL);
        if (s > s0) return;
        if (s == s0) {
            ans = xs;
            return;
        }

        for (int i = 0; i < sz(xs) - 1; ++i) {
            for (int j = i + 1; j < sz(xs); ++j) {
                auto ys = xs;
                const auto a = xs[i];
                const auto b = xs[j];
                ys.erase(cbegin(ys) + j);
                ys.erase(cbegin(ys) + i);
                ys.push_back(a * b);
                self(self, ys);
                if (!empty(ans)) return;
            }
        }
    };
    recur(recur, fs);
    return ans;
}

vector<ull> solve(const ull x0) {
    auto fs = kactl::factor(x0);
    auto s = accumulate(cbegin(fs), cend(fs), 0ULL);
    if (s > 41ULL) return {};

    for (ull s0 = 41; s0 >= 4; --s0) {
        auto opt = try_combining(s0, fs);
        if (!empty(opt)) {
            auto total = accumulate(cbegin(opt), cend(opt), 0ULL);
            while (total < 41ULL) {
                opt.push_back(1);
                ++total;
            }
            return opt;
        }
    }

    while (s < 41ULL) {
        fs.push_back(1);
        ++s;
    }

    return sz(fs) <= 100 ? fs : vector<ull>{};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        ull x0;
        cin >> x0;

        cout << "Case #" << i << ": ";
        const auto ans = solve(x0);
        if (empty(ans)) {
            cout << -1;
        } else {
            cout << sz(ans) << ' ' << ans;
        }
        cout << '\n';
    }

    return 0;
}
