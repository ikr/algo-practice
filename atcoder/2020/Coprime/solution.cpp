#include <bits/stdc++.h>
using namespace std;

using Result = string;
static const Result PAIRWISE{"pairwise coprime"};
static const Result SETWISE{"setwise coprime"};
static const Result NEITHER{"not coprime"};
static constexpr int N_MAX = 1e6;
static constexpr int PRIMES_COUNT_UP_TO_N_MAX = 78498;

vector<bool> sieve(const int n) {
    vector<bool> ans(n + 1, true);
    ans[0] = false;
    if (n) ans[1] = false;

    const int sq = sqrt(n);
    for (int i = 2; i <= sq; ++i) {
        if (!ans[i]) continue;
        for (int j = i * i; j <= n; j += i) ans[j] = false;
    }

    return ans;
}

vector<int> seq_of(const vector<bool> &xs, const int expected_count) {
    vector<int> ans;
    ans.reserve(expected_count);

    for (auto i = 0U; i < xs.size(); ++i) {
        if (xs[i]) ans.push_back(i);
    }

    return ans;
}

vector<int> prime_factors(const vector<bool> &primes,
                          const vector<int> &primes_seq, const int x) {
    if (primes[x]) return {x};

    const int sq = sqrt(x);
    vector<int> ans;

    for (const auto p : primes_seq) {
        if (p > sq) break;
        if (x % p) continue;

        ans.push_back(p);
        const int q = x / p;
        if (q > sq && primes[q]) ans.push_back(q);
    }

    return ans;
}

bool all_ones(const unordered_map<int, int> &cs) {
    for (const auto [k, v] : cs) {
        if (v != 1) return false;
    }

    return true;
}

Result solve(vector<int> xs) {
    const auto primes = sieve(N_MAX);
    const auto primes_seq = seq_of(primes, PRIMES_COUNT_UP_TO_N_MAX);
    assert(primes_seq.size() == PRIMES_COUNT_UP_TO_N_MAX);
    assert(primes_seq.back() == 999983);

    // Ho many times a prime is a factor of one of the xs
    unordered_map<int, int> cs;

    for (const auto x : xs) {
        for (const int p : prime_factors(primes, primes_seq, x)) ++cs[p];
    }

    if (all_ones(cs)) return PAIRWISE;

    return reduce(cbegin(xs) + 1, cend(xs), xs[0],
                  [](const int a, const int b) { return gcd(a, b); }) == 1
               ? SETWISE
               : NEITHER;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    cout << solve(xs) << '\n';
    return 0;
}
