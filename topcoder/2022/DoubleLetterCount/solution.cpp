#include "lest.hpp"
#include <iostream>
#include <string>
using namespace std;

template <typename T> constexpr int inof(const T x) { return static_cast<int>(x); }

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

struct DoubleLetterCount final {
    int count(const string &xs) const {
        int result{};

        for (int i = 1; i <sz(xs); ++i) {
            if (xs[i - 1] == xs[i]) ++result;
        }

        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DoubleLetterCount{}.count("MISS");
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = DoubleLetterCount{}.count("COMMITTEE");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
