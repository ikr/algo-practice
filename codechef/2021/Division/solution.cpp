#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

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
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

// Source:
// https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory

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

optional<pii> min_max_odd_divisor(const int x) {
    auto fs = factor(x);
    sort(begin(fs), end(fs));
    const auto it = upper_bound(cbegin(fs), cend(fs), 2);
    if (it == cend(fs)) return nullopt;

    int q = x;
    while (q % 2 == 0) q /= 2;

    return pii{*it, q};
}

optional<int> max_even_divisor(const int x) {
    if (x % 2) return nullopt;

    int ans = 2;

    while (x % (ans * 2) == 0) {
        ans *= 2;
    }

    return ans;
}

int max_points(const int N, const int A, const int B) {
    map<int, int> memo;
    memo[1] = 0;

    function<int(int)> recur;
    recur = [&](const int x) -> int {
        const auto it = memo.find(x);
        if (it != cend(memo)) return it->second;

        int ans = INT_MIN;

        if (isPrime(x)) {
            ans = (x == 2) ? A : B;
        } else {
            for (int q = 1; llof(q) * llof(q) <= llof(x); ++q) {
                if (x % q) continue;
                if (q > 1) {
                    ans = max(ans, ((q % 2) ? B : A) + recur(x / q));
                }

                const int p = x / q;
                ans = max(ans, ((p % 2) ? B : A) + recur(x / p));
            }
        }

        memo[x] = ans;
        return ans;
    };

    const auto ans = recur(N);
    // cerr << memo << endl;
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int N, A, B;
        cin >> N >> A >> B;

        cout << max_points(N, A, B) << '\n';
    }

    return 0;
}
