#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

template <typename T> int intof(T x) { return static_cast<int>(x); }

struct Solution final {
    int maxSubArray(const vector<int> &xs) const { return intof(xs.size()); }
};

// clang-format off
const lest::test tests[] = {
    CASE("-2147483648 on empty array") {
        const auto actual = Solution().maxSubArray({});
        const auto expected = INT_MIN;
        EXPECT(actual == expected);
    },
    CASE("trivial positive") {
        const auto actual = Solution().maxSubArray({1});
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("trivial negative") {
        const auto actual = Solution().maxSubArray({-1});
        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("all positive") {
      const auto actual = Solution().maxSubArray({1, 2, 3, 4});
        const auto expected = 10;
        EXPECT(actual == expected);
    },
    CASE("problem statement example") {
      const auto actual = Solution().maxSubArray({-2,1,-3,4,-1,2,1,-5,4});
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("all negative") {
      const auto actual = Solution().maxSubArray({-3,-1,-2,-4});
        const auto expected = -1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
