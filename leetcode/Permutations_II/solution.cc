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

struct Solution {
    vector<vector<int>> permuteUnique(const vector<int> &xs) {
        return xs.size() ? vector<vector<int>>{{xs.back()}}
                         : vector<vector<int>>{{}};
    }
};

int answer_to_life_universe_and_everything() { return -1; }

// clang-format off
const lest::test tests[] = {
    CASE("empty output on empty input") {
        const auto actual = Solution().permuteUnique(vector<int>{});
        const auto expected = vector<vector<int>>{{}};
        EXPECT(actual == expected);
    },
    CASE("trivial 1-element input") {
        const auto actual = Solution().permuteUnique(vector<int>{42});
        const auto expected = vector<vector<int>>{{42}};
        EXPECT(actual == expected);
    },
    CASE("example from the problem statement") {
        const auto actual = Solution().permuteUnique(vector<int>{1,1,2});
        const auto expected = vector<vector<int>>{{1,1,2},{1,2,1},{2,1,1}};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
