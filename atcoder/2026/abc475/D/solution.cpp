#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using vi = vector<int>;
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

struct PairHash {
    std::size_t operator()(const std::pair<int, int> &p) const noexcept {
        return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;

    const int n = sz(s);

    const auto primes = eratosthenes();

    vector<vector<int>> idx(26, vector<int>{});
    for (int i = 0; i != sz(s); ++i) {
        idx[s[i] - 'a'].push_back(i);
    }

    unordered_set<pii, PairHash> eq;
    unordered_set<pii, PairHash> ne;

    for (const auto &ii : idx) {
        if (!ii.empty()) {
            for (int a = 0; a < sz(ii); ++a) {
                for (int b = a + 1; b < sz(ii); b++) {
                }
            }
        }
    }

    return 0;
}
