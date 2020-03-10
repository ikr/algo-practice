#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int cutOffTree(vector<vector<int>> &forest) { return forest.size(); }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        vector<vector<int>> input{
            {1,2,3},
            {0,0,4},
            {7,6,5}
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        vector<vector<int>> input{
            {1,2,3},
            {0,0,0},
            {7,6,5}
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        vector<vector<int>> input{
            {2,3,4},
            {0,0,5},
            {8,7,6}
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("A single tree") {
        vector<vector<int>> input{
            {1,1,1},
            {0,1,1},
            {2,1,0}
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = 4;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
