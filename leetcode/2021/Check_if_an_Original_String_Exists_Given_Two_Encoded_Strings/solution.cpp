#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct Solution final {
    bool possiblyEquals(const string &a, const string &b) { return false; }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const auto actual = Solution{}.possiblyEquals("internationalization", "i18n");
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = Solution{}.possiblyEquals("l123e", "44");
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = Solution{}.possiblyEquals("a5b", "c5b");
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = Solution{}.possiblyEquals("112s", "g841");
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = Solution{}.possiblyEquals("ab", "a2");
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("111 and 84") {
        const auto actual = Solution{}.possiblyEquals("111", "84");
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("6aa and 23aa") {
        const auto actual = Solution{}.possiblyEquals("6aa", "23aa");
        const auto expected = false;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
