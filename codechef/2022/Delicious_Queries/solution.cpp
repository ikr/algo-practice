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
    assert(!xs.empty());
    vector<ll> ss(sz(xs), xs[0]);
    for (int i = 1; i < sz(xs); ++i) ss[i] = ss[i - 1] + xs[i];

    const auto ps =
        intersection_of(relevant_primes(xs), extract_distinct_ps(qs));

    map<int, int> ps_idx;
    for (int j = 0; j < sz(ps); ++j) ps_idx[ps[j]] = j;

    if (ps.empty()) {
        vector<ll> result;
        result.reserve(sz(qs));
        for (const auto &[_, k] : qs) {
            result.push_back(ss[k - 1]);
        }
        return result;
    }

    vector<vector<int>> p_indices(sz(ps));
    vector<vector<int>> p_values(sz(ps));

    for (int i = 0; i < sz(xs); ++i) {
        for (int j = 0; j < sz(ps); ++j) {
            if (xs[i] % ps[j]) continue;

            p_indices[j].push_back(i);
            p_values[j].push_back(xs[i]);
        }
    }

    vector<vector<int>> p_values_sorted = p_values;
    for (auto &row : p_values_sorted) sort(rbegin(row), rend(row));

    vector<vector<ll>> p_value_prefix_sums(sz(ps));
    for (int j = 0; j < sz(ps); ++j) {
        assert(!p_values[j].empty());
        p_value_prefix_sums[j] = vector<ll>(sz(p_values[j]));
        p_value_prefix_sums[j][0] = p_values[j][0];
    }

    vector<vector<ll>> p_value_sorted_prefix_sums(sz(ps));
    for (int j = 0; j < sz(ps); ++j) {
        assert(!p_values_sorted[j].empty());
        p_value_sorted_prefix_sums[j] = vector<ll>(sz(p_values_sorted[j]));
        p_value_sorted_prefix_sums[j][0] = p_values_sorted[j][0];
    }

    for (int j = 0; j < sz(ps); ++j) {
        for (int i = 1; i < sz(p_value_prefix_sums[j]); ++i) {
            p_value_prefix_sums[j][i] =
                p_value_prefix_sums[j][i - 1] + p_values[j][i];

            p_value_sorted_prefix_sums[j][i] =
                p_value_sorted_prefix_sums[j][i - 1] + p_values_sorted[j][i];
        }
    }

    vector<ll> result;
    result.reserve(sz(qs));
    for (const auto &[p, k] : qs) {
        assert(k - 1 < sz(ss));
        auto S = ss[k - 1];

        if (ps_idx.count(p)) {
            const auto j = ps_idx.at(p);
            auto it =
                lower_bound(cbegin(p_indices[j]), cend(p_indices[j]), k - 1);
            if (it != cend(p_indices[j]) && (*it) == k - 1) {
            } else {
                if (it == cbegin(p_indices[j])) {
                    it = cend(p_indices[j]);
                } else {
                    it = prev(it);
                }
            }

            if (it != cend(p_indices[j])) {
                const auto ii = inof(distance(cbegin(p_indices[j]), it));
                assert(ii < sz(p_indices[j]));
                assert(ii < sz(p_value_prefix_sums[j]));
                assert(ii < sz(p_value_sorted_prefix_sums[j]));

                S -= p_value_prefix_sums[j][ii];
                S += p_value_sorted_prefix_sums[j][ii];
            }
        }

        result.push_back(S);
    }
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
