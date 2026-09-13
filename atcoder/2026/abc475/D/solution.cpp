#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using vi = vector<int>;
using vii = vector<vi>;
using pii = pair<int, int>;

#define rep(i, a, b) for (int i = a; i < (b); ++i)

constexpr int LIM = 1e7;
constexpr int S =
    static_cast<int>(std::round(std::sqrt(static_cast<double>(LIM))));

constexpr int R = LIM / 2;

bitset<LIM> isPrime;

vi eratosthenes() {
    vi pr = {2}, sieve(S + 1);
    pr.reserve(int(LIM / log(LIM) * 1.1));
    vector<pii> cp;
    for (int i = 3; i <= S; i += 2)
        if (!sieve[i]) {
            cp.push_back({i, i * i / 2});
            for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
        }
    for (int L = 1; L <= R; L += S) {
        array<bool, S> block{};
        for (auto &[p, idx] : cp)
            for (int i = idx; i < S + L; idx = (i += p)) block[i - L] = 1;
        rep(i, 0, min(S, R - L)) if (!block[i]) pr.push_back((L + i) * 2 + 1);
    }
    for (int i : pr) isPrime[i] = 1;
    return pr;
}

template <typename T> vector<int> digits_reversed(T n) {
    vector<int> ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= static_cast<T>(10);
    }

    return ans;
}

template <typename T> vector<int> digits(T n) {
    auto ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

vii eq_classes(const vii &idx) {
    vii result{};
    ranges::copy_if(idx, back_inserter(result),
                    [](const vi &ii) { return !ii.empty(); });
    ranges::sort(result);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;
    const auto primes = eratosthenes();

    vector<vector<int>> idx_alpha(26, vector<int>{});

    for (int i = 0; i != sz(s); ++i) {
        idx_alpha[s[i] - 'a'].push_back(i);
    }

    const auto target = eq_classes(idx_alpha);

    const auto match_it = ranges::find_if(primes, [&target](const int p) {
        const auto ds = digits(p);
        vector<vector<int>> idx_digit(10, vector<int>{});

        for (int i = 0; i != sz(ds); ++i) {
            idx_digit[ds[i]].push_back(i);
        }

        return target == eq_classes(idx_digit);
    });

    if (match_it == primes.end()) {
        cout << -1 << '\n';
    } else {
        cout << *match_it << '\n';
    }

    return 0;
}
