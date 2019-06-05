#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int slidingPuzzle(const vector<vector<int>> &board) const {
        return static_cast<int>(board.size());
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("problem statement example 1") {
        const auto actual = Solution().slidingPuzzle({
            {1,2,3},
            {4,0,5}
        });

        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 1 variation") {
        const auto actual = Solution().slidingPuzzle({
            {1,2,0},
            {4,5,3}
        });

        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 2") {
        const auto actual = Solution().slidingPuzzle({
            {1,2,3},
            {5,4,0}
        });

        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 3") {
        const auto actual = Solution().slidingPuzzle({
            {4,1,2},
            {5,0,3}
        });

        const auto expected = 5;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 4") {
        const auto actual = Solution().slidingPuzzle({
            {3,2,4},
            {1,5,0}
        });

        const auto expected = 14;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
