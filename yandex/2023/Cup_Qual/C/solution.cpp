#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using mint = atcoder::modint1000000007;
using Freq = array<mint, 8 * sizeof(ull)>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

Freq brute_force_bit_counts(const ull n) {
    Freq fs{};
    for (ull k = 1; k <= n; ++k) {
        for (int i = 0; i < sz(fs); ++i) {
            if (k & (1ULL << i)) ++fs[i];
        }
    }
    return fs;
}

constexpr int mlog2(const ull x) {
    return 8 * sizeof(ull) - __builtin_clzll(x) - 1;
}

constexpr optional<int> next_set_bit_index(const ull x, const int i) {
    for (int j = i + 1; j < 64; ++j) {
        if (x & (1ULL << j)) return j;
    }
    return nullopt;
}

Freq bit_counts(const ll N) {
    const auto X = mlog2(N);
    Freq fs{};
    // if (X) fill(begin(fs), begin(fs) + X, mint{2}.pow(X - 1));

    for (int x = X; x >= 0; --x) {
        auto a = (N >> (x + 1)) << x;
        a += max(0LL, N - a * 2LL - (1LL << x));
        fs[x] = a;
        if (N & (1ULL << x)) ++fs[x];

        // const auto y = next_set_bit_index(N, x);
        // if (y) {
        //     assert(*y > x);
        //     fs[x] += mint{2}.pow(*y - 1);
        // }

        // if (N & (1ULL << x)) {
        //     const auto n = (N >> x) << x;
        //     fs[x] += N - n + 1;
        // }
    }

    return fs;
}

ostream &operator<<(ostream &os, const mint x) {
    os << x.val();
    return os;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int sum_of_ands(const ull n) {
    // cerr << bit_counts(n) << endl;
    // cerr << brute_force_bit_counts(n) << endl;
    // assert(bit_counts(n) == brute_force_bit_counts(n));

    const auto fs = bit_counts(n);
    mint ans{};

    for (int i = 0; i < sz(fs); ++i) {
        ans += fs[i].pow(2) * mint{2}.pow(i);
    };

    return ans.val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int T;
    cin >> T;
    while (T--) {
        ull n;
        cin >> n;
        cout << sum_of_ands(n) << '\n';
    }

    return 0;
}
