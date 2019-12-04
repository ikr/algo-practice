#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    vector<int> plusOne(const vector<int> &xs) const {
        vector<int> ans = xs;
        bool carry = true;

        for (auto i = ans.rbegin(); i != ans.rend() && carry; ++i) {
            const int x = *i + 1;
            *i = x % 10;
            carry = x / 10;
        }

        if (carry) ans.insert(ans.begin(), 1);

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("problem statement example 1") {
        const auto actual = Solution().plusOne({1, 2, 3});
        const auto expected = vector<int>{1, 2, 4};
        EXPECT(actual == expected);
    },
    CASE("problem statement example 2") {
        const auto actual = Solution().plusOne({4,3,2,1});
        const auto expected = vector<int>{4,3,2,2};
        EXPECT(actual == expected);
    },
    CASE("zero") {
        const auto actual = Solution().plusOne({0});
        const auto expected = vector<int>{1};
        EXPECT(actual == expected);
    },
    CASE("with a double carry") {
        const auto actual = Solution().plusOne({9, 9});
        const auto expected = vector<int>{1, 0, 0};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
