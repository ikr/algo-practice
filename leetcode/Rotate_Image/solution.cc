#include "lest.hpp"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using vvec = vector<vector<int>>;

struct Solution {
    void rotate(vvec &rows) {
        assert(rows.size());
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("3 x 3") {
        vvec actual{
            {1,2,3},
            {4,5,6},
            {7,8,9},
        };

        Solution().rotate(actual);

        const vvec expected{
            {7,4,1},
            {8,5,2},
            {9,6,3}
        };

        EXPECT(actual == expected);
    },
    CASE("4 x 4") {
        vvec actual{
            { 5, 1, 9,11},
            { 2, 4, 8,10},
            {13, 3, 6, 7},
            {15,14,12,16}
        };

        Solution().rotate(actual);

        const vvec expected{
            {15,13, 2, 5},
            {14, 3, 4, 1},
            {12, 6, 8, 9},
            {16, 7,10,11}
        };

        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
