#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    vector<int> maxSlidingWindow(const vector<int> &xs, const int wsz) const {
        if (xs.empty()) return {};

        multiset<int> window(xs.cbegin(), xs.cbegin() + wsz);
        vector<int> ans(xs.size() - wsz + 1, *(window.rbegin()));

        for (size_t i = 1; i != xs.size() - wsz + 1; ++i) {
            window.erase(window.find(xs[i - 1]));
            window.insert(xs[i + wsz - 1]);
            ans[i] = *(window.rbegin());
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("empty array") {
        const auto actual = Solution().maxSlidingWindow({}, 0);
        const auto expected = vector<int>{};
        EXPECT(actual == expected);
    },
    CASE("max window on asc array") {
        const auto actual = Solution().maxSlidingWindow({1,2,3}, 3);
        const auto expected = vector{3};
        EXPECT(actual == expected);
    },
    CASE("max window on desc array") {
        const auto actual = Solution().maxSlidingWindow({3,2,1}, 3);
        const auto expected = vector{3};
        EXPECT(actual == expected);
    },
    CASE("tiny array") {
        const auto actual = Solution().maxSlidingWindow({0,1}, 1);
        const auto expected = vector{0,1};
        EXPECT(actual == expected);
    },
    CASE("problem statement exmple") {
        const auto actual = Solution().maxSlidingWindow({1,3,-1,-3,5,3,6,7}, 3);
        const auto expected = vector{3,3,5,5,6,7};
        EXPECT(actual == expected);
    },
    CASE("failed on 1st submission") {
        const auto actual = Solution().maxSlidingWindow({-7,-8,7,5,7,1,6,0}, 4);
        const auto expected = vector{7,7,7,7,7};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
