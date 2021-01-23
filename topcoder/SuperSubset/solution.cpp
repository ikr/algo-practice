#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

constexpr ll pow_mod(const ll base, const ll exp, const ll m) {
    if (!exp) return 1;
    if (exp % 2) return (base * pow_mod(base, exp - 1, m)) % m;
    const ll q = pow_mod(base, exp / 2, m);
    return (q * q) % m;
}

struct SuperSubset final {
    int solve(const vector<int> &xs, const int y) const {
        const int n = xs.size();
        vector<int> ss(n + 1, 0);
        partial_sum(xs.cbegin(), xs.cend(), next(begin(ss)));
        cout << ss << '\n';

        ll ans = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                const int s = ss[j + 1] - ss[i];
                if (s == y) {
                    const int d = j - i + 1;
                    const int r = n - d;
                    ans += pow_mod(2LL, r, M);
                    ans %= M;
                }
            }
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SuperSubset{}.solve({1, 2, 3}, 3);
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SuperSubset{}.solve({1, 1, 1, 1, 1}, 4);
        const auto expected = 10;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
