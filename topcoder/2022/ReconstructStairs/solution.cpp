#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

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

bool not_zero(const int x) { return x != 0; }

struct ReconstructStairs final {
    int reconstruct(const vector<int> &xs) const {
        const auto given_total = accumulate(xbegin(xs), xend(xs), 0);

        const auto a =
            inof(distance(xbegin(xs), find_if(xbegin(xs), xend(xs), not_zero)));

        auto b = sz(xs) - 1;
        while (xs[b] == 0) --b;
        assert(b >= 0);

        int hi{};
        for (int i = a; i <= b; ++i) {
            const auto rem = b - i;
            hi = max(hi, xs[i] + rem);
        }

        return (hi * (hi + 1)) / 2 - given_total;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ReconstructStairs{}.reconstruct({1, 2, 3, 4});
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = ReconstructStairs{}.reconstruct({0, 0, 1, 2, 3, 4, 0, 0});
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = ReconstructStairs{}.reconstruct({1, 2, 1, 4});
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = ReconstructStairs{}.reconstruct({3, 2, 1});
        const auto expected = 9;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
