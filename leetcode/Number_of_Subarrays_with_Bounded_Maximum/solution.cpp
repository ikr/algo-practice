#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int numSubarrayBoundedMax(const vector<int> &xs, const int lo,
                              const int hi) const {
        int ans{0};
        optional<int> first;
        optional<int> current_max;

        for (size_t i = 0; i != xs.size(); ++i) {
            if (!current_max) {
                if (lo <= xs[i] && xs[i] <= hi) {
                    current_max = xs[i];
                    first = i;
                }
            } else {
                if (xs[i] > *current_max) {
                    if (lo <= xs[i] && xs[i] <= hi) {
                        current_max = xs[i];
                    } else {
                        ans += i - *first;
                        first = nullopt;
                        current_max = nullopt;
                    }
                }
            }
        }

        if (current_max) {
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
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("propblem statement example") {
        const auto actual = Solution().numSubarrayBoundedMax({2,1,4,3}, 2, 3);
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("random 1") {
        const auto actual = Solution().numSubarrayBoundedMax({1,2,3,1,2}, 1, 2);
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("random 2") {
        const auto actual = Solution().numSubarrayBoundedMax({6,9,2,7,4,7,1,8,5}, 4, 7);
        const auto expected = 7;
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
