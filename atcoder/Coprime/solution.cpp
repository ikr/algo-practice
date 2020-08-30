#include <bits/stdc++.h>
using namespace std;

using Result = string;
static const Result PAIRWISE{"pairwise coprime"};
static const Result SETWISE{"pairwise coprime"};
static const Result NEITHER{"not coprime"};
static constexpr int N_MAX = 1e6;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

vector<bool> sieve(const int n) {
    vector<bool> ans(n + 1, true);
    ans[0] = false;
    ans[1] = false;

    const int sq = static_cast<int>(sqrt(n));
    for (int i = 2; i <= sq; ++i) {
        if (!ans[i]) continue;
        for (int j = i * i; j <= n; j += i) ans[j] = false;
    }

    return ans;
}

vector<int> seq_of(const vector<bool> &xs) {
    vector<int> ans;
    ans.reserve(xs.size() / 3);

    for (auto i = 0U; i < xs.size(); ++i) {
        if (xs[i]) ans.push_back(i);
    }

    return ans;
}

vector<int> prime_factors(const vector<bool> &primes,
                          const vector<int> &primes_seq, const int x) {
    if (primes[x]) return {x};

    const int sq = static_cast<int>(sqrt(x));
    vector<int> ans;

    for (const auto p : primes_seq) {
        if (p > sq) break;
        const int r = x % p;
        if (r) continue;

        ans.push_back(p);

        const int q = x / p;
        if (primes[q]) ans.push_back(q);
    }

    return ans;
}

Result solve(vector<int> xs) {
    const auto original_size = xs.size();
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), cend(xs));

    const auto primes = sieve(N_MAX);
    const auto primes_seq = seq_of(primes);

    // Ho many times a prime is a factor of one of the xs
    unordered_map<int, int> cs;

    for (const auto x : xs) {
        for (const auto p : prime_factors(primes, primes_seq, x)) {
            ++cs[p];
        }
    }
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
