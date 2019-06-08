#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    vector<int> prevPermOpt1(const vector<int> &xs) { return xs; }
};

// clang-format off
const lest::test tests[] = {
    CASE("degenerate 0") {
        const auto actual = Solution().prevPermOpt1({});
        const auto expected = vector<int>{};
        EXPECT(actual == expected);
    },
    CASE("degenerate 1") {
        const auto actual = Solution().prevPermOpt1({1});
        const auto expected = vector<int>{1};
        EXPECT(actual == expected);
    },
    CASE("problem statement example 1") {
        const auto actual = Solution().prevPermOpt1({3,2,1});
        const auto expected = vector<int>{3,1,2};
        EXPECT(actual == expected);
    },
    CASE("problem statement example 2") {
        const auto actual = Solution().prevPermOpt1({1,1,5});
        const auto expected = vector<int>{1,1,5};
        EXPECT(actual == expected);
    },
    CASE("problem statement example 3") {
        const auto actual = Solution().prevPermOpt1({1,9,4,6,7});
        const auto expected = vector<int>{1,7,4,6,9};
        EXPECT(actual == expected);
    },
    CASE("problem statement example 4") {
        const auto actual = Solution().prevPermOpt1({3,1,1,3});
        const auto expected = vector<int>{1,3,1,3};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
