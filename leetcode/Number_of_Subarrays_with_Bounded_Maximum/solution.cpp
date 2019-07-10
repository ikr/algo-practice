#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

// {6,9,2,7,4,7,1,8,5}, 4, 7
// ans 1
// i 2
// xs[i] 2
// first -
// current_max -

struct Solution final {
    int numSubarrayBoundedMax(const vector<int> &xs, const int lo,
                              const int hi) const {
        int ans{0};
        optional<int> first;
        optional<int> curr_max;

        for (size_t i = 0; i != xs.size(); ++i) {
            if (!first) {
                if (xs[i] <= hi) {
                    first = i;
                }
            } else {
                if (xs[i] > hi) {
                    if (curr_max) ans += i - *first;
                    first = nullopt;
                    curr_max = nullopt;
                    continue;
                }
            }

            if (lo <= xs[i] && xs[i] <= hi) {
                if (!curr_max || *curr_max < xs[i]) {
                    curr_max = xs[i];
                }
            }
        }

        if (curr_max) {
            ans += xs.size() - *first;
        };

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("empty") {
        const auto actual = Solution().numSubarrayBoundedMax({}, 1, 2);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("full") {
        const auto actual = Solution().numSubarrayBoundedMax({1,1,1,1}, 1, 2);
        const auto expected = 10;
        EXPECT(actual == expected);
    },
    CASE("propblem statement example") {
        const auto actual = Solution().numSubarrayBoundedMax({2,1,4,3}, 2, 3);
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("leetcode test 3") {
        const auto actual = Solution().numSubarrayBoundedMax({2,9,2,5,6}, 2, 8);
        const auto expected = 7;
        EXPECT(actual == expected);
    },
    CASE("random 1") {
        const auto actual = Solution().numSubarrayBoundedMax({1,2,3,1,2}, 1, 2);
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("random 2") {
        const auto actual = Solution().numSubarrayBoundedMax({6,9,2,7,4,7,1,8,5}, 4, 7);
        const auto expected = 15;
        EXPECT(actual == expected);
    },
    CASE("PI 8 9") {
        const auto actual = Solution().numSubarrayBoundedMax({3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3}, 8, 9);
        const auto expected = 104;
        EXPECT(actual == expected);
    },
    CASE("head-only") {
        const auto actual = Solution().numSubarrayBoundedMax({1,2,2}, 1, 1);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("tail-only") {
        const auto actual = Solution().numSubarrayBoundedMax({2,2,2,1}, 1, 1);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
