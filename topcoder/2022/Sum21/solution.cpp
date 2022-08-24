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

struct Sum21 final {
    int countWays(const vector<int> &xs) const {
        int result{};

        for (int i = 0; i < sz(xs) - 1; ++i) {
            for (int j = i + 1; j < sz(xs); ++j) {
                result += (xs[i] + xs[j] == 21);
            }
        }

        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = Sum21{}.countWays({ 1, 20 });
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = Sum21{}.countWays({ 10, 10, 11, 11 });
        const auto expected = 4;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
