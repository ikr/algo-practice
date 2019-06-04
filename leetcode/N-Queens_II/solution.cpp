#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

int intof(const size_t x) { return static_cast<int>(x); }

bool is_ok(const vector<int> &cols, const int candidate_col) {
    const int candidate_row = intof(cols.size());

    for (int r = 0; r != intof(cols.size()); ++r) {
        const int c = cols[r];

        if (c == candidate_col ||
            abs(c - candidate_col) == abs(r - candidate_row)) {
            return false;
        }
    }

    return true;
}

int recur(const int sz, vector<int> &cols) {
    if (intof(cols.size()) == sz) return 1;

    int result = 0;

    for (int col = 0; col != sz; ++col) {
        if (is_ok(cols, col)) {
            cols.push_back(col);
            result += recur(sz, cols);
            cols.pop_back();
        }
    }

    return result;
}

struct Solution final {
    int totalNQueens(const int sz) const {
        std::vector<int> v{};
        return recur(sz, v);
    }
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
    CASE("9") {
        const auto actual = Solution().totalNQueens(9);
        const auto expected = 352;
        EXPECT(actual == expected);
    },
    CASE("10") {
        const auto actual = Solution().totalNQueens(10);
        const auto expected = 724;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
