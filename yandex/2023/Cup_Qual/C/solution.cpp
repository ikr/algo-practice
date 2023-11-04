#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using mint = atcoder::modint1000000007;
using Freq = array<mint, 8 * sizeof(ull)>;

Freq brute_force_bit_counts(const ull n) {
    Freq fs{};
    for (ull k = 1; k <= n; ++k) {
        for (ull i = 0; i < 64; ++i) {
            if (k & (1ULL << i)) ++fs[i];
        }
    }
    return fs;
}

constexpr int mlog2(const ull x) {
    return 8 * sizeof(ull) - __builtin_clzll(x) - 1;
}

Freq bit_counts(const ull n) {
    const auto x = mlog2(n);
    Freq fs{};

    for (int i = 0; i < x; ++i) {
        fs[i] = mint{2}.pow(x);
    }

    for (int i = x; i >= 0; --i) {
        const auto mask = (1ULL << (i + 1)) - 1ULL;
        const auto m = n & mask;
        if ((1ULL << x) & m) fs[i] += m - (1ULL << i) + 1;
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

ull sum_of_ands(const ull n) {
    cerr << bit_counts(n) << endl;
    cerr << brute_force_bit_counts(n) << endl;
    assert(bit_counts(n) == brute_force_bit_counts(n));
    return 0;
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
