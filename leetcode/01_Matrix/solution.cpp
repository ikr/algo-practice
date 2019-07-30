#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Vec = vector<int>;
using VVec = vector<Vec>;
using RowCol = pair<int, int>;

struct Solution {
    VVec updateMatrix(const VVec &rows) { return rows; }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution{}.updateMatrix({
                {0,0,0},
                {0,1,0},
                {0,0,0},
            });

        const VVec expected = {
                {0,0,0},
                {0,1,0},
                {0,0,0},
        };

        EXPECT(actual == expected);
    },
    CASE("Problem statement example 2") {
        const auto actual = Solution().updateMatrix({
                {0,0,0},
                {0,1,0},
                {1,1,1},
            });

        const VVec expected = {
                {0,0,0},
                {0,1,0},
                {1,2,1},
       };

        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
