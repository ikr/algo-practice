#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

struct MaxDistinctPairs final {
    string maximize(const int N, string xs) const {
        if (xs.empty()) return xs;

        const auto bump = [&](const char x) -> char {
            return chof(inof('A') + ((inof(x) - inof('A') + 1) % N));
        };

        for (int i = 0; i < sz(xs); ++i) {
            if (xs[i] != '.') continue;
            const auto l = (i == 0) ? chof(inof('A') - 1) : xs[i - 1];
            const auto r = (i == sz(xs) - 1) ? '~' : xs[i + 1];

            xs[i] = bump(l);
            if (xs[i] == r) xs[i] = bump(xs[i]);
        }

        return xs;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = MaxDistinctPairs{}.maximize(26, "........");
        const auto expected = "ABABABAB";
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = MaxDistinctPairs{}.maximize(1, "..A.A..A");
        const auto expected = "AAAAAAAA";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
