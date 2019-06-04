#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int totalNQueens(const int n) const { return n; }
};

// clang-format off
const lest::test tests[] = {
    CASE("0") {
        const auto actual = Solution().totalNQueens(0);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("1") {
        const auto actual = Solution().totalNQueens(1);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("2") {
        const auto actual = Solution().totalNQueens(2);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("3") {
        const auto actual = Solution().totalNQueens(3);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("4") {
        const auto actual = Solution().totalNQueens(4);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("5") {
        const auto actual = Solution().totalNQueens(5);
        const auto expected = 10;
        EXPECT(actual == expected);
    },
    CASE("8") {
        const auto actual = Solution().totalNQueens(8);
        const auto expected = 92;
        EXPECT(actual == expected);
    },
    CASE("10") {
        const auto actual = Solution().totalNQueens(724);
        const auto expected = 92;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
