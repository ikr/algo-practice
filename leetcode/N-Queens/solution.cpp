#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    vector<vector<string>> solveNQueens(int n) const { return {}; }
};

// clang-format off
const lest::test tests[] = {
    CASE("1 x 1") {
        const auto actual = Solution{}.solveNQueens(4).size();
        const auto expected = 1U;
        EXPECT(actual == expected);
    },
    CASE("2 x 2") {
        const auto actual = Solution{}.solveNQueens(4).size();
        const auto expected = 0U;
        EXPECT(actual == expected);
    },
    CASE("3 x 3") {
        const auto actual = Solution{}.solveNQueens(4).size();
        const auto expected = 0U;
        EXPECT(actual == expected);
    },
    CASE("4 x 4") {
        const auto actual = Solution{}.solveNQueens(4).size();
        const auto expected = 2U;
        EXPECT(actual == expected);
    },
    CASE("5 x 5") {
        const auto actual = Solution{}.solveNQueens(4).size();
        const auto expected = 10U;
        EXPECT(actual == expected);
    },
    CASE("9 x 9") {
        const auto actual = Solution{}.solveNQueens(4).size();
        const auto expected = 352U;
        EXPECT(actual == expected);
    },
    CASE("10 x 10") {
        const auto actual = Solution{}.solveNQueens(4).size();
        const auto expected = 724U;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
