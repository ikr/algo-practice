#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
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

vector<int> relevant_primes(const vector<int> &xs) {
    set<int> result;
    for (const auto x : xs) {
        for (const auto f : kactl::factor(x)) {
            result.insert(inof(f));
        }
    }
    assert(!result.count(1));
    return vector<int>(cbegin(result), cend(result));
}

vector<int> extract_distinct_ps(const vector<pii> &qs) {
    set<int> result;
    for (const auto &[p, _] : qs) {
        result.insert(p);
    }
    return vector<int>(cbegin(result), cend(result));
}

vector<int> intersection_of(const vector<int> &xs, const vector<int> &ys) {
    vector<int> result;
    set_intersection(cbegin(xs), cend(xs), cbegin(ys), cend(ys),
                     back_inserter(result));
    return result;
}

vector<ll> top_total_flavours(const vector<int> &xs, const vector<pii> &qs) {
    vector<ll> ss(sz(xs), xs[0]);
    for (int i = 1; i < sz(xs); ++i) ss[i] = ss[i - 1] + xs[i];

    const auto ps =
        intersection_of(relevant_primes(xs), extract_distinct_ps(qs));

    vector<vector<int>> p_indices(sz(ps));
    vector<vector<int>> p_values(sz(ps));
    vector<vector<int>> p_value_prefix_sums(sz(ps));
    vector<vector<int>> p_values_sorted(sz(ps));
    vector<vector<int>> p_value_sorted_prefix_sums(sz(ps));

    for (int i = 0; i < sz(xs); ++i) {
        for (int j = 0; j < sz(ps); ++j) {
        }
    }

    vector<ll> result(sz(qs), -1);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        vector<int> xs(N);
        for (auto &x : xs) cin >> x;

        int Q;
        cin >> Q;

        vector<pii> qs(Q);
        for (auto &[p, k] : qs) cin >> p >> k;

        for (const auto ans : top_total_flavours(xs, qs)) cout << ans << '\n';
    }

    return 0;
}
