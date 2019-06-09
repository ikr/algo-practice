#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    bool possibleBipartition(const int n, const vector<vector<int>> &dislikes) {
        return n > static_cast<int>(dislikes.size());
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("problem statement example 1") {
        const auto actual = Solution().possibleBipartition(4, {{1,2},{1,3},{2,4}});
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 2") {
        const auto actual = Solution().possibleBipartition(3, {{1,2},{1,3},{2,3}});
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 3") {
        const auto actual = Solution().possibleBipartition(5, {{1,2},{2,3},{3,4},{4,5},{1,5}});
        const auto expected = false;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
