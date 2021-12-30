#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

static constexpr ll HI = 1LL << 60LL;
static constexpr ll N_MAX = 1000000000000LL;

struct NailingABanner final {
    ll coordinate(const ll n) const {
        if (n == 1) return 0;
        if (n == 2) return HI;

        vll cs;
        for (ll i = 0; (1LL << i) < N_MAX; ++i) {
            cs.push_back(1LL << i);
        }

        vll ss(sz(cs), 0LL);
        partial_sum(xbegin(cs), xend(cs), begin(ss));

        const auto x = n - 2LL;
        const auto it = lower_bound(xbegin(ss), xend(ss), x);
        assert(it != xend(ss));

        const ll i = distance(xbegin(ss), it);
        const ll d = x - (i > 0LL ? ss[i - 1] : 0LL);
        assert(d >= 0LL);

        const ll st0 = HI / (1LL << (i + 1LL));
        const ll st = 2LL * st0;

        return st0 + (d - 1LL) * st;
    }
};

ll oracle(ll N) {
    if (N == 1) return 0;
    if (N == 2) return 1L << 60;
    N -= 2;
    for (int round = 1;; ++round) {
        long placed_this_round = 1L << (round - 1);
        if (placed_this_round < N) {
            N -= placed_this_round;
            continue;
        }
        long first_index = 1L << (60 - round);
        return (2 * N - 1) * first_index;
    }
}

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = NailingABanner{}.coordinate(1);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = NailingABanner{}.coordinate(3);
        const auto expected = 576460752303423488LL;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = NailingABanner{}.coordinate(4);
        const auto expected = 288230376151711744LL;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = NailingABanner{}.coordinate(24);
        const auto expected = 468374361246531584LL;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = NailingABanner{}.coordinate(65537);
        const auto expected = 1152903912420802560LL;
        EXPECT(actual == expected);
    },
    CASE("Example A") {
        const auto actual = NailingABanner{}.coordinate(2);
        const auto expected = (1LL << 60LL);
        EXPECT(actual == expected);
    },
    CASE("Testing against an oracle - LO") {
        for (ll i = 1; i < 1'000; ++i) {
            const auto actual = NailingABanner{}.coordinate(i);
            const auto expected = oracle(i);
            EXPECT(actual == expected);
        }
    },
    CASE("Testing against an oracle - HI") {
        const ll BIG = 1'000'000'000'000;

        for (ll i = BIG - 1'000LL; i <= BIG; ++i) {
            const auto actual = NailingABanner{}.coordinate(i);
            const auto expected = oracle(i);
            EXPECT(actual == expected);
        }
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
